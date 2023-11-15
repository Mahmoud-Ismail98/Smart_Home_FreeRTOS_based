/*
 * ICU.c
 *
 * Created: 30/10/2023 06:21:46 م
 *  Author: mkora
 */ 
#include "../../services/Std_types.h"
#include "../../services/Bit_utils.h"

#include "../../MCAL/PORT/include/port.h"
#include "../../MCAL/DIO/include/DIO.h"
#include "../../MCAL/DIO/include/DIO_private.h"
#include "../../MCAL/TIMER0/include/TIMER0_private.h"
#include "../../MCAL/TIMER0/include/TIMER0_Interface.h"
#include "../../MCAL/EXT_INTERUPT/include/external_interrupt.h"
#include "../../MCAL/EXT_INTERUPT/include/external_interupt_private.h"
volatile u8 EXTI_COUNTER=0;
volatile u32  on_period=0;
volatile u32  off_period=0;
volatile u32 NUM_TIMER_OVERFLOW=0;
volatile float duty_cycle= 0;

void ISR_TIMER0_OVERFLOW(void)
{

	 NUM_TIMER_OVERFLOW++;
}
void EXTI0_CALLBACK(void)
{
	TGL_BIT(PORTA,PORTA_PIN1);
	if (EXTI_COUNTER==0)
	{
		Timer0_EnableInterupt();
		TCNT0=0;
		CLR_BIT(MCUCSR,6);   //falling_edge		
		EXTI_COUNTER++;
	}
	else if (EXTI_COUNTER==1)
	{
		SET_BIT(MCUCSR,6);  //rising edge 
		on_period = TCNT0+NUM_TIMER_OVERFLOW*256;
		TCNT0=0;
		NUM_TIMER_OVERFLOW=0;
		EXTI_COUNTER++;
	}
	else if(EXTI_COUNTER==2)
	{
		off_period = TCNT0+NUM_TIMER_OVERFLOW*256;	
		EXTI_COUNTER++;
		NUM_TIMER_OVERFLOW=0;
		duty_cycle=(float)on_period/(on_period+off_period)*100;
		EXTI_COUNTER=0;
		
	} 	
}

float ICU_calculateDuty_cycle(void)
{

	while (duty_cycle==0);
	return duty_cycle;
	
}
void ICU_int(void)
{
		Global_Interrupt_EnablE();
		Enable_EXT_INT(EXT_INT0);
		extrnal_int_init(EXT_INT0,RISING_EDGE,EXTI0_CALLBACK);
		TIMER0_voidMode();
		Timer0SetCallBack(ISR_TIMER0_OVERFLOW);
	
}