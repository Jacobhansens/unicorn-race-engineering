/*********************************************
 * Interrupt-service-rutiner
 *
 * Max er helt ude
 * Min er helt inde
 *
 *********************************************/

#include "config.h"
#include "extern.h"
#include "prototyper.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ADC
unsigned int ADCconv = 0;

// Gear
unsigned short int gearBut = 0;
unsigned short int gearButCAN = 0;

// Debugging
char tempchar[10];
unsigned short int i = 0;

// ADC convert complete
ISR(ADC_vect,ISR_NOBLOCK)
{
	unsigned int adlow = 0;
	unsigned int adhigh = 0;

    gearPositionOld = gearPosition;
    
	// Read ADC convertion
    adlow=ADCL;
    adhigh=ADCH;
	ADCconv = (unsigned int)((adhigh<<8)|(adlow & 0xFF));
    //ADCconv = (ADCconv-1023)*-1; //Hvis det skal vendes
    gearPosition = ADCconv;
}

// Timer0 (8-bit) overflow interrupt (168 Hz)
ISR(TIMER0_OVF_vect)
{
    servoCheck();
    
	if((i%15)==0)
	{
		sendtekst("Pos: ");
		itoa(gearPosition,tempchar,10);
		sendtekst(tempchar);
		sendtekst("\t");
        
        sendtekst("PosOld: ");
		itoa(gearPositionOld,tempchar,10);
		sendtekst(tempchar);
		sendtekst("\t");
        
        sendtekst("GotoPos: ");
		itoa(gearGotoPosition,tempchar,10);
		sendtekst(tempchar);
		sendtekst("\t");
        
        sendtekst("GearActive: ");
		itoa(gearActive,tempchar,10);
		sendtekst(tempchar);
		sendtekst("\t");
        
        sendtekst("GearCounter: ");
		itoa(gearCounter,tempchar,10);
		sendtekst(tempchar);
		sendtekst("\r\n");
        
		i = 0;
	}
	i++;
    
}
