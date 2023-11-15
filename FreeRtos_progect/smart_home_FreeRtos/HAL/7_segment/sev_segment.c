#include "../../services/Bit_utils.h"
#include "../../services/Std_types.h"
#include "../../MCAL/PORT/include/port_private.h"
#include "../../MCAL/DIO/include/DIO.h"
#include "../../MCAL/PORT/include/port.h"
#include "../../HAL/7_segment/sev_segment_config.h"
#include "../../HAL/7_segment/seven_segment.h"
#include	<util/delay.h>


seven_segment_pin * ARR_SEV_SEG[4];
seven_segment_pin	sven_seg1={PORTA_PIN0,PORTA_PIN1,PORTA_PIN2,PORTA_PIN3};
seven_segment_pin	sven_seg2={PORTA_PIN4,PORTA_PIN5,PORTA_PIN6,PORTA_PIN7};
seven_segment_pin	sven_seg3={PORTB_PIN0,PORTB_PIN1,PORTB_PIN2,PORTB_PIN3};
seven_segment_pin	sven_seg4={PORTB_PIN4,PORTB_PIN5,PORTB_PIN6,PORTB_PIN7};	
	

void init_four_sev_Seg(void)
{
	ARR_SEV_SEG[0]=&sven_seg1;
	ARR_SEV_SEG[1]=&sven_seg2;
	ARR_SEV_SEG[2]=&sven_seg3;
	ARR_SEV_SEG[3]=&sven_seg4;
	Sev_SegmentInit(ARR_SEV_SEG[0]);
	Sev_SegmentInit(ARR_SEV_SEG[1]);
	Sev_SegmentInit(ARR_SEV_SEG[2]);
	Sev_SegmentInit(ARR_SEV_SEG[3]);	
}
void Sev_SegmentInit(seven_segment_pin* sev_seg)
{		
	Port_setPinDirection(sev_seg->Sev_SegPinA,PIN_OUTPUT);
	Port_setPinDirection(sev_seg->Sev_SegPinB,PIN_OUTPUT);
	Port_setPinDirection(sev_seg->Sev_SegPinC,PIN_OUTPUT);
	Port_setPinDirection(sev_seg->Sev_SegPinD,PIN_OUTPUT);
	_delay_ms(10);
}
/*
void Sev_SegmentInit(seven_segment_pin* sev_seg,u8 number_segment)
{
	for (u8	i=0,i<number_segment;i++)
	{
			Port_setPinDirection(sev_seg->Sev_SegPinA,PIN_OUTPUT);
			Port_setPinDirection(sev_seg->Sev_SegPinB,PIN_OUTPUT);
			Port_setPinDirection(sev_seg->Sev_SegPinC,PIN_OUTPUT);
			Port_setPinDirection(sev_seg->Sev_SegPinD,PIN_OUTPUT);
	}

}*/
void Sev_SegmentShow(u8 val,seven_segment_pin* sev_seg)
{
	DIO_WritrPin(sev_seg->Sev_SegPinA,GET_BIT(val,0));
	DIO_WritrPin(sev_seg->Sev_SegPinB,GET_BIT(val,1));
	DIO_WritrPin(sev_seg->Sev_SegPinC,GET_BIT(val,2));
	DIO_WritrPin(sev_seg->Sev_SegPinD,GET_BIT(val,3));
	_delay_ms(30);
}

void Sev_SegmentCounter_up(u16 counter_value)
{
u8 SEVEN_SEGArray[numbe_seven_Segment]={0};	
for (u32 count=counter_value;count <10000;count++)
{
	u32 loc_var =count;
	if (loc_var>=1000)
	{
		SEVEN_SEGArray[0]=loc_var/1000;
		loc_var%=1000;
	}
	else
	{
		SEVEN_SEGArray[0]=loc_var/1000;
	}
	if (loc_var>100)
	{
		SEVEN_SEGArray[1]=loc_var/100;
		loc_var%=100;
	}
	else{SEVEN_SEGArray[1]=loc_var/100;}
	SEVEN_SEGArray[2]=loc_var/10;
	SEVEN_SEGArray[3]=loc_var%10;
	for (u8 i=0;i<numbe_seven_Segment;i++)
	{
		Sev_SegmentShow(SEVEN_SEGArray[i],ARR_SEV_SEG[i]);
	}
	
}

}
void sev_seg_stop_watch(void)	
{

		Port_SetPinMode(START_PUTTON_PIN,PIN_IN_PULLUP);
		Port_SetPinMode(CLEAR_PUTTON_PIN,PIN_IN_PULLUP);
		Port_SetPinMode(STOP_PUTTON_PIN,PIN_IN_PULLUP);
		u8 SEVEN_SEGArray[numbe_seven_Segment]={0};	
		u32 count=0;
		u32 loc_var =count;
		u8 start_put_read=1;
		u8 clear_put_read=1;
		u8 stop_put_read=1;
while (1)
{

	DIO_READ_PIN(START_PUTTON_PIN,&start_put_read);
	DIO_READ_PIN(STOP_PUTTON_PIN,&stop_put_read);
	DIO_READ_PIN(CLEAR_PUTTON_PIN,&clear_put_read);			
	while (start_put_read==0 & stop_put_read==1 & clear_put_read==1)
	{
		loc_var=count;	
		if (loc_var>=1000)
		{
			SEVEN_SEGArray[0]=loc_var/1000;
			loc_var%=1000;
		}
		else
		{
			SEVEN_SEGArray[0]=0;
		}
		if (loc_var>=100)
		{
			SEVEN_SEGArray[1]=loc_var/100;
			loc_var%=100;
		}
		else
		{
			SEVEN_SEGArray[1]=0;
		}
		SEVEN_SEGArray[2]=loc_var/10;
		SEVEN_SEGArray[3]=loc_var%10;
		for (u8 i=0;i<numbe_seven_Segment;i++)
		{
			Sev_SegmentShow(SEVEN_SEGArray[i],ARR_SEV_SEG[i]);
		}
	   DIO_READ_PIN(CLEAR_PUTTON_PIN,&clear_put_read);
	   DIO_READ_PIN(STOP_PUTTON_PIN,&stop_put_read);
	   count++;	  			
    }
  if (clear_put_read==0)
   {
	SEVEN_SEGArray[0]=0;
	SEVEN_SEGArray[1]=0;
	SEVEN_SEGArray[2]=0;
	SEVEN_SEGArray[3]=0;
	count=0;
	for (u8 i=0;i<numbe_seven_Segment;i++)
	{
		Sev_SegmentShow(SEVEN_SEGArray[i],ARR_SEV_SEG[i]);
	}
  }
  //else if()
 }
}