void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_SendString(char* str);
void LCD_Init(void);
void LCD_set_cursor(uint32_t row, uint32_t column);
void LCD_Light_BackGround(uint8_t State);

#include <lcd16x2.c>