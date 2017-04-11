/*
 * converter.c
 *
 *  Created on: 27. märts 2017
 *      Author: Karl
 *      TODO:
 *      implement ref settle delay for adcconf
 *      implement invalid configuration for adcconf
 *      implement isADC busy check for startconversion and adcconf, maybe remove startconversion isadcbusy check alltogether and do it in config
 */
#include "ADC.h"
#include "timer.h"

uint8 c_ADC_REF_SETTLE = 1;
uint8 c_INVALID_CONFIGURATION = 0;
uint8 configuration = ADC_TEMP;
volatile int16 tulemus = -1;

float temp = 0;

#ifdef TEST
uint16 ADC10CTL1 = 0;
#endif

int CAL_ADC_25T30_V = 444;
int CAL_ADC_25T85_V = 527;

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
checkIsBitSet(uint16 registerr, uint16 position)
/*******************************************************
** int position - position of the bit to be checked
** LSB is 0th bit
** Returns 1 if the bit is set
**
**
********************************************************/
{

  uint16 result = (((registerr)>>(position)) & 1);
  return result;

}

uint8
/*******************************************************
** Configures ADC registers and turns on the ADC
** returns error if refrence not settled, or invalid config, success otherwise
**
**
********************************************************/
ADC_configureADC(uint8 configuration)
{
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + REF2_5V + ADC10ON; /*VR+ = VREF+ and VR- = VSS, maximum sample-and-hold time, Turn internal refrence generator on, refrence voltage 2.5V */

	if (c_INVALID_CONFIGURATION) /* configuration checking test double, needs proper implementation */
	{
		return ADC_INVALID_INPUT;
	}
	  if (c_ADC_REF_SETTLE)/* adc refrence settle test double, needs proper implementation */
	{
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


	    }
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

float ADC_calibrateResult(uint16 *result)
{

}

float
ADC_measure(uint8 configuration)
/*******************************************************
**
** returns uncalibrated ADC conversion result (range: 0 to 1023)
** Further calibration is needed based on ADC configuration
** \return
** \return
** \return TIMEOUT-
**
********************************************************/
{

  volatile TimerStruct timer;
  if( ADC_INVALID_INPUT == ADC_configureADC(configuration))
    return ADC_INVALID_CONVERSION_RESULT;

  while( ADC_BUSY == ADC_startConversion()); /* wait till adc is ready */

  /* delay */

  timer_initCount(&timer);

  while(100 > timer_getElapsedTime(&timer)); /* wait for 1500 us */

  ADC_stopConversion();

  volatile uint16 result = ADC_getConversionResult();

  return result;

}

void ADC_cyclic()
{

}
