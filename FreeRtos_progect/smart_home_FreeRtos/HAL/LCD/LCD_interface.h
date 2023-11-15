
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_voidInit(void);
void LCD_voidWriteCharacter(u8 Character);
void LCD_voidSendCommand(u8 Command);
void LCD_voidWriteString(u8 *string);

void LCD_voidSetCursor(u8 a, u8 b);
void LCD_voidClear(void);
void LCD_voidCustomChar (unsigned char loc, unsigned char *msg);
void Lcd_voidShiftRight(void);
void Lcd_voidShiftLeft(void);

void lcd_voidSendNumber   ( u16 *Copynum);
#endif 
