#include <msp430.h> 

/*
 * main.c
 */

#include "clock.h"
//#include "ADC.h"
#include "watchdog.h"
#include "system.h"
volatile long temp1;
volatile long temp2;
const uint8 hue = 1;

int main(void) {
    //WDTCTL = WDTPW | WDTHOLD;
    initClk();
    WDT_configure();
    for(;;)
      {
      }

	return 0;
}

