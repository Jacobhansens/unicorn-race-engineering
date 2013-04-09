/*********************************************
 * Functions
 *********************************************/

#include "config.h"
#include "extern.h"
#include "prototyper.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "debug.h"
#include <util/delay.h>

void servoPosition(unsigned int position) {
	count = 0;
	gearCounter = 0;
    gearGotoPosition = position;
    gearActive = 1;
    float dutyCycle = (0.6278260870)*(float)position+(42.63130435);
    OCR3CH = (0xFF) & ((int)dutyCycle>>8);
    OCR3CL = (0xFF) & ((int)dutyCycle);
}//Maximum: 0x01, 0xAE; //Minimum: 0x00, 0x45;

void gearUp(void){
	servoPosition(230);
	_delay_ms(GEARWAIT);
	servoPosition(MIDPOS);
	_delay_ms(GEARWAIT);
}

void gearDown(void){
	servoPosition(500);
	_delay_ms(GEARWAIT);
	servoPosition(MIDPOS);
	_delay_ms(GEARWAIT);
}

void gearNeutral(void){
	servoPosition(400);
	_delay_ms(GEARWAIT);
	servoPosition(MIDPOS);
	_delay_ms(GEARWAIT);
}

void servoCheck(void)
{/*
    if (abs(gearPosition-gearGotoPosition) < 5 && gearCounter > 100) {
        gearActive = 0;
        gearCounter = 0;
        if (gearGotoPosition != MIDPOS) {
            servoPosition(MIDPOS);
        }
    }*/
     if (gearCounter > 100) {
        gearActive = 0;
        gearCounter = 0;
        servoPosition(MIDPOS);
    }
    else if (abs(gearPosition - gearPositionOld) < 5) {
        gearCounter++;
    }
}

void adcStop(void)
{
	ADCSRA &=~(1<<ADEN); // ADC prescaler disable
}

void sendtekst(char *tekstarray)
{
	short int i;
	for (i = 0; tekstarray[i] != '\0'; i++)
	{	
		while ((UCSR1A & (1 << UDRE1)) == 0) {};
		UDR1 = tekstarray[i];
	}
}
