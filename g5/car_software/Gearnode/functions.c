/*********************************************
 * Functions
 *********************************************/

#include "config.h"
#include "extern.h"
#include "prototyper.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

void servoPosition(unsigned int position)
{
    float dutyCycle = (0.6278260870)*(float)position+(42.63130435);
    OCR3CH = (0xFF) & ((int)dutyCycle>>8);
    OCR3CL = (0xFF) & ((int)dutyCycle);
    
}//Maximum: 0x01, 0xAE;// Middle position//Minimum: 0x00, 0x45;

unsigned short int getBut(void)
{
	 if(!((PINE&0b10000000)==0b10000000))
	 	return GEARUPBUT;

	 else if(!((PINE&0b01000000)==0b01000000))
	 	return GEARDOWNBUT;

	 else if(!((PINE&0b00100000)==0b00100000))
	 	return GEARNEUBUT;
			 
	 else 
	 	return 0;
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