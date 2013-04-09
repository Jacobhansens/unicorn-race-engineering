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
#include "debug.h"

// ADC
unsigned int ADCconv = 0;

// Debugging
char tempchar[10];
unsigned short int count = 0;

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
    //servoCheck();
    
    gearBut = gearButCAN;
    
    if((gearBut == 0) || (gearBut == GEARNEUBUT))
		gearButActive = 2;
    else gearButActive = 1;
    
	if((count%250)==0)
	{

        /* Data til leg med gear knapper
        sendtekst("gearButCAN: ");
		itoa(gearButCAN,tempchar,2);
		sendtekst(tempchar);
		sendtekst("\t");
        
        sendtekst("gearButActive: ");
		itoa(gearButActive,tempchar,2);
		sendtekst(tempchar);
		sendtekst("\r\n");
        */
        /* Data til leg med gear positioner */
		//sendtekst("Pos: ");
		itoa(gearPosition,tempchar,10);
		sendtekst(tempchar);
		//sendtekst("\t");
        
        //sendtekst("PosOld: ");
		//itoa(gearPositionOld,tempchar,10);
		//sendtekst(tempchar);
		//sendtekst("\t");
        sendtekst("/");
        //sendtekst("GotoPos: ");
		itoa(gearGotoPosition,tempchar,10);
		sendtekst(tempchar);
		//sendtekst("\t");
        
        //sendtekst("GearActive: ");
		//itoa(gearActive,tempchar,10);
		//sendtekst(tempchar);
		//sendtekst("\t");
        sendtekst(" - ");
        //sendtekst("GearCounter: ");
		itoa(gearCounter,tempchar,10);
		sendtekst(tempchar);
		sendtekst("\r\n");
		//servoPosition(MIDPOS);

		count = 0;
	}
	count++;
    
}
