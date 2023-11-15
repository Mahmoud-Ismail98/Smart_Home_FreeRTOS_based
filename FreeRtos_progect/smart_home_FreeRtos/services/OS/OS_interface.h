
#ifndef OS_INTERFACE_H_
#define OS_INTERFACE_H_

#define READY  1
#define SUSPEND 2
#define DELETED 3
#define NON_PEEMATIVE 4 
#define PEEMATIVE    5

void OS_voidCreateTask(u8 Copy_u8TaskID,u16 period,void (*ptr)(void),u8 state,u8 first_delay);
void OS_voidStart(void);
void OS_voidDeletTask(u8 Copy_u8TaskID);
void OS_voidSuspendTask(u8 Copy_u8TaskID);
void OS_voidResumeTask(u8 Copy_u8TaskID);

#endif /* OS_H_ */
