/*
 * BNO055.c
 *
 * Created: 06/04/2018 12:58:46
 *  Author: Studente
 */ 
#include "BNO055.h"

void writeReg_BNO(uint8_t reg, uint8_t value)
{
	if (startI2C()) {stoplaser();}									//mi restituisce 1 se lo start NON è avvenuto correttamente
	if (sendI2Claser(slave|TW_WRITE)) {stoplaser();}				////mi restituisce 1 se la trasmissione NON è avvenuta correttamente
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
void setMode (uint8_t mode)
{
	writeReg_BNO(BNO055_OPR_MODE_ADDR, _mode);//0x3D
	_delay_ms(30);
}
int BNO_begin()
{
	  uint8_t id = read8(BNO055_CHIP_ID_ADDR);
	  if(id != BNO055_ID)
	  {
	    _delay_ms(1000); 
	    id = read8(BNO055_CHIP_ID_ADDR);
	    if(id != BNO055_ID)
	    {
	      Serial_print("errore, nessun dispositivo collegato");
	    }
	  }
}

