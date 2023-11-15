#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


#define ADC_enable_pin 7
#define ADC_INT_PIN	4
#define ADC_START_CONVERSATIONPin 6
#define INTERRUPT_ENABLE 1
#define INTERUPT_DISABLE 0


#define			 Free_Running_mode					0b000
#define			 Analog_Comparator					0b001
#define			 External_Interrupt_Request0		0b010
#define			 Timer_Counter0_Compare_Match		0b011
#define			 Timer_Counter0_Overflow			0b100
#define			 Timer_Counter1_Compare_Match_B		0b101
#define			 Timer_Counter1_Overflow			0b110
#define			 Timer_Counter1_Capture_Event		0b111
//#define Trigger_Source_Selections

#define INTERRUPT_ENABLE 1
#define INTERUPT_DISABLE 0
//#define INTERRUP_MODE INTERRUPT_ENABLE

#define ADMUX 		*((volatile u8 *)0x27)
#define ADCSRA 		*((volatile u8 *)0x26)
#define ADCH 		*((volatile u8 *)0x25)
#define ADCL 		*((volatile u8 *)0x24)
#define SFIOR 		*((volatile u8 *)0x50)



#define	PRE_SCALER0	   0b000
#define	PRE_SCALER2	   0b001
#define	PRE_SCALER4	   0b010
#define	PRE_SCALER8	   0b011
#define	PRE_SCALER16   0b100
#define	PRE_SCALER32   0b101
#define	PRE_SCALER64   0b110
#define	PRE_SCALER128  0b111


#define	 AREF				0b00
#define	 AVCC_5v			0b01
#define	 Reserved			0b10
#define	 Internal_2_5V		0b11


#endif