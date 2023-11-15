

#include "../../../services/Std_types.h"
#include "../../../services/Bit_utils.h"
#include "../../../MCAL/PORT/include/port.h"

#include "../../../MCAL/DIO/include/DIO.h"
#include "../../../MCAL/ADC/include/ADC_private.h"
#include "../../../MCAL/ADC/include/ADC_cfg.h"
#include "../../../MCAL/ADC/include/ADC.h"

static void(* ADC_PTRTOFUN)(u16 date) =NULL;


void ADC_voidInit(void)
{  
	
	SET_BIT(ADCSRA,ADC_enable_pin);  //ADC_enable_pin
	ADCSRA|=(PRESCALER);
	ADMUX|=(Ref_VOLT_MODE<<6);  //6
	//ADMUX|=(ADC_CHA);


#ifdef ADC_CHA
ADMUX|=(ADC_CHA);
#endif	
//SINGLE CONVERSATION MODE ADCSC CLEARD AUTOMATICALLY BY HARDWARE

#ifdef Trigger_Source_Selections
  SET_BIT(ADCSRA,5); //ADATE: ADC Auto Trigger Enable pin 
  SFIOR|=(Trigger_Source_Selections<<5);
#endif

#if INTERUPT==INTERRUPT_ENABLE
SET_BIT(ADCSRA ,3);  //Bit 3 – ADIE: ADC Interrupt Enable 
#endif	
}


ADC_ERROR_STATE ADC_read(u8 ADC_CHANEL,u16 *loc_AdcVal)
{
	ADC_ERROR_STATE ADC_ERROR =ADC_ERROR_FREE;
		ADCSRA |= (1<<ADC_START_CONVERSATIONPin);		/*6 IS  Start_conversion_pin  */
		
while((ADCSRA&(1<<ADC_INT_PIN))==0);	/*check for interrupt if */

	*loc_AdcVal = (u16)ADCL ;
	*loc_AdcVal = *loc_AdcVal+(u16)ADCH*256 ;
/*	*loc_AdcVal|=ADCL;
	*loc_AdcVal|=(ADCH<<8);	*/			
//	CLR_BIT(ADCSRA,4); 		
	return ADC_ERROR;

}

void ADC_Disable(void)
{
	CLR_BIT(ADCSRA,ADC_START_CONVERSATIONPin); //sart conversation pin 	
}


void ADC_SetCallBack(void (* copy_ptrfun)(u16 var))
{
	ADC_PTRTOFUN=copy_ptrfun;	
}
void ADC_InteruptDisable(void)
{
	CLR_BIT(ADCSRA ,3);  //Bit 3 – ADIE: ADC Interrupt Enable 
}
void ADC_AScyn(void)
{
	SET_BIT(ADCSRA ,3);  //Bit 3 – ADIE: ADC Interrupt Enable 	
	SET_BIT(ADCSRA,5);	//ADATE: ADC Auto Trigger Enable pin
	SFIOR|=(Free_Running_mode<<5);
	ADCSRA |= (1<<ADC_START_CONVERSATIONPin);		/*6 IS  Start_conversion_pin  */	
}

void __vector_16 (void)	__attribute__((signal)) ;
void __vector_16 (void)
{
		u16 loc_AdcVal = (u16)ADCL ;
		loc_AdcVal = loc_AdcVal+(u16)ADCH*256 ;
    	ADC_PTRTOFUN(loc_AdcVal);
		SET_BIT(ADCSRA,ADC_START_CONVERSATIONPin);
}

