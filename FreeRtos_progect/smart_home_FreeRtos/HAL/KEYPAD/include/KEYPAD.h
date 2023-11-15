

#ifndef KEYPAD_H
#define KEYPAD_H



typedef enum{
	KEYPAD_ERROR_FREE,
	NO_KEY_PRESSED
}ERROR_KEYPAD_STATUS;

void KEYPAD_voidInit(void);
ERROR_KEYPAD_STATUS KEYPAD_FindKey(u8 *Loc_keyPress);
void KEYPAD_ReadPins(u8 *value);
void KEYPAD_WritrPin(u8 value);



#endif 
