
#include "../../services/Std_types.h"
#include "../../services/Bit_utils.h"
#include <util/delay.h>
#include "../../MCAL/PORT/include/port.h"
#include "../../MCAL/DIO/include/DIO.h"
#include "../../HAL/LCD/LCD_config.h"
#include "../../HAL/LCD/LCD_interface.h"
//#include "../../../../FreeRTOS/Source/include/task.h"

#include "FreeRTOS.h"
#include "task.h"

#define HIGH_LEVEL 1
#define LOW_LEVEL 0

void LCD_voidInit(void)
{

	Port_setPinDirection(D0_PIN,PIN_OUTPUT);
	Port_setPinDirection(D1_PIN,PIN_OUTPUT);
	Port_setPinDirection(D2_PIN,PIN_OUTPUT);
	Port_setPinDirection(D3_PIN,PIN_OUTPUT);
	Port_setPinDirection(D4_PIN,PIN_OUTPUT);
	Port_setPinDirection(D5_PIN,PIN_OUTPUT);
	Port_setPinDirection(D6_PIN,PIN_OUTPUT);
	Port_setPinDirection(D7_PIN,PIN_OUTPUT);

	Port_setPinDirection(RS_PIN,PIN_OUTPUT);
	Port_setPinDirection(RW_PIN,PIN_OUTPUT);
	Port_setPinDirection(EN_PIN,PIN_OUTPUT);
	

//	_delay_ms(40);       //wait for start initialization
	vTaskDelay(40);
	LCD_voidSendCommand(0x38);   //8bit mode
	LCD_voidSendCommand(0x0E);   //curser not be blinking
	LCD_voidSendCommand(0x01);   // clear display
//	_delay_ms(2);	
	vTaskDelay(2);
	//LCD_voidSendCommand(0x06);   //INCREAMENT CURSOR TO RIGHT
	LCD_voidSendCommand(0x0C);   //hide CURSOR 

}

void LCD_voidWriteCharacter(u8 Character)
{

	DIO_WritrPin(RW_PIN,LOW_LEVEL);
	DIO_WritrPin(RS_PIN,HIGH_LEVEL);
	//DIO_WritePin(RW_PORT,RW_PIN,LOW_LEVEL);

	DIO_WritrPin(D0_PIN,GET_BIT(Character,0));
	DIO_WritrPin(D1_PIN,GET_BIT(Character,1));
	DIO_WritrPin(D2_PIN,GET_BIT(Character,2));
	DIO_WritrPin(D3_PIN,GET_BIT(Character,3));
	DIO_WritrPin(D4_PIN,GET_BIT(Character,4));
	DIO_WritrPin(D5_PIN,GET_BIT(Character,5));
	DIO_WritrPin(D6_PIN,GET_BIT(Character,6));
	DIO_WritrPin(D7_PIN,GET_BIT(Character,7));

	DIO_WritrPin(EN_PIN,HIGH_LEVEL);
	vTaskDelay(2);
	//_delay_ms(2);
	DIO_WritrPin(EN_PIN,LOW_LEVEL);

}
void LCD_voidSendCommand(u8 Command)
{
	DIO_WritrPin(RS_PIN,LOW_LEVEL);
	DIO_WritrPin(RW_PIN,LOW_LEVEL);

	DIO_WritrPin(D0_PIN,GET_BIT(Command,0));
	DIO_WritrPin(D1_PIN,GET_BIT(Command,1));
	DIO_WritrPin(D2_PIN,GET_BIT(Command,2));
	DIO_WritrPin(D3_PIN,GET_BIT(Command,3));
	DIO_WritrPin(D4_PIN,GET_BIT(Command,4));
	DIO_WritrPin(D5_PIN,GET_BIT(Command,5));
	DIO_WritrPin(D6_PIN,GET_BIT(Command,6));
	DIO_WritrPin(D7_PIN,GET_BIT(Command,7));

	DIO_WritrPin(EN_PIN,HIGH_LEVEL);
		
	_delay_ms(2);		
	DIO_WritrPin(EN_PIN,LOW_LEVEL);
	_delay_ms(10);


}
void LCD_voidCustomChar (unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
		LCD_voidSendCommand (0x40 + (loc*8));	/* Command 0x40  point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_voidWriteCharacter(msg[i]);
	}
	  LCD_voidSendCommand(0x80); //shift back to DDRAM location 0
}
void LCD_voidWriteString(u8 *string)
{

	while(*string!='\0')
	{
		LCD_voidWriteCharacter(*string);
		string++;

	}


}
u8 ARR_LOC_ROWS[]={0x80,0xC0,0x94,0xD4};
/*void LCD_voidSetCursor(u8 x,u8 y)
{
	
	LCD_voidSendCommand(ARR_LOC_ROWS[x-1]+(y-1));
}
*/
void LCD_voidSetCursor(u8 x, u8 y)
{
	if((x<20)&&(y<4))
	{
		
		u8 loc_address=0;
		switch(y)
		{
			case 0:loc_address=0x80+0x00; break;
			case 1:loc_address=0x80+0x40; break;
			case 2:loc_address=0x80+0x14; break;						
			case 3:loc_address=0x80+0x54; break;			
		}	
		LCD_voidSendCommand(loc_address+x);   
		}		
}

void LCD_voidClear(void)
{
	LCD_voidSendCommand(0x01);
}

void Lcd_voidShiftRight(void)
{
	LCD_voidSendCommand(0x1C);
	//LCD_voidSendCommand(0x14);   //INCREAMENT CURSOR TO RIGHT
}

void Lcd_voidShiftLeft(void)
{
	LCD_voidSendCommand(0x18);
}
void lcd_voidSendNumber   ( u16 *Copynum2)
{
u16	Copynum=*Copynum2;
u16 LOC_u64Reversed = 1 ;
if( Copynum == 0 ){ LCD_voidWriteCharacter('0'); }
else{
	while( Copynum != 0 ){
		LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Copynum % 10 );
		Copynum /= 10 ;
	}
	while( LOC_u64Reversed != 1 ){
		LCD_voidWriteCharacter( ( LOC_u64Reversed % 10 ) + 48 );
		LOC_u64Reversed /= 10 ;
	}
}

}

/*
void lcd_voidSendNumber ( u64 Copy_u64Number)
{	
		if(Copy_u64Number==0)
		{
			LCD_voidWriteCharacter('0');
		}
		else
		{
		u8 numbers[10]={'0','1','2','3','4','5','6','7','8','9'};
		u32 temp=1;
		while(Copy_u64Number)
		{
			temp=temp*10+Copy_u64Number%10;
			Copy_u64Number/=10;
		}
		while(temp>1)
		{
			LCD_voidWriteCharacter(numbers[temp%10]);
			temp/=10;
		}
	   }
	
}
*/
/*
void lcd_voidSendNumber(u32 *Copynum2)
{
	u8 Copynum=*Copynum2;
	u8 arr[3]={0};
		for (u8 y=2;y>=0;y--)
		{
			//u8 arr[y]={0};
			arr[y]=Copynum%10;
			Copynum/=10;			
		}
		for (u8 y=0;y<=2;y++)
		{
		LCD_voidWriteCharacter(arr[y]+'0');	
		}
}
*/