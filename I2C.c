/*
 * I2C.c
 *
 * Created: 16/09/2017 23:30:38
 *  Author: Matteo
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include "I2C.h"
#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#define TWI_FREQ 100000

short startI2C()//inizia la comunicazione I2C 
{
	TWCR|=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	waitACKlaser();
	if (checkSTARTlaser()) {return 1;}			//restituisce 1 quando lo start non è avvenuto correttamente
	else {return 0;}
}

void waitACKlaser()
{
	while(!(TWCR & (1<<TWINT)));
}

uint8_t checkSTARTlaser()
{
	if ( ( ( TW_STATUS) != TW_START) && ( TW_STATUS != TW_REP_START) )
	return 1; //TW_STATUS...... guarda util.twi.h
	else return 0;
}

short sendI2Claser(short dato)
{
	TWDR=dato;
	TWCR= (1<<TWINT) | (1<<TWEN);
	waitACKlaser();
	if (checkDATAACKlaser()&&checkMTSLAACKlaser()&&checkMRSLAACKlaser()) {return 1;}		//controlla se il dato restituito è uno di quelli possibili
		else {return 0;}
}

uint8_t checkMTSLAACKlaser()
{
	if ( ( TW_STATUS) != TW_MT_SLA_ACK) return 1;
	else return 0;
}
uint8_t checkMRSLAACKlaser()
{
	if ( ( TW_STATUS) != TW_MR_SLA_ACK) return 1;
	else return 0;
}

uint8_t checkDATAACKlaser()
{
	if ( ( TW_STATUS) != TW_MT_DATA_ACK) return 1;
	else return 0;
}
void stoplaser()
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
uint8_t check_readNACKlaser()//controllo lettura non sequenziale
{
	if(TW_STATUS!= TW_MR_DATA_NACK)return 1;
	else return 0;
}
uint16_t readNACKlaser()//lettura non sequenziale
{
	TWCR=(1<<TWINT)|(1<<TWEN);
	waitACKlaser();
	uint16_t ret = (uint16_t)check_readNACKlaser() << 8;//da questa riga di programma posso avere o un 1 o uno 0 shiftati di 8 verso sinistra
	return ret | TWDR;//qui prendo la variabile ret e la metto in or con il dato all'interno di TWDR
}
uint8_t check_readACKlaser()//controllo lettura sequenziale
{
	if(TW_STATUS!= TW_MR_DATA_ACK)return 1;
	else return 0;
}
uint16_t readACKlaser()//lettura sequenziale da verificare appena avremmo un attimo
{
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	waitACKlaser();
	uint16_t ret = (uint16_t)check_readACKlaser() << 8;//da questa riga di programma posso avere o un 1 o uno 0 shiftati di 8 verso sinistra
	return ret | TWDR;//qui prendo la variabile ret e la metto in or con il dato all'interno di TWDR
}

void init_I2C()
{
	TWSR=0;
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;  //12=400KHz 72=100KHz
}

