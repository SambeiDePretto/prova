/*
 * Seriale.c
 *
 * Created: 04/11/2017 15:55:11
 *  Author: Matteo
 */ 

#include "Seriale.h"
#include <avr/io.h>
#include <util/delay.h>
#define USART_BAUDRATE 9600
#define BAUDR 103		// "9600,N,8,1"

void USART_Init( unsigned int BAUD) //inizializza seriale
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(BAUD>>8);  // 9600 bit/s
	UBRR0L = (unsigned char)BAUD;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit, none parity  "9600,N,8,1" */
	UCSR0C = 0b00000110;
} // USART_Init

void USART_Tx( unsigned char data )//Trasmissione seriale (un carattere)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0=data;//0b00001111 ;
}

unsigned char USART_Rx( void )//ricezione seriale (un carattere)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void Serial_int(uint32_t num)
{
	if(num==0)
	{
		USART_Tx('0');
	}
	else
	{
		int str[10];				// definisce una stringa sulla quale convertire il numero da trasmettere (max 10 cifre)
		int i;						// contatore ciclo
		for(i=0;i<10;i++) str[i]=0; // cancella la stringa
		i=9;
		while (num)
		{
			str[i]=num%10+'0';		// converte il numero da trasmettere in una stringa (dalla cifra meno significativa)
			num/=10;
			i--;
		}
		for (i=0;i<10;i++)			// invia la stringa un carattere alla volta
		if (str[i]) USART_Tx((char)str[i]);
	}
}

void Serial_float(double num, int pot)
{
	int resto,temp;
	Serial_int(num);
	USART_Tx('.');
	num=(num-(int)num+0.00001);
	for(int i=1;i<=pot;i++)
	{
		temp=num*pow(10,i);
		resto=temp%10;
		Serial_int(resto);
	}
}

void Serial_print(char string[])
{
	int i=0;
	while(string[i])
	{
		USART_Tx(string[i]);
		i++;
	}
}

void Serial_println(char string[])
{
	int i=0;
	while(string[i])
	{
		USART_Tx(string[i]);
		i++;
	}
	USART_Tx('\n');
}

void USART_Send_Uint(uint32_t num)
{
	char str[10];				// definisce una stringa sulla quale convertire il numero da trasmettere (max 10 cifre)
	char i;						// contatore ciclo
	for(i=0;i<10;i++) str[i]=0; // cancella la stringa
	i=9;
	while (num)
	{
		str[i]=num%10+'0';		// converte il numero da trasmettere in una stringa (dalla cifra meno significativa)
		num/=10;
		i--;
	}
	for (i=0;i<10;i++)			// invia la stringa un carattere alla volta
	if (str[i]) USART_Tx(str[i]);
}
