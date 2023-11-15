
#include "../../../services/Std_types.h"
#include "../../../services/Bit_utils.h"

#include "../../../MCAL/PORT/include/port.h"
#include "../../../MCAL/DIO/include/DIO.h"

#include "../../../MCAL/EXT_INTERUPT/include/external_interupt_private.h"
#include "../../../MCAL/EXT_INTERUPT/include/external_interrupt.h"
/*
#define EXT0_PIN	PORTD_PIN2
#define EXT1_PIN	PORTD_PIN3
#define EXT2_PIN	PORTB_PIN2
*/
/*DIRECTION*/

static void (*Call_backFromExtISR[3]) (void); // pointers to array of  funcation 
void Global_Interrupt_EnablE(void)
{
	SET_BIT(SREG,Global_Interrupt_Enablepin);
}
void Global_Interrupt_Disable(void)
{
	CLR_BIT(SREG,Global_Interrupt_Enablepin);
}
void extrnal_int_init(enum_extenal_int_n_t X,enum_external_int_type_t int_type,void (*PTR_TO_FUN)())
{
	switch (X)
	{
		case EXT_INT0 :
		{
			//DDRD  &= ~(1<<2);
			Port_setPinDirection(EXT0_PIN,PIN_INPUT);
			MCUCR &= 0b11111100 ;
			MCUCR |= int_type << 0;
			Call_backFromExtISR[0]=PTR_TO_FUN;
			break;
		}
		case EXT_INT1 :
		{
			Port_setPinDirection(EXT1_PIN,PIN_INPUT);
			MCUCR &= 0b11110011;
			MCUCR |= int_type<<2;
			Call_backFromExtISR[1]=PTR_TO_FUN;
			break;
		}
		case EXT_INT2 :
		{
			Port_setPinDirection(EXT2_PIN,PIN_INPUT);
			if(int_type==INT_FALLING_EDGE)
			{
				CLR_BIT(MCUCSR,6);
				
			}
			else if(int_type==INT_RISING_EDGE)
			{
				SET_BIT(MCUCSR,6);
			}
			else
			{
				//error
			}
			Call_backFromExtISR[2]=PTR_TO_FUN;
			break;
		}
	}	
}

void Enable_EXT_INT(u8 X)
{

	SET_BIT(GICR,X);
}

void Disable_EXT_INT(u8 X)
{
	CLR_BIT(GICR,X);
}

/*
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
Call_backFromExtISR[0]();
}


void __vector_2(void)__attribute__((signal));
void __vector_2(void)
{
Call_backFromExtISR[1]();
}


void __vector_3(void)__attribute__((signal));
void __vector_3(void)
{
Call_backFromExtISR[2]();
}
*/
/* Prototype for ISR of EXTI0 */
void __vector_1(void)			__attribute__((signal));
void __vector_1(void){
	if(Call_backFromExtISR[0] != NULL){
		Call_backFromExtISR[0]();
		SET_BIT( GIFR , EXT_INT0 );		
	}
}

/* Prototype for ISR of EXTI1 */
void __vector_2(void)			__attribute__((signal));
void __vector_2(void){
	if(Call_backFromExtISR[1] != NULL){
		Call_backFromExtISR[1]();
		SET_BIT( GIFR , EXT_INT1 );		
	}
}

/* Prototype for ISR of EXTI2 */
void __vector_3(void)			__attribute__((signal));
void __vector_3(void){
	if(Call_backFromExtISR[2] != NULL){
		Call_backFromExtISR[2]();
	}
}
