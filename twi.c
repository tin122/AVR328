#include "twi.h"

unsigned char timer;

void I2C_Init(void)
{
	TWBR=0x48; //скорость передачи 100к√ц
}

void I2C_StartCondition(void) // —тарт
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //TWIE Ц бит, который разрешает прерывани€
	//while(!(TWCR&(1<<TWINT)));//подождем пока установитс€ TWIN
	timer=0;
	while (!(TWCR & (1<<TWINT))&&timer<255)timer++; //ждем
}

void I2C_StopCondition(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(TWEN);	
}


void I2C_SendByte(unsigned char c)
{
	TWDR=c; //запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу байта
	//while (!(TWCR & (1<<TWINT)));//подождем пока установитс€ TWIN
	timer=0;
	while (!(TWCR & (1<<TWINT))&&timer<255)timer++; //ждем
}

 void I2C_SendByteByADDR(unsigned char c,unsigned char addr)
 {
	 I2C_StartCondition(); // ќтправим условие START
	 I2C_SendByte(addr); // ќтправим в шину адрес устройства + бит чтени€-записи
	 I2C_SendByte(c);// ќтправим байт данных
	 I2C_StopCondition();// ќтправим условие STOP
 }