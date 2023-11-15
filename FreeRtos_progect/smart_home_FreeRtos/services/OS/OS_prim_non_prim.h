#define 		NULL 					(0)
u8 Task1_flag_ARR[NUM_OF_TASKS]={0};
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
	static u8 Local_u8TaskCounter;
//	for(Local_u8TaskCounter=0;Local_u8TaskCounter<NUM_OF_TASKS;Local_u8TaskCounter++)
//	{
switch(os_moode)
case PEEMATIVE:		
		for (u8 i=0;i<NUM_OF_TASKS;i++)
		{
		while (OStasks[Local_u8TaskCounter].state==READY)
		{
			if (OStasks[Local_u8TaskCounter].first_delay==0)
			{
				OStasks[Local_u8TaskCounter].first_delay=OStasks[Local_u8TaskCounter].Period;
				for (u8 i=0;i<3;i++)
				{
				  OStasks[Local_u8TaskCounter].TASK_ROUTINE();
				}
				Task1_flag_ARR[Local_u8TaskCounter]=1;				
			}			
			else
			{
				OStasks[Local_u8TaskCounter].first_delay--;
				Local_u8TaskCounter++;
			}
			if (Task1_flag_ARR[Local_u8TaskCounter]==1)
			{
				Task1_flag_ARR[Local_u8TaskCounter]=0;
				Local_u8TaskCounter++;
			}
		}
		else
		{
			
		}
		}
	}
	
case PEEMATIVE:		
	//	TIMER1_voidSetPreload(250);
	TIMER0_SET_COUNTER(247);
}

#endif
