/*
 * Digital_Thermometer.c
 * Romashov Denis 2100
 */ 
 
#define F_CPU 16000000
#include <avr/delay.h>
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>

#define BUAD 9600
#define BRC ((F_CPU/16/BUAD) - 1)
#define TX_BUFFER_SIZE 128

char serialBuffer[TX_BUFFER_SIZE];
uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;

void appendSerial(char c);
void serialWrite(char c[]);

char tempstr[20];
 
/*заявляем LCD дисплей */
void LCD_send_command(unsigned char cmnd);
void LCD_send_data(unsigned char data);
void LCD_init();
void LCD_goto(unsigned char y, unsigned char x);
void LCD_print(char *string);
 
/*преобразование постоянного тока в программе обработки прерываний (ISR)*/
ISR(ADC_vect);
 
#define LCD_DATA_PORT	PORTB
#define LCD_DATA_DDR	DDRB
#define LCD_DATA_PIN	PINB
 
#define LCD_CNTRL_PORT	PORTD
#define LCD_CNTRL_DDR	DDRD
#define LCD_CNTRL_PIN	PIND
 
#define LCD_RS_PIN		6
#define LCD_RW_PIN		5
#define LCD_ENABLE_PIN	        7
#define SET_HOUR		3
#define SET_MINUTE		4
 
int main(void)
{
	UBRR0H = (BRC >> 8);
	UBRR0L = BRC;
	
	UCSR0B = (1 << TXEN0) | (1 << TXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	unsigned char i; 
 
    LCD_init();
	LCD_goto(1,2);
	LCD_print("Temperature is");
 
 
	LCD_CNTRL_PORT = (1<<SET_HOUR | 1<<SET_MINUTE);
 
	DDRC = 0x00;			// Аналоговый порт на вход

	ADCSRA = 0x8F;			

	ADMUX = 0xE0;			
	
 
	sei();				// разрешение прерывания
	ADCSRA |= 1<<ADSC;
 
	while(1)
	{
	serialWrite(tempstr);
	_delay_ms(3000);
	}
}
 
void LCD_send_command(unsigned char cmnd)
{
	LCD_DATA_PORT = cmnd;
	LCD_CNTRL_PORT &= ~(1<<LCD_RW_PIN);
	LCD_CNTRL_PORT &= ~(1<<LCD_RS_PIN);
 
	LCD_CNTRL_PORT |= (1<<LCD_ENABLE_PIN);
	_delay_us(2);
	LCD_CNTRL_PORT &= ~(1<<LCD_ENABLE_PIN);
	_delay_us(100);
}
 
/* Функция посылает данные на LCD дисплей*/
void LCD_send_data(unsigned char data)
{
	LCD_DATA_PORT = data;
	LCD_CNTRL_PORT &= ~(1<<LCD_RW_PIN);
	LCD_CNTRL_PORT |= (1<<LCD_RS_PIN);
 
	LCD_CNTRL_PORT |= (1<<LCD_ENABLE_PIN);
	_delay_us(2);
	LCD_CNTRL_PORT &= ~(1<<LCD_ENABLE_PIN);
	_delay_us(100);
}
 
void LCD_init()
{
	LCD_CNTRL_DDR = 0xFF;
	LCD_CNTRL_PORT = 0x00;
	LCD_DATA_DDR = 0xFF;
	LCD_DATA_PORT = 0x00;
 
	_delay_ms(10);
	LCD_send_command(0x38);
	LCD_send_command(0x0C);
	LCD_send_command(0x01);
	_delay_ms(10);
	LCD_send_command(0x06);
}
 
/* Эта функция перемещает курсор*/
void LCD_goto(unsigned char y, unsigned char x)
{
	unsigned char firstAddress[] = {0x80,0xC0,0x94,0xD4};
 
	LCD_send_command(firstAddress[y-1] + x-1);
	_delay_ms(10);	
}
 
void LCD_print(char *string)
{
	unsigned char i=0;
 
	while(string[i]!=0)
	{
		LCD_send_data(string[i]);
		i++;
	}
}
 
/*Завершение преобразования прерывания (ISR)*/
ISR(ADC_vect)
{	
	char tempC, tempF;
	float tempff;
	char display[36];
 
	tempC = ADCH;			
	tempff = (float)tempC;
	tempff = (tempff*9)/5 + 32;	
	tempF = tempff;
 
	LCD_goto(2,4);	
	itoa(tempC/10,display,10);
	LCD_print(display);
	itoa(tempC%10,display,10);
	LCD_print(display);
	LCD_send_data(0xDF);
	LCD_print("C   ");
	itoa(tempF/10,display,10);
	LCD_print(display);
	itoa(tempF%10,display,10);
	LCD_print(display);
	LCD_send_data(0xDF);
	LCD_print("F");
	_delay_ms(500);
	sprintf(tempstr, "%d %d", tempC, tempF);
	ADCSRA |= 1<<ADSC;		
}

void appendSerial(char c)
{
	  serialBuffer[serialWritePos] = c;
	  serialWritePos++;
	  
	  if (serialWritePos >= TX_BUFFER_SIZE)
	  {
		  serialWritePos = 0;
	  }
}

void serialWrite(char c[])
{
	for(uint8_t i = 0; i < strlen(c); i++)
	{
		appendSerial(c[i]);
	}

	if(UCSR0A & (1 << UDRE0))
	{
		UDR0 = 0;
	}
}

ISR(USART_TX_vect)
{
	if (serialReadPos != serialWritePos)
	{
		UDR0 = serialBuffer[serialReadPos];
		serialReadPos++;
		
		if(serialReadPos >= TX_BUFFER_SIZE)
		{
			serialReadPos++;
		}
	}
}
