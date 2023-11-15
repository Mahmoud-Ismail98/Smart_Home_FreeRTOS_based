/*
 * WDT.c
 *
 * Created: 30/10/2023 01:12:06 ص
 *  Author: mkora
 */ 
#include "../../../services/Bit_utils.h"
#include "../../../services/Std_types.h"

#include "../../../MCAL/WDT/include/WDT_private.h"
#include "../../../MCAL/WDT/include/WDT.h"

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR, WDTCR_WDE);
}
void WDT_voidDisable(void)
{
	/*Set WDTOE Watchdog Turn-off Enable  and WDE in the same operation*/
	WDTCR = (1 << WDTCR_WDTOE) | (1 << WDTCR_WDE);
	/*Within The Next Four Clock Cycles, Write Logic 0 to WDE*/
	WDTCR = 0x00;
}

void WDT_voidSleep(u8 Copy_u8SleepTimeOut)
{
	if(Copy_u8SleepTimeOut < 8)
	{
		WDTCR &= 0xFB;
		WDTCR |= Copy_u8SleepTimeOut;
	}
	else
	{
		//Do Nothing
	}
}