/*
 * clock.c
 *
 *  Created on: 18. märts 2017
 *      Author: Karl
 *      TODO: interface for SMCLK enable/disable?
 */

/** @file
**	\brief
**
**
**
**/

#include "clock.h"
void
initClk ()
/*!* Basic clock initialization
 **  After a PUC, the basic clock module+ uses DCOCLK for MCLK
 **
 **
 ********************************************************/

{
  IFG1 &= ~OFIFG;
  //_bis_SR_register(SCG1); /* turn off SMCLK */

  /* Setting up DCO */
 // BCSCTL1 = CALBC1_1MHZ; /* DCO calibration, done in MRF_LNK general.h configuration header*/
 // DCOCTL = CALDCO_1MHZ; /* DCO calibration done in MRF_LNK*/

  /* MCLK configuration */
  BCSCTL2 |= SELM_0 + DIVM_0;  /* MCLK sourced by DCO which is determined in MRF_LNK System_Init function*/

  /* ACLK configuration sourced by VLO (approx 4-20kHz)*/
  BCSCTL3 |= LFXT1S_2;
  BCSCTL1 |= DIVA_0;

  /* SMCLK configuration */
  BCSCTL2 |= DIVS_0; /* SMCLK sourced by DCO(default) at 1MHz (1us interval)*/

}

