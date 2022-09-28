#include "main.h"

//-------------------------------------------------------

//volatile unsigned char cnt=0;
volatile signed short cnt=0;
volatile unsigned char r2r=0, r2r_d=0, r2r_b=0;

//unsigned char x=0, y=0; //-��� ���������� USART

//////////////////////////////////////////////////////////////////////////
void port_ini(void)  
{
	//R - R2R; L-LED; E - �������: SW � PD2 (D2), DT � PD3 (D3), CLK � PD4 (D4).
	DDRD  = 0b11100000; //RRREEE(Tx)(Rx)
	PORTD = 0b00000000;
	PORTD|= (1 << 2); //����������� ��� ��������
	
	DDRB  = 0b00111111; //--LRRRRR
	PORTB = 0b00000000;
	PORTB &= ~ (1 << 5); //��������� ��������� PORTB|= (1 << 5); //�������� ���������=)
		
	//r2r_d = (PIND & 0b11100000);
	//r2r_b = (PINB & 0b00011111);
		
}

void timer_ini(void)
{
	OCR1A = 25; //�������� � 100 ����������� (10 ���) ��� 16 ���
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11) | (1 << CS10); //��� 10 ���
	TIMSK1 |= (1 << OCIE1A);
}

////////////////////////////////////////////////////////////////////////////////////////
ISR (TIMER1_COMPA_vect)
{
	static unsigned char new_state=0;
	static unsigned char old_state=0;
	new_state = (PIND&0b00011000)>>3;
	if(!(PIND&0b00000100)) cnt=0; //�������� ������� ������
	switch(old_state|new_state)
	{
		case 0x01: case 0x0e:
		cnt++;
		break;
		case 0x04: case 0x0b:
		cnt--;
		break;
	}
	
	old_state = new_state<<2;
	if (!(cnt < 511 && cnt >= 0)) cnt = 0;
}


ISR(USART_RX_vect) // ������ � ����������� �� ������. ���������� ����� - 8 ���.
{
		USART_Read();
		USART_Transmit (U_buff);
}

//////////////////////////////////////////////////////////////////////////
int main(void)
{
	
	short cnt_local = 0;
	short cnt_local_old = -1;
	char str1[16];
	
	//-----------------------		
	port_ini();
	//-----------------------
	cli();
	USART_Init (8); //8-115200(U2X=0)
	asm("nop");
	//---------------------
	I2C_Init();
	//---------------------
	LCD_ini();
	LCD_Clear();
	//LCD_SetPos(0,0);
	//LCD_Sendchar('!');
	//---------------------
	timer_ini();
	sei();
	//---------------------
	
	while (1)
	{
		cli();
		cnt_local=cnt/2;
		sei();
		
		if(cnt_local != cnt_local_old)
		{
			LCD_SetPos(0,0);
			sprintf(str1, "%4d", cnt_local);
			LCD_String(str1);
			cnt_local_old = cnt_local;
			
			//--�������������
			
			PORTB =(cnt_local & 0b00011111);
			PORTD =(cnt_local & 0b11100000);
			
			//---������ ������ ����
			r2r_b = (PINB & 0b00011111); 
			r2r_d = (PIND & 0b11100000);	
			r2r   = (r2r_d | r2r_b);
					
			USART_Transmit(r2r);
			
		}
		_delay_ms(10);
		
		//-------------- ������������� ���� �� r2r
		//PORTB = (r2r_bits & 0b00011111); //DDRB = 0b00011111; ---RRRRR
		//PORTD = (r2r_bits & 0b11100000); //DDRD = 0b11100000; RRREEE--
	}
				
}
