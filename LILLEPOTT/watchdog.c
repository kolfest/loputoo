/*
 * watchdog.c
 *
 *  Created on: 28. märts 2017
 *      Author: Karl
*/
/*
#include "watchdog.h"
#define LED1 BIT0
#define LED2 BIT6
int flag=0;
unsigned int wdtCounter = 0;

void WDT_configure()
{
	WDTCTL = WDT_ADLY_1000; // Set Watchdog Timer interval to 1 second
	IE1 |= WDTIE; // Enable WDT interrupt
	P1DIR |= BIT0; // Set P1.0 to output direction
	__enable_interrupt();
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
	if(wdtCounter == 0)
	{
			if (flag)
			{   flag=0;
				_BIS_SR(LPM3_bits + GIE);//go to sleep bastard

			}else{
				//flag=1;
				_BIC_SR_IRQ(LPM3_bits);  // wake up from low power mode

			}

			wdtCounter = 0;
			//P1OUT ^= 0x01; // P1.0 turn off
	}
	else
	{
		wdtCounter++;
	}
}

*/
