#include "../../../services/Bit_utils.h"
#include "../../../services/Std_types.h"
#include "../../../MCAL/PORT/include/port_cfg.h"
#include "../../../MCAL/PORT/include/port_private.h"
#include "../../../MCAL/PORT/include/port.h"




void Port_Init(void)
{

    #undef  PIN_IN_FLOAT
    #define PIN_IN_FLOAT 0

    #undef  PIN_IN_PULLUP
    #define PIN_IN_PULLUP 0

    #undef  PIN_OUT_LOW
    #define PIN_OUT_LOW 1

    DDRA=CONC(PORTA_PIN7_MODE,PORTA_PIN6_MODE,PORTA_PIN5_MODE,PORTA_PIN4_MODE,PORTA_PIN3_MODE,PORTA_PIN2_MODE,PORTA_PIN1_MODE,PORTA_PIN0_MODE);
    DDRB=CONC(PORTA_PIN7_MODE,PORTB_PIN6_MODE,PORTB_PIN5_MODE,PORTB_PIN4_MODE,PORTB_PIN3_MODE,PORTB_PIN2_MODE,PORTA_PIN1_MODE,PORTB_PIN0_MODE);
    DDRC=CONC(PORTC_PIN7_MODE,PORTC_PIN6_MODE,PORTC_PIN5_MODE,PORTC_PIN4_MODE,PORTC_PIN3_MODE,PORTC_PIN2_MODE,PORTC_PIN1_MODE,PORTC_PIN0_MODE);
    DDRD=CONC(PORTD_PIN7_MODE,PORTD_PIN6_MODE,PORTD_PIN5_MODE,PORTD_PIN4_MODE,PORTD_PIN3_MODE,PORTD_PIN2_MODE,PORTD_PIN1_MODE,PORTD_PIN0_MODE);

	#undef PIN_OUT_LOW
	#define PIN_OUT_LOW  0
	
    #undef PIN_IN_FLOAT
    #define PIN_IN_FLOAT 0

    #undef PIN_IN_PULLUP
    #define PIN_IN_PULLUP 1
	
    PORTA=CONC(PORTA_PIN7_MODE,PORTA_PIN6_MODE,PORTA_PIN5_MODE,PORTA_PIN4_MODE,PORTA_PIN3_MODE,PORTA_PIN2_MODE,PORTA_PIN1_MODE,PORTA_PIN0_MODE);
    PORTB=CONC(PORTA_PIN7_MODE,PORTB_PIN6_MODE,PORTB_PIN5_MODE,PORTB_PIN4_MODE,PORTB_PIN3_MODE,PORTB_PIN2_MODE,PORTA_PIN1_MODE,PORTB_PIN0_MODE);
    PORTC=CONC(PORTC_PIN7_MODE,PORTC_PIN6_MODE,PORTC_PIN5_MODE,PORTC_PIN4_MODE,PORTC_PIN3_MODE,PORTC_PIN2_MODE,PORTC_PIN1_MODE,PORTC_PIN0_MODE);
    PORTD=CONC(PORTD_PIN7_MODE,PORTD_PIN6_MODE,PORTD_PIN5_MODE,PORTD_PIN4_MODE,PORTD_PIN3_MODE,PORTD_PIN2_MODE,PORTD_PIN1_MODE,PORTD_PIN0_MODE);
	
	#undef PIN_IN_FLOAT
	#define PIN_IN_FLOAT 2
	#undef PIN_IN_PULLUP
	#define PIN_IN_PULLUP 3	


}
PIN_ERROR_TYPES Port_setPinDirection(u8 pin_id,u8 pin_direction)  
{
PIN_ERROR_TYPES ERROR_LOC_RET =ERROR_FREE;	
if (pin_id>31)  /* in case not valid id pin */
{
	ERROR_LOC_RET=PIN_NUMBER_ERROR;
} 
else           /*in case valid id pin */
{	
    u8 loc_pin_id =pin_id % 8;
    u8 loc_port_num=pin_id/8;
    switch(loc_port_num)
    {
        case u8PORTA:
        if(pin_direction==PIN_OUTPUT)
        {
            SET_BIT(DDRA,loc_pin_id);   
        }
        else if(pin_direction==PIN_INPUT)
        {
            CLR_BIT(DDRA,loc_pin_id);
        } 
		break;     
        case u8PORTB:
        if(pin_direction==PIN_OUTPUT)
        {
           SET_BIT(DDRB,loc_pin_id);
        }
        else if(pin_direction==PIN_INPUT)
        {
            CLR_BIT(DDRB,loc_pin_id);
        }
        break;
        case u8PORTC:

        if(pin_direction==PIN_OUTPUT)
        {
            SET_BIT(DDRC,loc_pin_id);
        }
        else if(pin_direction==PIN_INPUT)
        {
            CLR_BIT(DDRC,loc_pin_id);
        }
        break;
        case u8PORTD:
        if(pin_direction==PIN_OUTPUT)
        {
            SET_BIT(DDRD,loc_pin_id);
        }
        else if(pin_direction==PIN_INPUT)
        {
            CLR_BIT(DDRD,loc_pin_id);
        }
        break;
    default:
	 ERROR_LOC_RET =PIN_DIR_ERROR;
		
    }
}
 return ERROR_LOC_RET;   
}
PIN_ERROR_TYPES Port_SetPinMode(u8 pin_id,u8 pin_mode)
{
PIN_ERROR_TYPES ERROR_LOC_RET =ERROR_FREE;
if (pin_id>31)  /*in case not valid pin id */
{
	ERROR_LOC_RET=PIN_NUMBER_ERROR;
}
else	 /*case valid id pin*/
{
    u8 loc_Pin_id= pin_id % 8;
    u8 loc_port_num=pin_id/8;
    switch(loc_port_num)
    {
        case u8PORTA:
          switch(pin_mode){
            case PIN_OUT_HIGH:
			SET_BIT(DDRA,loc_Pin_id);
			SET_BIT(PORTA,loc_Pin_id);
			break;
			case  PIN_OUT_LOW:
			SET_BIT(DDRA,loc_Pin_id);
			CLR_BIT(PORTA,loc_Pin_id);
			break;	
            case   PIN_IN_FLOAT:
		    CLR_BIT(DDRA,loc_Pin_id);
		    CLR_BIT(PORTA,loc_Pin_id);                     
		    break;
            case   PIN_IN_PULLUP:
			CLR_BIT(DDRA,loc_Pin_id);
			SET_BIT(PORTA,loc_Pin_id);                     
			break;   				         
            default:
			ERROR_LOC_RET= PIN_MODE_ERROR;
		  }
		  break;			
        case u8PORTB:
          switch(pin_mode){		  
            case PIN_OUT_HIGH:
            SET_BIT(DDRB,loc_Pin_id);
            SET_BIT(PORTB,loc_Pin_id);
            break;
           case PIN_OUT_LOW:
            SET_BIT(DDRB,loc_Pin_id);
            CLR_BIT(PORTB,loc_Pin_id);
            break;
            case   PIN_IN_FLOAT:
            CLR_BIT(DDRB,loc_Pin_id);
            CLR_BIT(PORTB,loc_Pin_id);                     
            break;
            case   PIN_IN_PULLUP:
            CLR_BIT(DDRB,loc_Pin_id);
            SET_BIT(PORTB,loc_Pin_id);                     
            break;            
            default:
			ERROR_LOC_RET=PIN_MODE_ERROR;			  
		  }
		  break;			
        case u8PORTC:
          switch(pin_mode){
            case PIN_OUT_HIGH:
            SET_BIT(DDRC,loc_Pin_id);
            SET_BIT(PORTC,loc_Pin_id);
            break;
		    case PIN_OUT_LOW:
            SET_BIT(DDRC,loc_Pin_id);
            CLR_BIT(PORTC,loc_Pin_id);
            break;
            case   PIN_IN_FLOAT:
            CLR_BIT(DDRC,loc_Pin_id);
            CLR_BIT(PORTC,loc_Pin_id);                     
            break;

            case   PIN_IN_PULLUP:
            CLR_BIT(DDRC,loc_Pin_id);
            SET_BIT(PORTC,loc_Pin_id);                     
            break;            
            default:
			ERROR_LOC_RET=PIN_MODE_ERROR;	
		  }
		  break;					 
        case u8PORTD:
          switch(pin_mode){
            case PIN_OUT_HIGH:
            SET_BIT(DDRD,loc_Pin_id);
            SET_BIT(PORTD,loc_Pin_id);
            break;
            case PIN_OUT_LOW:
            SET_BIT(DDRD,loc_Pin_id);
            CLR_BIT(PORTD,loc_Pin_id);
            break;			
            case PIN_IN_FLOAT:
            CLR_BIT(DDRD,loc_Pin_id);
            CLR_BIT(PORTD,loc_Pin_id);                     
            break;
            case PIN_IN_PULLUP:
            CLR_BIT(DDRD,loc_Pin_id);
            SET_BIT(PORTD,loc_Pin_id);                     
            break;            
            default: 
			ERROR_LOC_RET=PIN_MODE_ERROR;	
			}
			break;		
        }   
	}	
	return ERROR_LOC_RET;	
	}
