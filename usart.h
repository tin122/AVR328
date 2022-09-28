#ifndef USART_H_
#define USART_H_

#include "main.h"
#include "lcdtwi.h"
#include "twi.h"
#include "lcdtwi.h"

volatile unsigned char U_buff; // бужер приема сообщений

void USART_Init(unsigned int ubrr);
void USART_Transmit (unsigned int data);
void USART_Read ();

#endif /* USART_H_ */