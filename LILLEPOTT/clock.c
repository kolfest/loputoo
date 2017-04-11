/*
 * clock.c
 *
 *  Created on: 18. märts 2017
 *      Author: Karl
 *      TODO: interface for SMCLK enable/disable?
 */

//#define DEBUG

#ifdef DEBUG
unsigned char CAL_DATA[8];
int j;
#endif

#include "clock.h"
void
initClk ()
/** Basic clock initialization
 **  After a PUC, the basic clock module+ uses DCOCLK for MCLK
 **
 **
 ********************************************************/

{
  IFG1 &= ~OFIFG;
  //_bis_SR_register(SCG1); /* turn off SMCLK */


  /* Setting up DCO */
#ifdef DEBUG
  /* get calibration constants from segmentA */
  j = 0;
  CAL_DATA[j++] = DCOCTL;
  CAL_DATA[j++] = BCSCTL1;
#endif

  BCSCTL1 = CALBC1_1MHZ; /* DCO calibration */
  DCOCTL = CALDCO_1MHZ; /* DCO calibration */

#ifdef DEBUG
  /* get calibration constants from segmentA */
  CAL_DATA[j++] = DCOCTL;
  CAL_DATA[j++] = BCSCTL1;
#endif

  /* MCLK configuration */
  BCSCTL2 |= SELM_0 + DIVM_0;  /* MCLK sourced by DCO at 125kHz*/

  /* ACLK configuration */
  BCSCTL3 |= LFXT1S_0; /* 32768-Hz on LFXT1 */
  BCSCTL1 |= DIVA_0;

  /* SMCLK configuration */
  BCSCTL2 |= DIVS_0; /* SMCLK sourced by DCO(default) at 1MHz (1us interval)*/

  //BCSCTL1 &= ~(1<<6);

}

