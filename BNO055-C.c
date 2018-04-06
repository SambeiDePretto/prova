/*
 * BNO055.c
 *
 * Created: 06/04/2018 12:57:30
 *  Author: Studente
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "Seriale.h"
#include "BNO055.h"

int main(void)
{
    init_I2C();
    while(1)
    {
        BNO_begin(); 
    }
}
