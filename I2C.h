/*
 * I2C.h
 *
 * Created: 16/09/2017 23:30:53
 *  Author: Matteo
 */ 


#ifndef I2C_H_
#define I2C_H_
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <stdbool.h>
#define USART_BAUDRATE 9600
#define BAUDR 103		// "9600,N,

	short startI2C();
	void waitACKlaser();
	uint8_t checkSTARTlaser();
	short sendI2Claser(short dato);
	uint8_t checkMTSLAACKlaser();
	uint8_t checkMRSLAACKlaser();
	uint8_t checkDATAACKlaser();
	void stoplaser();
	uint8_t check_readNACKlaser();
	uint16_t readNACKlaser();
	uint8_t check_readACKlaser();
	uint16_t readACKlaser();
	
	void init_I2C();

#endif /* I2C_H_ */