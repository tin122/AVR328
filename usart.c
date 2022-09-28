#include "usart.h"

void USART_Init(unsigned int ubrr)
{
	UBRR0H=(unsigned char)(ubrr>>8);
	UBRR0L=(unsigned char)ubrr;
	
	UCSR0B=(1<<RXEN0)|(1<<TXEN0); //вкл приемопередачу
	UCSR0B|=(1<<RXCIE0); //разреш. прерывание при передаче
	//UCSR0A |= (1<<U2X0);
	UCSR0C=(1<<UCSZ00)|(1<<UCSZ01)|(1<<USBS0); 
	//8-бит посылка (UCSZ01=1 и UCSZ00=1)
	//1 стоп-бит/ 2 стоп-бита (USBS=0)
	// асинхрон. режим (UMSELn1=0, UMSELn0=0)
	//UCSRC |= (1<<UPM1) // без контроля четности (UPM1=0 и UPM0=0), 
}

void USART_Transmit (unsigned int data)
{
	while ( !(UCSR0A&(1<<UDRE0)) ); //Ожидаем опустошение буфера приема
	{
		UDR0=data; //Data register Начало передачи данных
	}
}

void USART_Read ()
{
	while(UCSR0A & (1 << RXC0)) // RXC0 = 0 - после того, как регистр UDR0 опустошен
	{
		U_buff = UDR0;
	}
}