#ifndef LCD_H_
#define LCD_H_

#include "main.h"
//-----------------
 void sendhalfbyte (unsigned char c);
 void LCD_ini(void);
 void LCD_SetPos(unsigned char x, unsigned y);
 void LCD_String (char *str1);
 void LCD_Clear(void);
 void LCD_Sendchar(unsigned char c);
 //--------------------
  #define e1 I2C_SendByteByADDR(portlcd|=0x04,0b01001110) // установка линии E в 1
  #define e0 I2C_SendByteByADDR(portlcd&=~0x04,0b01001110) // установка линии E в 0
  #define rs1 I2C_SendByteByADDR(portlcd|=0x01,0b01001110) // установка линии RS в 1
  #define rs0 I2C_SendByteByADDR(portlcd&=~0x01,0b01001110) // установка линии RS в 0
  #define setled() I2C_SendByteByADDR(portlcd|=0b00001000,0b01001110) // включение подсветки
  //#define setled() I2C_SendByteByADDR(portlcd&=~0b00001000,0b01001110) // выключение подсветки
  #define setwrite() I2C_SendByteByADDR(portlcd&=~0x02,0b01001110) // установка записи в память дисплея
  
#endif /* LCD_H_ */