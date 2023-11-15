#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_


/*ERROR TYPE RETURN ERROR IN CASE PASSING WRONG PORT OR MODE ELSE RETURN ERROR_FREE */
/*
typedef enum {
	ERROR_FREE,
	PIN_NUMBER_ERROR,
	PIN_DIR_ERROR,
	PORT_ERROR,
	PIN_MODE_ERROR
}PIN_ERROR_TYPES;
*/

#define LOW_LEVEL  0
#define HIGH_LEVEL 1
/*PORT NUMBER*/
#define u8PORTA 					    0
#define u8PORTB							1
#define u8PORTC 			     		2
#define u8PORTD						    3
/*DIRECTION*/	
#define PIN_INPUT  0
#define PIN_OUTPUT 1
/*MODE*/
#define PIN_OUT_LOW    0
#define PIN_OUT_HIGH   1
#define PIN_IN_FLOAT   2
#define PIN_IN_PULLUP  3

#define PORTA (*(volatile u8*) 0x3B)
#define DDRA  (*(volatile u8*) 0x3A)
#define PINA  (*(volatile u8*) 0x39)
#define PORTB (*(volatile u8*) 0x38)
#define DDRB  (*(volatile u8*) 0x37)
#define PINB  (*(volatile u8*) 0x36)
#define PORTC (*(volatile u8*) 0x35)
#define DDRC  (*(volatile u8*) 0x34)
#define PINC  (*(volatile u8*) 0x33)
#define PORTD (*(volatile u8*) 0x32)
#define DDRD  (*(volatile u8*) 0x31)
#define PIND  (*(volatile u8*) 0x30)

/*PORTA*/
#define PORTA_PIN0     0
#define PORTA_PIN1     1
#define PORTA_PIN2     2
#define PORTA_PIN3     3
#define PORTA_PIN4     4
#define PORTA_PIN5     5
#define PORTA_PIN6     6
#define PORTA_PIN7     7
/*PORTB*/
#define PORTB_PIN0    8
#define PORTB_PIN1    9
#define PORTB_PIN2    10
#define PORTB_PIN3    11
#define PORTB_PIN4    12
#define PORTB_PIN5    13
#define PORTB_PIN6    14
#define PORTB_PIN7    15
/*PORTC*/
#define PORTC_PIN0    16
#define PORTC_PIN1    17
#define PORTC_PIN2    18
#define PORTC_PIN3    19
#define PORTC_PIN4    20
#define PORTC_PIN5    21
#define PORTC_PIN6    22
#define PORTC_PIN7    23
/*PORTD*/
#define PORTD_PIN0    24
#define PORTD_PIN1    25
#define PORTD_PIN2    26
#define PORTD_PIN3    27
#define PORTD_PIN4    28
#define PORTD_PIN5    29
#define PORTD_PIN6    30
#define PORTD_PIN7    31

#endif