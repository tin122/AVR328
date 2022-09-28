#include "lcdtwi.h"
//----------------
unsigned char portlcd = 0; //ячейка для хранения данных порта микросхемы расширения 

void sendhalfbyte (unsigned char c)
{
	c<<=4;
	e1; //вкл линию E
	//_delay_us(1);
	I2C_SendByteByADDR(portlcd|c,0b01001110);
	e0; //выкл линию Е
	//_delay_us(1);
}
//--------------------

void sendbyte(unsigned char c, unsigned char mode)
{
	if (mode==0) rs0; //команды 
	else rs1;//данные	
	unsigned char hc=0;
	hc=c>>4;
	
	sendhalfbyte(hc);
	sendhalfbyte(c);
}
//--------------------

void LCD_Sendchar (unsigned char c)// передача данных
{
	//_delay_us(40);
	sendbyte(c,1);
	//_delay_ms(1);
}
//---------------------
void LCD_SetPos (unsigned char x, unsigned y)
{
	switch(y)
	{
		case 0:
		 sendbyte(x|0x80,0);
		 break;
		case 1:
		 sendbyte((0x40+x)|0x80,0);
		 break;
	}
}
//---------------------
void LCD_ini(void) //------------ на время debug
{
	  setwrite();
	  //_delay_ms(100);
	  sendhalfbyte(0b00000011);
	  //_delay_us(4500);
	  sendhalfbyte(0b00000011);
	 // _delay_us(4500);
	  sendhalfbyte(0b00000011);
	 // _delay_us(4500);
	  sendhalfbyte(0b00000010);
	  sendbyte(0x28,0);//режим 4 бит, 2 линии (для нашего большого дисплея это 4 линии, шрифт 5х8
	  sendbyte(0x08,0);//дисплей пока выключаем
	 // _delay_us(1000);
	  sendbyte(0x01,0);//уберем мусор
	 // _delay_us(2000);
	  sendbyte(0x06,0);//пишем вправо
	  //_delay_us(1000);
	  sendbyte(0x0C,0);//дисплей включаем (D=1), курсоры никакие не нужны
	  sendbyte(0x02,0);//курсор на место
	  sendbyte(0X80,0);//SET POS LINE 0
	 // _delay_us(2000);
	  setled();//подсветка
	/* //1602
	 		_delay_ms(15); //Ждем 15 мс (стр 45)
			sendhalfbyte(0b00000011);
			_delay_ms(4);
			sendhalfbyte(0b00000011);
			_delay_us(100);
			sendhalfbyte(0b00000011);
		 	_delay_ms(1);
	 		sendhalfbyte(0b00000010);
	 		_delay_ms(1);
		 	sendbyte(0b00101000, 0); //4бит-режим (DL=0) и 2 линии (N=1)
	 		_delay_ms(1);
	 		sendbyte(0b00001100, 0); //включаем изображение на дисплее (D=1), курсоры никакие не включаем (C=0, B=0)
	 		_delay_ms(1);
	 		sendbyte(0b00000110, 0); //курсор (хоть он у нас и невидимый) будет двигаться влево
	 		_delay_ms(1);
	setled();//подсветка
	setwrite();//запись
	*/
}
//--------------------
void LCD_Clear(void)
{
	sendbyte(0b00000001, 0);
	//_delay_us(1500);
}
//--------------------
void LCD_String (char *str1)
{
	unsigned char i=0;
	while (str1[i]!=0)
	{
		sendbyte(str1[i],1);
		i++;
	}
}
//--------------------
