
#include "../../services/Bit_utils.h"
#include "../../services/Std_types.h"

#include "../../MCAL/TIMER/timer_interface.h"
#include "../../MCAL/TIMER0/include/TIMER0_Interface.h"

#include "OS_interface.h"
#include "OS_config.h"
#include "OS_private.h"


void OS_voidCreateTask(u8 Copy_u8TaskID,u16 period,void (*ptr)(void),u8 state,u8 first_delay)
{
	
	OStasks[Copy_u8TaskID].Period = period;
	OStasks[Copy_u8TaskID].TASK_ROUTINE = ptr;
	OStasks[Copy_u8TaskID].state = state;	
	OStasks[Copy_u8TaskID].first_delay = first_delay;		
	
}

void OS_voidStart(void)
{
//	TIMER1_voidInit() ;
	TIMER0_voidMode();
	TIMER0_SET_COUNTER(247);
	Timer0SetCallBack(SCHEDULER);
	Timer0_EnableInterupt();
//	TIMER1_voidSetPreload(250);
//	TIMER_u8SetCallBack(SCHEDULER,TIMER1_OVF_VECTOR_ID);
}

void OS_voidSuspendTask(u8 Copy_u8TaskID)
{
	OStasks[Copy_u8TaskID].state = SUSPEND;
}

void OS_voidDeletTask(u8 Copy_u8TaskID)
{
	OStasks[Copy_u8TaskID].state = DELETED;
}

void OS_voidResumeTask(u8 Copy_u8TaskID)
{
	OStasks[Copy_u8TaskID].state = READY;
}