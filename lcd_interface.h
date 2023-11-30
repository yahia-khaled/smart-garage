
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include"std_types.h"

void lcd_writedata(u8 data);
void lcd_sendcommand(u8 inst);
void lcd_initialisation();
void lcd_string(u8 name[]);
void lcd_number(int x);
void Lcd8_Set_Cursor(char line, char col);
void GoToPos(u8 row ,u8 col);
u8 StrLen (u8*arr);

#endif
