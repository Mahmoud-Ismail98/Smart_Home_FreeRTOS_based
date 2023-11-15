/*
 * WDT.h
 *
 * Created: 30/10/2023 01:11:49 ص
 *  Author: mkora
 */ 


#ifndef WDT_H_
#define WDT_H_


#define TIMEOUT_16_3_MS		0
#define TIMEOUT_32_5_MS		1
#define TIMEOUT_65_MS		2
#define TIMEOUT_0_13_S		3
#define TIMEOUT_0_26_S		4
#define TIMEOUT_0_52_S		5
#define TIMEOUT_1_0_S		6
#define TIMEOUT_2_1_S		7


void WDT_voidEnable(void);
void WDT_voidDisable(void);
void WDT_voidSleep(u8 Copy_u8SleepTimeOut);




#endif /* WDT_H_ */