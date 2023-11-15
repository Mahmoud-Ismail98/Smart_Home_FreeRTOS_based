#ifndef OS_PRIVATE_H_
#define OS_PRIVATE_H_


#define 		NULL 					(0)
typedef struct
{
	u16 Period;
	void (*TASK_ROUTINE)(void);
	u16 first_delay; 
	u8 state;
}Task;

static Task OStasks[NUM_OF_TASKS] = {NULL};
	
static void SCHEDULER(void)
{
static u32 counter_time=0;
	u8 Local_u8TaskCounter;
		for(Local_u8TaskCounter=0;Local_u8TaskCounter<NUM_OF_TASKS;Local_u8TaskCounter++)
		{
		 if (OStasks[Local_u8TaskCounter].state==READY)
		 {
		// OStasks[Local_u8TaskCounter].Period%counter_time=0;		 		 	
			if (OStasks[Local_u8TaskCounter].first_delay==0)
			{
				    OStasks[Local_u8TaskCounter].first_delay=OStasks[Local_u8TaskCounter].Period;
					OStasks[Local_u8TaskCounter].TASK_ROUTINE();
			}
			else
			{
			OStasks[Local_u8TaskCounter].first_delay--;
			}
		 }
		 else 
		 {
			 
		 }	
		 }
	//	TIMER1_voidSetPreload(250);	
		TIMER0_SET_COUNTER(247);
}

#endif
