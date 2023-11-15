
#ifndef KEYPAD_CFG
#define KEYPAD_CFG
//#include "../../MCAL/DIO/include/DIO_private.h"
//#include "../../MCAL/PORT/include/port_private.h"


#define	 KEY_RAW0		PORTC_PIN0
#define	 KEY_RAW1		PORTC_PIN1
#define	 KEY_RAW2		PORTC_PIN2
#define	 KEY_RAW3		PORTC_PIN3
#define	 KEY_COL0		PORTC_PIN4
#define	 KEY_COL1		PORTC_PIN5
#define	 KEY_COL2		PORTC_PIN6
#define	 KEY_COL3		PORTC_PIN7

#define RAW_NUM 4
static u8 KEYPAD_SYMBOL[16]={7,8,9,0xFF,
							 4,5,6,0xFA,
							 1,2,3,0xFD,
							 4,0,0x0D,0xFB};

							 
							 
#endif 
