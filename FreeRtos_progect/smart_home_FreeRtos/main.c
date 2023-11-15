
/*services includes*/
#include "services/Bit_utils.h"
#include "services/Std_types.h"
#include <util/delay.h>
/*FreeRTOS includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
/*MCAL includes*/
#include "MCAL/PORT/include/port.h"
#include "MCAL/PORT/include/port_private.h"
#include "MCAL/DIO/include/DIO.h"
#include "MCAL/ADC/include/ADC.h"
#include "MCAL/EXT_INTERUPT/include/external_interrupt.h"
/*HAL includes*/
#include "HAL/LCD/LCD_interface.h"
#include "HAL/KEYPAD/include/KEYPAD.h"

/*SOME of define pins*/
#define BUZZER_PIN	PORTA_PIN1	
//#define MAX_TEMP_OUT 60				/*for mapping reading from ADC channel to max temp*/

xSemaphoreHandle LCD_Semaphore = NULL;
xSemaphoreHandle TEMPSemaphore= NULL;

/*task code */
void  INIT_Task (void *pv);		/*initialization task for initialize lcd  then termiate */
void  KeyPad_Task (void *pv);   /*task that take the password from user and compare it with correct password then terminate*/
void  Lcd_Task	  (void *pv);   /*task responsable showing the state of temperture on lcd */
void  Buzzer_Task (void *pv);   /*task turn the buzzer if user enter wrong password equal to the max number of attempt*/
void  Fan_Task    (void *pv);	/*task that responsable on turning the fan tha matching the temperture of the room*/


/*sup function */
void TempNotificatonRead(u16 local_tempread);	/*function that passed to ADC interupt request in asynchrons mode*/
u16 compar_pass(u8 arr[],u8 pass_size);			/*function that convert the entered password into form of decimal to be easy used in compared with saved password*/

/*Create Task Handles Create */
xTaskHandle KeyPad_Task_Hadler  =NULL;
xTaskHandle Lcd_Task_Hadler		=NULL;
xTaskHandle Buzzer_Task_Hadler	=NULL;
xTaskHandle Fan_Task_Hadler		=NULL;


u16 CorrectPass=1234;		  /*var u16 that saved the password*/
u8  Buzzer_Flag =0;			  /*falg in case enter wrong password max number of attempt*/
volatile TEMP_READ = 0;       /*Variable to read the from ADC CH0 temp sensor*/
volatile  TempFlag=0;         /*FLAG TO that make synchronization between lcd_task and temp_task*/


int main(void)
{
	
/*intialization some of resources*/
	Port_setPinDirection(BUZZER_PIN,PIN_OUTPUT);
	Port_setPinDirection(PORTD_PIN7,PIN_OUTPUT);
	KEYPAD_voidInit();			
	ADC_voidInit();				/*ADC for receive read from temp sensor lm35*/
	TIMER2_voidInit();			/*timer2 resposable out pwm on fan depend on room temp */
	Global_Interrupt_EnablE();	/*ENABLE global interupt*/
	
/* semphore creation and intialization preferely to give semphore after creation */
	LCD_Semaphore=xSemaphoreCreateBinary();
	xSemaphoreGive(LCD_Semaphore);
	TEMPSemaphore=xSemaphoreCreateBinary();
	xSemaphoreGive(TEMPSemaphore);
	
/*create tasks*/
	xTaskCreate(INIT_Task,(const signed char *)"Init",150,NULL,5,NULL);
	xTaskCreate(KeyPad_Task,(const signed char *)"Task1",150,NULL,4,KeyPad_Task_Hadler);
	xTaskCreate(Lcd_Task,(const signed char *)"Task2",150,NULL,3,Lcd_Task_Hadler);	
	xTaskCreate(Buzzer_Task,(const signed char *)"Task3",150,NULL,4,Buzzer_Task_Hadler);
	xTaskCreate(Fan_Task,(const signed char *)"Task4",150,NULL,2,Fan_Task_Hadler);
	vTaskStartScheduler(); 
	while(1);
	return 0;
}

void  INIT_Task (void *pv)
{
	if(xSemaphoreTake(LCD_Semaphore,portMAX_DELAY) == pdPASS)
	{
		LCD_voidInit();
		LCD_voidSetCursor(4,0);	
		LCD_voidWriteString("WELCOME");	
		vTaskDelay(300);			
	}
	xSemaphoreGive(LCD_Semaphore);	
	vTaskDelete(NULL);	
}
void  KeyPad_Task (void *pv)
{
	u32 Entered_Pass=0;     /*var that take the return password for compare password fun */
	u8 key_pressed[4]={0};	/*array that store the entered password from the user*/	
	u8 trial_enterPass=0;   /*variable that count the number of wrong password */
	u8 size_arr=0;          /*variable to caculate the size of entered password*/
	u8 Max_num_wrongPass=3; /*var that store the max number of wrong password attempt*/
	u8 entered_key=0xFF;    /*var carry that return the keypressed value*/

	while(1)
	{

		if(xSemaphoreTake(LCD_Semaphore,portMAX_DELAY) == pdPASS)
		{
		LCD_voidClear();
		LCD_voidWriteString("Enter password ");					
		for (u8 i=0;i<4;i++)
		{
			while (entered_key==0xFF)
			{
		    	KEYPAD_FindKey(&entered_key);				
			}
			key_pressed[i]=entered_key;			
			entered_key=0xFF;
			LCD_voidWriteCharacter(key_pressed[i]+'0');		
		}
		size_arr= (sizeof(key_pressed)/sizeof(key_pressed[0]));
		Entered_Pass=compar_pass(key_pressed,size_arr );
		if (Entered_Pass==CorrectPass)
		{
			vTaskDelay(100);
			LCD_voidClear();
			LCD_voidSetCursor(4,0);				
			LCD_voidWriteString("done ");	
			xSemaphoreGive(LCD_Semaphore);
			vTaskDelete(NULL);		
		} 
		else
		{
			LCD_voidClear();
			LCD_voidWriteString("wrong_pass");	
			vTaskDelay(250);			
			xSemaphoreGive(LCD_Semaphore);	/*give the semaphore to enter the loop again*/	
			trial_enterPass++;
	
		}
		if (trial_enterPass==Max_num_wrongPass)
		{
				Buzzer_Flag=1;
				xSemaphoreTake(LCD_Semaphore,portMAX_DELAY); //take the semphore to insure not entering in lcd task			
			    vTaskDelete(NULL);					
		}
	  }	
	}
}

u16 compar_pass(u8 arr[],u8 pass_size)
{	
	u16 check_password=0;
	for (u8 i=0;i<pass_size;i++)
	{
		check_password=check_password*10+arr[i];	
	}
	return check_password;

}
void  Lcd_Task (void *pv)
{
	u8 lcd_semphore_state=0;
	u8 TEMP_semphore_state=0;	
	while(1)
	{		
		lcd_semphore_state=xSemaphoreTake(LCD_Semaphore,portMAX_DELAY);		
	    if(lcd_semphore_state == pdPASS)
	    {			
		 ADC_SetCallBack(TempNotificatonRead);
		 ADC_AScyn();
		// xSemaphoreGive(LCD_Semaphore);
	    }
		 vTaskDelay(250);
	}		
}

void  Buzzer_Task (void *pv)
{
	while (1)
	{
		if (Buzzer_Flag==1)
		{
			LCD_voidClear();
			LCD_voidWriteString("WARNING");
			DIO_WritrPin(BUZZER_PIN,PIN_OUT_HIGH);
			vTaskDelay(1000);
			Buzzer_Flag=0;
			DIO_WritrPin(BUZZER_PIN,PIN_OUT_LOW);
			LCD_voidClear();
		}
		vTaskDelay(500);
	}
}
void  Fan_Task(void *pv)
{
	u16 Last_Temp_Read=0;  /*variable store the current read then compare it with the last new read to save the cpu load in case equal reading */
	while (1)
	{
		if ((TempFlag==1 )&&(TEMP_READ!=Last_Temp_Read))
		{
			LCD_voidClear();	
			LCD_voidWriteString("ROOM TEMP ");
			lcd_voidSendNumber(&TEMP_READ);
			LCD_voidSetCursor(1,1);
			LCD_voidWriteString("FAN SPEED ");
			if (TEMP_READ<=20)
			{
				LCD_voidWriteString("OFF");
				TIMER2_voidSetCTC(0);				
			}			
			else if (20<TEMP_READ&&TEMP_READ<=30)
			{
				LCD_voidWriteString("50%");
				TIMER2_voidSetCTC(128);				
			}
			else if (30<TEMP_READ&&TEMP_READ<=35)
			{
				LCD_voidWriteString("75%");
				TIMER2_voidSetCTC(200);					
			}
			else if (TEMP_READ>35)
			{
				LCD_voidWriteString("100%");
			    TIMER2_voidSetCTC(255);	
			}
			Last_Temp_Read=TEMP_READ;	
		  }
			TempFlag=0;

		vTaskDelay(1000);		
	}
}
void TempNotificatonRead(u16 local_tempread)
{
	xSemaphoreGive(TEMPSemaphore);
	local_tempread=(local_tempread*500)/1023;
	TEMP_READ=local_tempread;
	TempFlag=1;
}