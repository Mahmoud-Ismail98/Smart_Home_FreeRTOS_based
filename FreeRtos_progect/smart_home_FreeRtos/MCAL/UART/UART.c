#include "../../services/Bit_utils.h"
#include "../../services/Std_types.h"
#include "../../MCAL/PORT/include/port.h"
//#include "../MCAL/UART/UART.h"
//#include "../MCAL/UART/UART_Lcfg.h"
#include "UART.h"
#include "UART_Lcfg.h"
//#include "LCD.h"
 /****************************Pointer to functions to be assigned to ISR*********************************/

static void (*UART_RX_Fptr) (void);
static void (*UART_TX_Fptr) (void);


/********************************************initialization **********************************************/

/************************* Array of  UBRR values ***************************/
const u16 BaudRateArray[TOTAL_SPEED_MODE][TOTAL_CPU_F][TOTAL_BAUD_RATE]=
		 {{{103, 51, 25, 16, 12,  8},{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34}},
		  {{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34},{832,416,207,138,103, 68}}};
									
void UART_Init(void)
{ 
	u8  UCSRC_var=0;
	u16 UBRR_var=0; 
/***************************** transmission speed***************************/
	#if (SPEED_MODE==NORMAL_SPEED)
	CLR_BIT(UCSRA,U2X);
	#elif (SPEED_MODE==DOUBLE_SPEED)
	SET_BIT(UCSRA,U2X);
	#endif

//******************set URSEL to write data to UCSRC register***************/ 
   SET_BIT(UCSRC_var,URSEL);
 
//********************************synch***********************************/
	 #if (SYNCH_MODE==SYNCH)
	 SET_BIT(UCSRC_var,URSEL)
	 #elif (SYNCH_MODE==ASYNCH)
 	 CLR_BIT(UCSRC_var,URSEL);
	 #endif
 //*****************************parity mode*******************************/
	
	#if (PARITY_MODE==NO_PARITY)
	CLR_BIT(UCSRC_var,UPM0);
	CLR_BIT(UCSRC_var,UPM1);
	#elif (PARITY_MODE==EVEN_PARITY)
	CLR_BIT(UCSRC_var,UPM0);
	SET_BIT(UCSRC_var,UPM1);
	#elif (PARITY_MODE==ODD_PARITY)
	SET_BIT(UCSRC_var,UPM0);
	SET_BIT(UCSRC_var,UPM1);
	#endif
//************************Data bits*******************************/	
	#if (N_DATA_BITS==_5_DATA_BITS)
	CLR_BIT(UCSRC_var,UCSZ0);
	CLR_BIT(UCSRC_var,UCSZ1);
	CLR_BIT(UCSRC_var,UCSZ2);
	#elif (N_DATA_BITS==_6_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	CLR_BIT(UCSRC_var,UCSZ1);
	CLR_BIT(UCSRC_var,UCSZ2);
    #elif (N_DATA_BITS==_7_DATA_BITS)
    CLR_BIT(UCSRC_var,UCSZ0);
    SET_BIT(UCSRC_var,UCSZ1);
    CLR_BIT(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_8_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_9_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	SET_BIT(UCSRB,UCSZ2);
	#endif
//************************Stop bits*******************************/	
	#if (N_STOP_BITS==ONE_STOP_BIT)
	CLR_BIT(UCSRC_var,USBS);
	#elif (N_STOP_BITS==TWO_STOP_BIT)
	SET_BIT(UCSRC_var,USBS);
	#endif
//*****************set UCSRC value   *******************************/	
	UCSRC=UCSRC_var;

//************************Baud rate *******************************/	

    UBRR_var=BaudRateArray[SPEED_MODE][CPU_F][BUAD_RATE];
	UBRRH = (u8)(UBRR_var>>8);
	UBRRL = (u8)UBRR_var;
	
//************************Enable  *******************************/		
//enable UART  receiver.
SET_BIT(UCSRB,RXEN);
//enable UART  transmitter .
SET_BIT(UCSRB,TXEN);
}
/*
void UART_Init(void)
{
	// transmission speed
	CLR_BIT(UCSRA,U2X);

	//enable UART  receiver.
	SET_BIT(UCSRB,RXEN);

	//enable UART  transmitter .
	SET_BIT(UCSRB,TXEN);

	//B- Bit data
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);

	//Async
	CLR_BIT(UCSRC,UMSEL);
	//NO parity
	CLR_BIT(UCSRC,UPM0);
	CLR_BIT(UCSRC,UPM1);
	// One stop bit
	CLR_BIT(UCSRC,USBS);


	
	UBRRH = 0;
	UBRRL = 51;
}
*/


/*****************************************Interrupt functions*********************************************/


 void UART_RX_InterruptEnable(void) 
{
	SET_BIT(UCSRB,RXCIE);
}

 void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

 void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

 void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}
/*****************************************Set Call Back Functions*********************************************/	
 void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

 void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}
/***********************************************ISR ************************************************************/
void __vector_13 (void)	__attribute__((signal)) ;
void __vector_13 (void)
{
	if (UART_RX_Fptr!=NULL)
	{
		UART_RX_Fptr();
	}
}

void __vector_15 (void)	__attribute__((signal)) ;
void __vector_15 (void)
{
	if (UART_TX_Fptr!=NULL)
	{
		UART_TX_Fptr();
	}
}


/****************************************Send and receive functions with no ckecking********************************/

void UART_SendByteNoBlock(u8 data)
{
	UDR = data;
}

u8 UART_ReceiveByteNoBlock(void)
{
    return UDR;
}
/****************************************Send and receive functions with polling     ********************************/
void UART_SendByte(u8 data)
{
	/*UDRE flag is set when the buffer is empty and ready
	for transmitting a new byte so wait until this flag is set to one 
	and it will cleared by hardware when u write  new data to puffer.*/
	while(!(GET_BIT(UCSRA,UDRE)));  
	UDR = data;
}

u8 UART_ReceiveByte(void)
{
	/*RXC flag is set when the UART receive data so  wait until this flag is set to one
	and it will cleared by hardware when u read the data*/
	while(!(GET_BIT(UCSRA,RXC)));  
    return UDR;
}



u8 UART_Receive_NoBlock(u8*pdata)
{
	u8 status=0;
	if(GET_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		status=1;
	}
	else
	{	status=0;
	}
return status;
}

void UART_SendString(u8 *Str)  //syncrounous
{
	u8 i=0;
	while(Str[i]!='\0')
	{
		UART_SendByte(Str[i]);
		i++;
	}

}

void UART_ReceiveString(u8 *str)
{

	u8 i=0;
	str[i]=UART_ReceiveByte();	
	while (str[i]!=0x0D)
	{
		i++;
		str[i]=UART_ReceiveByte();
	}
	str[i]='\0';
	
}








