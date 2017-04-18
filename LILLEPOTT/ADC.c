/*
 * converter.c
 *
 *  Created on: 27. märts 2017
 *      Author: Karl
 *      TODO:
 *	*ADC_IDLE is not covered in ADC_configureADC();
 *      implement isADC busy check for startconversion and adcconf, maybe remove startconversion isadcbusy check alltogether and do it in config
 */
#include "ADC.h"

uint8 configuration = 0;
volatile int16 tulemus = -1;

int CAL_ADC_25T30_V = 444; /*calibration constant */
int CAL_ADC_25T85_V = 527; /*calibration constant */

uint8
checkIfADCON()
/*******************************************************
**
**
********************************************************/
{

  return checkIsBitSet(ADC10CTL0, 4);

}

uint8
/*******************************************************
** Configures ADC registers and turns on the ADC
** returns error if refrence not settled, or invalid config, success otherwise
**
**
********************************************************/
ADC_configureADC(ADC_confType configuration)
{
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + REF2_5V + ADC10ON; /*VR+ = VREF+ and VR- = VSS, maximum sample-and-hold time, Turn internal refrence generator on, refrence voltage 2.5V */

	    switch (configuration)
	    {

		    case ADC_TEMP:
			    ADC10CTL1 = INCH_10 + ADC10DIV_0; /* select channel for internal temp sensor */
			    return ADC_CONFIG_SUCCESS;


		    case ADC_HUMIDITY:
			    ADC10CTL1 = INCH_10 + ADC10DIV_0; /* select A0 */
			    return ADC_CONFIG_SUCCESS;


		    case ADC_BATTERY:
			    ADC10CTL1 = INCH_11 + ADC10DIV_0; 	/* Analog channel (Vcc-Vss)/2 */
			    return ADC_CONFIG_SUCCESS;
		    case ADC_IDLE:
		    break;

	    }

	return ADC_CONFIG_FAILURE;
}

uint8
ADC_startConversion()
/*******************************************************
** Enables conversion and starts it if ADC10 is not busy
**
**
********************************************************/
{

  if(checkIfADCBusy())
      return ADC_BUSY;

  ADC10CTL0 |= ENC + ADC10SC; /* Enable and start conversion */

  return ADC_INIT_SUCCESS;
}

uint8 checkIfADCBusy()
{

  return checkIsBitSet(ADC10CTL1, 0);

}

void
ADC_stopConversion()
/*******************************************************
**
**
**
********************************************************/
{

  ADC10CTL0 &= ~ENC; /* Stop conversion */
  ADC10CTL0 &= ~(REFON + ADC10ON); /* Disable voltage refrence generator and ADC core */

}


int16
ADC_getConversionResult()
/*******************************************************
** Get ADC conversion result from ADC10MEM
**
**
********************************************************/
{

  //int16 result = -1;
  tulemus = ADC10MEM;
  return tulemus;

}

float
ADC_measure()
/*******************************************************
**
** returns uncalibrated ADC conversion result (range: 0 to 1023)
** Further calibration is needed based on ADC configuration
** \return
** \return
** \return
**
********************************************************/
{
/*
  if( ADC_CONFIG_FAILURE == ADC_configureADC(configuration))
    return ADC_INVALID_CONVERSION_RESULT;
*/

    if( checkIfADCBusy() == 1)
      return ADC_INVALID_CONVERSION_RESULT;

  ADC_startConversion();

  ADC_stopConversion();

  volatile uint16 result = ADC_getConversionResult();

  return result;

}
