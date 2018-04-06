/*
 * BNO055.c
 *
 * Created: 06/04/2018 12:58:46
 *  Author: Studente
 */ 
#include "BNO055.h"

void writeReg_BNO(uint8_t reg, uint8_t value)
{
	if (startI2C()) {stoplaser();}									//mi restituisce 1 se lo start NON � avvenuto correttamente
	if (sendI2Claser(slave|TW_WRITE)) {stoplaser();}				////mi restituisce 1 se la trasmissione NON � avvenuta correttamente
	if (sendI2Claser(reg)) {stoplaser();}
	if (sendI2Claser(value)) {stoplaser();}
	stoplaser();
	_delay_ms(5);
}

uint8_t readReg_BNO(uint8_t reg)
{
	if (startI2C()) {stoplaser();}
	if (sendI2Claser(slave|TW_WRITE)) {stoplaser();}
	if (sendI2Claser(reg)) {stoplaser();}
	//stop();
	startI2C();
	if (sendI2Claser(slave|TW_READ)) {stoplaser();}
	uint16_t value=readNACKlaser();
	stoplaser();
	_delay_ms(5);
	if (value>>8) {stoplaser();}
	return value;
}

int BNO_begin()
{
	
}

