#include "../../../services/Std_types.h"
#include "../../../services/Bit_utils.h"
#include "../../../MCAL/DIO/include/DIO_cfg.h"
#include "../../../MCAL/DIO/include/DIO_private.h"
#include "../../../MCAL/DIO/include/DIO.h"

PIN_ERROR_TYPES DIO_WritrPin(u8 pin_id,u8 level_value)
{
PIN_ERROR_TYPES ERROR_LOCRET =ERROR_FREE;
if (pin_id>31)  /*in case not valid pin id */
{
	ERROR_LOCRET=PIN_NUMBER_ERROR;
}
else	 /*case valid id pin*/
{	
	u8 loc_pin_id =pin_id % 8;

	u8 loc_port_num=pin_id/8;
	switch(loc_port_num)
	{
		case u8PORTA:
		if (GET_BIT(DDRA,loc_pin_id)==PIN_OUTPUT)
		{
			switch (level_value)
			{
				case HIGH_LEVEL:
				SET_BIT(PORTA,loc_pin_id);
				break;
				case LOW_LEVEL:
				CLR_BIT(PORTA,loc_pin_id);
				break;
			}
		}
		else
		{	ERROR_LOCRET=PIN_DIR_ERROR;
		}
		break;
		case u8PORTB:
		if (GET_BIT(DDRB,loc_pin_id)==PIN_OUTPUT)
		{
			switch (level_value)
			{
				case HIGH_LEVEL :
				SET_BIT(PORTB,loc_pin_id);
				break;
				case LOW_LEVEL : 
				CLR_BIT(PORTB,loc_pin_id);
				break;
			}
		}
		else
		{	ERROR_LOCRET=PIN_DIR_ERROR;
		}
		break;
		
		case u8PORTC:
		if (GET_BIT(DDRC,loc_pin_id)==PIN_OUTPUT)
		{
			switch (level_value)
			{
				case HIGH_LEVEL :
				SET_BIT(PORTC,loc_pin_id);
				break;
				case  LOW_LEVEL :
				CLR_BIT(PORTC,loc_pin_id);
				break;
			}
		}
		else
		{	ERROR_LOCRET=PIN_DIR_ERROR;
		}
		break;

		case u8PORTD:
		if (GET_BIT(DDRD,loc_pin_id)==PIN_OUTPUT)
		{
			switch (level_value)
			{
				case HIGH_LEVEL:
				SET_BIT(PORTD,loc_pin_id);
				break;
				case LOW_LEVEL:
				CLR_BIT(PORTD,loc_pin_id);
				break;
			}
		}
		else
		{	ERROR_LOCRET=PIN_DIR_ERROR;
		}
		break;
	}
}
	return ERROR_LOCRET;
}
PIN_ERROR_TYPES  DIO_READ_PIN(u8 pin_id,u8 *ptr_val)
{
PIN_ERROR_TYPES ERROR_LOCRET =ERROR_FREE;
if (pin_id>31)  /*in case not valid pin id */
{
	ERROR_LOCRET=PIN_NUMBER_ERROR;
}
else	 /*case valid id pin*/
{	
	//PIN_ERROR_TYPES ERROR_LOCRET=ERROR_FREE;
	u8 *Loc_ptr= ptr_val;

	u8 loc_pin_id =pin_id % 8;
	u8 loc_port_num=pin_id/8;
	
	switch(loc_port_num)
	{
		case u8PORTA:
		if(GET_BIT(DDRA,loc_pin_id)==PIN_INPUT)
		*Loc_ptr=(GET_BIT(PINA,loc_pin_id));
		
		else   ERROR_LOCRET=PIN_DIR_ERROR;
		
		case u8PORTB:
		if(GET_BIT(DDRB,loc_pin_id)==PIN_INPUT)
		*Loc_ptr=(GET_BIT(PINB,loc_pin_id));
		
		else   ERROR_LOCRET=PIN_DIR_ERROR;
		
		break;
		
		case u8PORTC:
		if(GET_BIT(DDRC,loc_pin_id)==PIN_INPUT)
		*Loc_ptr=(GET_BIT(PINC,loc_pin_id));
		
		else   ERROR_LOCRET=PIN_DIR_ERROR;
		
		break;
		
		case u8PORTD:
		if(GET_BIT(DDRD,loc_pin_id)==PIN_INPUT)
		*Loc_ptr=(GET_BIT(PIND,loc_pin_id));
		
		else   ERROR_LOCRET=PIN_DIR_ERROR;
		
		break;
		
		default :
		ERROR_LOCRET = PORT_ERROR;
		break;
	}
	

}
	return ERROR_LOCRET;
}

PIN_ERROR_TYPES  DIO_WritePort(u8 port_num,u8 port_value)
{
	PIN_ERROR_TYPES ERROR_LOCRET =ERROR_FREE;
	
	switch(port_num)
	{
		case u8PORTA:
		PORTA = port_value;
		break;
		
		case u8PORTB:
		PORTB = port_value;
		break;

		case u8PORTC:
		PORTC = port_value;
		break;

		case u8PORTD:
		PORTD = port_value;
		break;
		
		default:
		ERROR_LOCRET=PORT_ERROR;
		
	}
	return ERROR_LOCRET;
}

PIN_ERROR_TYPES  DIO_ReadPort(u8 port_num,u8 *ptr_val)
{
	
	PIN_ERROR_TYPES ERROR_LOCRET =ERROR_FREE;
	
	u8 *loc_ptr =ptr_val;
	switch(port_num)
	{
		case u8PORTA:
		*loc_ptr=PINA;
		break;
		
		case u8PORTB:
		*loc_ptr=PINB;
		break;

		case u8PORTC:
		*loc_ptr=PINC;
		break;

		case u8PORTD:
		*loc_ptr=PIND;
		break;
		
		default:
		ERROR_LOCRET=PORT_ERROR;
	}

	return ERROR_LOCRET;
}

PIN_ERROR_TYPES DIO_TogglePin(u8 Copy_u8ChannelId) {

	PIN_ERROR_TYPES LOC_enuReturnStatus = ERROR_FREE;
	u8 LOC_u8Port;
	u8 LOC_u8Pin;

		LOC_u8Port = Copy_u8ChannelId / 8;
		LOC_u8Pin = Copy_u8ChannelId % 8;

		switch (LOC_u8Port) {

			case u8PORTA:

			if (GET_BIT(DDRA,LOC_u8Pin) == PIN_OUTPUT) {

				TGL_BIT(PORTA, LOC_u8Pin);

			}
			break;

			case u8PORTB:

			if (GET_BIT(DDRB,LOC_u8Pin) == PIN_OUTPUT) {

				TGL_BIT(PORTB, LOC_u8Pin);

			}
			break;

			case u8PORTC:

			if (GET_BIT(DDRC,LOC_u8Pin) == PIN_OUTPUT) {

				TGL_BIT(PORTC, LOC_u8Pin);

			}
			break;

			case u8PORTD:

			if (GET_BIT(DDRD,LOC_u8Pin) == PIN_OUTPUT) {

				TGL_BIT(PORTD, LOC_u8Pin);

			}
			break;

		}

	return LOC_enuReturnStatus;
}