#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

void TIMER0_voidMode(void);
void TIMER0_voidCOModeNonPwm(void);
void TIMER0_voidCOModeFastPwm(void);
void TIMER0_voidCOMPhaseCorrectPWM(void);
void TIMER0_voidClockSelect(void);
void TIMER_GETTIMERCOUNT_VAL(u16 *copy_counter_val);
void TIMER0_SET_COUNTER(u8 COUNT);

void Timer0_EnableInterupt(void);
void Timer0_DisableInterupt(void);
void  Timer0SetCallBack(void(*capy_pf)(void));

void TIMER_setValMs(u16 value_ms);
//void T0delayOnems(void);
void T0delayms(int n);

#endif /* TIMER0_INTERFACE_H_ */
