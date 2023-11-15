

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
#include "../../MCAL/PORT/include/port_private.h"
#define RS_PORT  PORT_D
#define RS_PIN   PORTD_PIN2

#define RW_PORT  PORT_D
#define RW_PIN   PORTD_PIN1

#define EN_PORT  PORT_D
#define EN_PIN   PORTD_PIN0

/*
#define D0_PIN		PORTB_PIN3
#define D1_PIN		PORTA_PIN1
#define D2_PIN		PORTA_PIN2
#define D3_PIN		PORTA_PIN3
#define D4_PIN		PORTA_PIN4
#define D5_PIN		PORTA_PIN5
#define D6_PIN		PORTA_PIN6
#define D7_PIN		PORTA_PIN7

*/
#define D0_PIN		PORTC_PIN0
#define D1_PIN		PORTC_PIN1
#define D2_PIN		PORTC_PIN2
#define D3_PIN		PORTC_PIN3
#define D4_PIN		PORTC_PIN4
#define D5_PIN		PORTC_PIN5
#define D6_PIN		PORTC_PIN6
#define D7_PIN		PORTC_PIN7

#endif /* LCD_CONFIG_H_ */
