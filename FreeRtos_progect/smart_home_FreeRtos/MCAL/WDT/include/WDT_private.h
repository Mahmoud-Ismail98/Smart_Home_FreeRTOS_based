/*
 * WDT_private.h
 *
 * Created: 30/10/2023 01:10:53 ص
 *  Author: mkora
 */ 


#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

#define		WDTCR			*((volatile u8 *)(0x41))			// Watchdog Timer Control Register
#define 	WDTCR_WDP0		0									// Watchdog Timer Prescaler 0
#define 	WDTCR_WDP1		1									// Watchdog Timer Prescaler 1
#define 	WDTCR_WDP2		2									// Watchdog Timer Prescaler 2
#define 	WDTCR_WDE		3									// Watchdog Timer Enable
#define 	WDTCR_WDTOE		4									// Watchdog Timer Turn-off Enable




#endif /* WDT_PRIVATE_H_ */