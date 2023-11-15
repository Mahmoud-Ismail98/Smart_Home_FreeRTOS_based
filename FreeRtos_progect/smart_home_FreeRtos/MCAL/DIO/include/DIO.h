#ifndef DIO_H_
#define DIO_H_
/*DIO Driver is resposable to 
1) fun to write logical 0 or 1 on pin 
2)fun to write value on all pins of PORTA OR PORT B OR PORTC OR PORTD  
3)fun to read logical value on pins
4) fun to read the value on port and return it in pointer to integer 
*/

PIN_ERROR_TYPES  DIO_WritrPin(u8 pin_id,u8 level_value);		 /* fun to write logical 0 or 1 on pin */
PIN_ERROR_TYPES  DIO_READ_PIN(u8 pin_id,u8 *ptr_val);		/*fun to read logical value on pins*/
PIN_ERROR_TYPES  DIO_WritePort(u8 port_num,u8 port_value);   /*fun to write value on all pins of PORTA OR PORT B OR PORTC OR PORTD */  
PIN_ERROR_TYPES  DIO_ReadPort(u8 port_num,u8 *ptr_val);		/*fun to read the value on port and return it in pointer to integer*/
PIN_ERROR_TYPES DIO_TogglePin(u8 Copy_u8ChannelId); 

#endif