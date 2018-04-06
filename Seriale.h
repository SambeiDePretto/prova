/*
 * Seriale.h
 *
 * Created: 04/11/2017 15:55:26
 *  Author: Matteo
 */ 


#ifndef SERIALE_H_
#define SERIALE_H_
#include <avr/io.h>
#include <util/delay.h>
#define USART_BAUDRATE 9600
#define BAUDR 103

void USART_Init( unsigned int BAUD);
void USART_Tx( unsigned char data );
unsigned char USART_Rx( void );
void Serial_int(uint32_t num);
void Serial_float(double num, int pot);
void Serial_print(char string[]);
void Serial_println(char string[]);




#endif /* SERIALE_H_ */