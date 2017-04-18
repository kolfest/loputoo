/*
 * watchdog.c
 *
 *  Created on: 28. märts 2017
 *      Author: Karl
*/


#include "watchdog.h"
#define LED1 BIT0
#define LED2 BIT6
long long int result;

uint32 wdtCounter = 0;
uint32 wdtMaxP = 0x1E13380; //1 year in seconds
uint8 wdtMinP = 0x02;
uint32 wdtCurrentPeriod = 0;
uint32 count[30];
uint32 k = 0;
unsigned long long int aeg[10];


/*
void WDT_configure()
{

	WDTCTL = WDT_ADLY_1000; // Set Watchdog Timer interval to 1 second
	IE1 |= WDTIE; // Enable WDT interrupt
	P1DIR |= BIT0; // Set P1.0 to output direction
	__enable_interrupt();

}
*/

uint32
WDT_getCurrentPeriod()
{
  return wdtCurrentPeriod;
}


uint8 WDT_setWatchdog(uint32 period)
/*******************************************************
**Configures watchdog timer wakeup period
** Ranges from 1.6 * period(20kHz) to 8 * period(4kHz)
**
** minimal 2 periods (typically 8 seconds)
**
** typical 3.4 seconds per period (atleast 15 periods)
**
** 4kHz = 8 second period
** 8kHz = 4 second period
** 12kHz = 2.66666 second period
** 20kHz = 1.66666 second period
**
**
********************************************************/
{


 if(((wdtMinP > period) || (period > wdtMaxP)))
    return WDT_ERR;

  wdtCurrentPeriod = period;
  //WDT_configure();
  return WDT_SUCCESS;

}

/*
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{

	if(wdtCounter == wdtCurrentPeriod)
	{

	    P1OUT ^= 0x01;
	    //_BIS_SR(LPM3_bits + GIE);//go to sleep bastard
	    //_BIC_SR_IRQ(LPM3_bits);  // wake up from low power mode
	    wdtCounter = 0;

	    timer_getElapsedTime(&yhik);
	    aeg[k++] = yhik.elapsed;
	    timer_initCount(&yhik);
	    if (k == 8){
	    	WDTCTL = WDTPW | WDTHOLD;
	    }

	    //

	}
	else

	{
			wdtCounter++;

	}

}
*/
