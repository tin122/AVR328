#include "lcdtwi.h"
//----------------
unsigned char portlcd = 0; //������ ��� �������� ������ ����� ���������� ���������� 

void sendhalfbyte (unsigned char c)
{
	c<<=4;
	e1; //��� ����� E
	//_delay_us(1);
	I2C_SendByteByADDR(portlcd|c,0b01001110);
	e0; //���� ����� �
	//_delay_us(1);
}
//--------------------

void sendbyte(unsigned char c, unsigned char mode)
{
	if (mode==0) rs0; //������� 
	else rs1;//������	
	unsigned char hc=0;
	hc=c>>4;
	
	sendhalfbyte(hc);
	sendhalfbyte(c);
}
//--------------------

void LCD_Sendchar (unsigned char c)// �������� ������
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
void LCD_ini(void) //------------ �� ����� debug
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
	  sendbyte(0x28,0);//����� 4 ���, 2 ����� (��� ������ �������� ������� ��� 4 �����, ����� 5�8
	  sendbyte(0x08,0);//������� ���� ���������
	 // _delay_us(1000);
	  sendbyte(0x01,0);//������ �����
	 // _delay_us(2000);
	  sendbyte(0x06,0);//����� ������
	  //_delay_us(1000);
	  sendbyte(0x0C,0);//������� �������� (D=1), ������� ������� �� �����
	  sendbyte(0x02,0);//������ �� �����
	  sendbyte(0X80,0);//SET POS LINE 0
	 // _delay_us(2000);
	  setled();//���������
	/* //1602
	 		_delay_ms(15); //���� 15 �� (��� 45)
			sendhalfbyte(0b00000011);
			_delay_ms(4);
			sendhalfbyte(0b00000011);
			_delay_us(100);
			sendhalfbyte(0b00000011);
		 	_delay_ms(1);
	 		sendhalfbyte(0b00000010);
	 		_delay_ms(1);
		 	sendbyte(0b00101000, 0); //4���-����� (DL=0) � 2 ����� (N=1)
	 		_delay_ms(1);
	 		sendbyte(0b00001100, 0); //�������� ����������� �� ������� (D=1), ������� ������� �� �������� (C=0, B=0)
	 		_delay_ms(1);
	 		sendbyte(0b00000110, 0); //������ (���� �� � ��� � ���������) ����� ��������� �����
	 		_delay_ms(1);
	setled();//���������
	setwrite();//������
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
