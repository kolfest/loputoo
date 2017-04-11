/*
 * watchdog.c
 *
 *  Created on: 28. märts 2017
 *      Author: Karl
*/

#include "watchdog.h"
#include "timer.h"
#define LED1 BIT0
#define LED2 BIT6
TimerStruct testTimerModule;
long long int result;
int flag=1;
unsigned int wdtCounter = 0;
/*
void WDT_configure()
{
	WDTCTL = WDT_ADLY_1000; // Set Watchdog Timer interval to 1 second
	IE1 |= WDTIE; // Enable WDT interrupt
	P1DIR |= BIT0; // Set P1.0 to output direction
	__enable_interrupt();
	timer_initCount(&testTimerModule);


}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
	//P1OUT ^= 0x01;
	if(wdtCounter == 1)
	{
			if (flag)
			{   flag=0;

				//_BIS_SR(LPM3_bits + GIE);//go to sleep bastard

			}else{
				flag=1;
				//_BIC_SR_IRQ(LPM3_bits);  // wake up from low power mode

			}

			wdtCounter = 0;

			 // P1.0 turn off
	}
	else

	{
		result = timer_getElapsedTime(&testTimerModule);
		wdtCounter++;
	}

}

*/
