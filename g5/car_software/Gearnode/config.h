/*********************************************
 * Config header
 *********************************************/

// CPU clock
#define FOSC           110592		// 11,0592 MHz External cristal
#define F_CPU          (FOSC*100)	// Need for AVR GCC

// CAN
#include "compiler.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "can_std/at90can_drv.h"
#define CAN_BAUDRATE   250        // in kBit

// UART
#define USART_BAUDRATE 115200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 

// Buttons
#define GEARUPBUT 0b00000010
#define GEARDOWNBUT 0b00000001
#define GEARNEUBUT 0b00000100

// Ign Cut
#define IgnCutOn PORTE|= (1<<PE4)
#define IgnCutOff PORTE&=~ (1<<PE4)

// Gearneutralmeasure
#define GEARNEUTRALMEAS (!((PINE&0b10000000)==0b10000000))

//Counter0 Prescaler
#define counter0prescale256 4

// Error msg.
#define ERRORMSG_NOERROR 0
#define ERRORMSG_OVERCURRENT 1
#define ERRORMSG_GEARSTUCK 2
