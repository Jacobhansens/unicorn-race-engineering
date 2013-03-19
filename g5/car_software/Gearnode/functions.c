/*********************************************
 * Functions
 *********************************************/

#include "config.h"
#include "extern.h"
#include "prototyper.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

void servoPosition(unsigned int position) {
    gearGotoPosition = position;
    gearActive = 1;
    float dutyCycle = (0.6278260870)*(float)position+(42.63130435);
    OCR3CH = (0xFF) & ((int)dutyCycle>>8);
    OCR3CL = (0xFF) & ((int)dutyCycle);
}//Maximum: 0x01, 0xAE; //Minimum: 0x00, 0x45;

void servoCheck(void)
{
    if (abs(gearPosition-gearGotoPosition) < 5) {
        gearActive = 0;
        gearCounter = 0;
        if (gearGotoPosition != MIDPOS) {
            servoPosition(MIDPOS);
        }
    }
    else if (gearCounter > 20) {
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