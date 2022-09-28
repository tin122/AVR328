#include "usart.h"

void USART_Init(unsigned int ubrr)
{
	UBRR0H=(unsigned char)(ubrr>>8);
	UBRR0L=(unsigned char)ubrr;
	
	UCSR0B=(1<<RXEN0)|(1<<TXEN0); //��� ��������������
	UCSR0B|=(1<<RXCIE0); //������. ���������� ��� ��������
	//UCSR0A |= (1<<U2X0);
	UCSR0C=(1<<UCSZ00)|(1<<UCSZ01)|(1<<USBS0); 
	//8-��� ������� (UCSZ01=1 � UCSZ00=1)
	//1 ����-���/ 2 ����-���� (USBS=0)
	// ��������. ����� (UMSELn1=0, UMSELn0=0)
	//UCSRC |= (1<<UPM1) // ��� �������� �������� (UPM1=0 � UPM0=0), 
}

void USART_Transmit (unsigned int data)
{
	while ( !(UCSR0A&(1<<UDRE0)) ); //������� ����������� ������ ������
	{
		UDR0=data; //Data register ������ �������� ������
	}
}

void USART_Read ()
{
	while(UCSR0A & (1 << RXC0)) // RXC0 = 0 - ����� ����, ��� ������� UDR0 ���������
	{
		U_buff = UDR0;
	}
}