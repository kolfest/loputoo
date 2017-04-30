/*
 * watchdog.c
 *
 *  Created on: 28. märts 2017
 *      Author: Karl
*/
/** @file watchdog.c
**	\brief Documentation for the watchdog module.
**
**
**
**/

#include "watchdog.h"

uint32 wdtCounter = 0; /**< Period counter, period length depends on WDT configuration*/
static const uint32 wdtMaxP = 0x1E13380; /**< maximum bound for watchdog period setting, currently no interface to change*/
static const uint8 wdtMinP = 0x02; /**< minimum bound watchdog period setting, currently no interface to change*/
uint32 wdtCurrentPeriod = 0; /**< current configured period, default is 0, ranges from 2 to 31536000*/
extern uint16 fMeasurement;
void WDT_configure()
/*!******************************************************
** Configures watchdog module
********************************************************/
{

	WDTCTL = WDT_ADLY_1000; /* Set Watchdog Timer interval */
	IE1 |= WDTIE; /* Enable WDT interrupt */
	__enable_interrupt(); /* enable global interrupts? idk if needed */

}

uint32
WDT_getCurrentPeriod()
/*!******************************************************
** interface for getting current set WDT period count
** \return wdtCurrentPeriod
********************************************************/
{

  return wdtCurrentPeriod;

}


uint8 WDT_setWatchdog(
						uint32 period) /**< Period for watchdog, valid range:  2 - 31536000*/
/*!******************************************************
** Configures watchdog timer wakeup period
** Uses VLO as a source clock, which ranges from 4kHz - 20 kHz
**
** Acceptable input: 2 - 31536000 (typically 7.2 seconds - 1314 days)
**
** minimal 2 periods (typically 2 * 3.6 seconds)
**
** typical 3.6 seconds per period (atleast 15 periods)
**
** 4kHz = 8 second period
** 8kHz = 4 second period
** 12kHz = 2.66666 second period
** 20kHz = 1.66666 second period
**
**\return WDT_SUCCESS
**\return WDT_ERR
********************************************************/
{

// if(((wdtMinP > period) || (period > wdtMaxP))) /* check if input values are in range */
//    return WDT_ERR; /*return error if not */

  wdtCurrentPeriod = (period * 17); /* configure the watchdog period, usually 17 periods for 1 minute */
  WDT_configure(); /* configure watchdog */
  return WDT_SUCCESS;

}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{

	if(wdtCounter == wdtCurrentPeriod)
	{

	    _BIC_SR_IRQ(LPM3_bits);  /* wake up from low power mode */
	    IE1 &= ~(1 << 0); /* disable watchdog interrupt */
	    fMeasurement = 1; /* set the meaurement mode */
	    wdtCounter = 0; /* reset watchdog period counter */

	}
	else

	{
			wdtCounter++; /* add to the period counter */

	}

}

