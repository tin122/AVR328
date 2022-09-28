#include "twi.h"

unsigned char timer;

void I2C_Init(void)
{
	TWBR=0x48; //�������� �������� 100���
}

void I2C_StartCondition(void) // �����
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //TWIE � ���, ������� ��������� ����������
	//while(!(TWCR&(1<<TWINT)));//�������� ���� ����������� TWIN
	timer=0;
	while (!(TWCR & (1<<TWINT))&&timer<255)timer++; //����
}

void I2C_StopCondition(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(TWEN);	
}


void I2C_SendByte(unsigned char c)
{
	TWDR=c; //������� ���� � ������� ������
	TWCR = (1<<TWINT)|(1<<TWEN);//������� �������� �����
	//while (!(TWCR & (1<<TWINT)));//�������� ���� ����������� TWIN
	timer=0;
	while (!(TWCR & (1<<TWINT))&&timer<255)timer++; //����
}

 void I2C_SendByteByADDR(unsigned char c,unsigned char addr)
 {
	 I2C_StartCondition(); // �������� ������� START
	 I2C_SendByte(addr); // �������� � ���� ����� ���������� + ��� ������-������
	 I2C_SendByte(c);// �������� ���� ������
	 I2C_StopCondition();// �������� ������� STOP
 }