#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcdtwi.h"
#include "twi.h"
#include "usart.h"

void USART_Init(unsigned int ubrr);
void USART_Transmit (unsigned int data);

#endif /* MAIN_H_ */