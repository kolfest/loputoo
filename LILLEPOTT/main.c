#include <msp430.h> 

/*
 * main.c
 */

#include "clock.h"
#include "ADC.h"
#include "watchdog.h"
#include "system.h"
#include "timer.h"

volatile long temp1;
volatile long temp2;
uint16 result;
float input;
int CAL_ADC_25T30VV = 444;
int CAL_ADC_25T85VV = 527;
uint8 conf = ADC_TEMP;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    initClk();
    timer_init();
    //WDT_configure();
    TimerStruct esimene;
    timer_initCount(&esimene);
    result = ADC_measure(conf);
    timer_getElapsedTime(&esimene);
    input = ((float)(((int32)result - CAL_ADC_25T30VV) * (85 - 30)) / (CAL_ADC_25T85VV - CAL_ADC_25T30VV) + 30.000);
    for(;;)
      {

      }

	return 0;
}

