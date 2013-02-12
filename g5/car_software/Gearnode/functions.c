/*********************************************
 * Functions
 *********************************************/

#include "config.h"
#include "extern.h"
#include "prototyper.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

void servo_direction(unsigned int x)
{
    if (x==0){
        OCR3CH = (0x00);//Minimum: 0x00, 0x45;
        OCR3CL = (0x45);
    }
    else if (x==1){
        OCR3CH = (0x01); //Maximum: 0x01, 0xAE;
        OCR3CL = (0xAE);
    }
}

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