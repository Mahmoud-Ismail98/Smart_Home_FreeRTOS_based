/*
 * private.h
 *
 * Created: 24/10/2023 02:12:00 م
 *  Author: mkora
 */ 


#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_


/*
 * private.h
 *
 * Created: 24/10/2023 02:12:00 م
 *  Author: mkora
 */ 
#define SREG            *((volatile u8 *)0x5F)
#define TIMSK			*((volatile u8*)0X59)
#define TIFR			*((volatile u8*)0X58)
/*Timer0*/
#define TCCR0			*((volatile u8*)0X53)
#define TCNT0			*((volatile u8*)0X52)
#define OCR0			*((volatile u8*)0X5C)

//MODE
#define    NORMAL_MODE      			                            0
#define    PWM_OR_PHASE_COTROL                                      1
#define    CTC_MODE                                                 2
#define    FAST_PWM_MODE                                            3
//#define    TIMER_MODE NORMAL_MODE    
#define	normal				0
#define	toggle_OC0			1
#define	clear_OC0			2
#define	set_OC0				3
#define reversed			4

#define Compare_Output_Mode		set_OC0
#define comp_Fast_Pwm			clear_OC0
#define comp_phaseCorrect_Pwm	set_OC0

/*the  Macros of timer mode by Compare Output Mode non-PWM Mode */
#define    NON_PWM_NORMAL_PORT_OPRETATION                           0
#define    NON_PWM_TOGGLE_OC0_ON_COMPARE_MATCH                      1
#define    NON_PWM_CLEAR_OC0_ON_COMPARE_MATCH                       2
#define    NON_PWM_SET_OC0_ON_COMPARE_MATCH						    3
#define Compare_Output_nonPWM_Mode NON_PWM_TOGGLE_OC0_ON_COMPARE_MATCH
/*the  Macros of timer mode  
 by Compare Output Mode  by PWM Mode */   
#define    FAST_PWM_NORMAL_PORT_OPRETATION                          0
#define    FAST_PWM_CLEAR_OC0_ON_COMPARE_MATCH__SET_OC0_ON_TOP      1
#define    FAST_PWM_SET_OC0_ON_COMPARE_MATCH__CLEAR_OC0_ON_TOP	  	2
#define Compare_Output__PWM_Mode  FAST_PWM_NORMAL_PORT_OPRETATION
/*the  Macros of prescaler */   
#define		No_Clk_Source									 0	    //0
#define    CLK_DIV_BY_0										 1       //1
#define    CLK_DIV_BY_8										 8	    //2
#define    CLK_DIV_BY_64                                     64	     //3
#define    CLK_DIV_BY_256                                    256    //4
#define    CLK_DIV_BY_1024									1024    //5
#define    ECS_ON_T0_FALLING_EDGE      								6
#define    ECS_ON_T0_RISING_EDGE       								7
/*he macro count of resing or Falling*/
#define	   RISING_EDGE												0
#define	   FALLING_EDGE												1


#endif /* PRIVATE_H_ */