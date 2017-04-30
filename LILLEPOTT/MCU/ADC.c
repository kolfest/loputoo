/*
 * converter.c
 *
 *  Created on: 27. m�rts 2017
 *      Author: Karl
 *      TODO:
 *		*ADC_IDLE is not covered in ADC_configureADC();
 *      implement isADC busy check for startconversion and adcconf, maybe remove startconversion isadcbusy check alltogether and do it in config
 */

/** @file
**	\brief ADC hardware abstraction
**
**
**
**/

#include "ADC.h"

volatile uint16 tulemus = 0;

const int CAL_ADC_25T30_V = 444; /*calibration constant */
const int CAL_ADC_25T85_V = 527; /*calibration constant */

uint8
checkIfADCON()
/*!******************************************************

	Check if ADC core is turned on
	Called by ADC_configureADC (yet to be implemented)
\return 1 if on, 0 otherwise
********************************************************/
{

  return checkIsBitSet(ADC10CTL0, 4);

}

uint8
/*!******************************************************
** Configures ADC registers and turns on the ADC
** returns error if refrence not settled, or invalid config, success otherwise
@startuml{ADC_configureADC.png}
 	ADC_MGR -> ADC: ADC_configureADC
 	ADC -> ADC: configure ADC
	ADC_MGR <-- ADC: ADC_CONFIG_SUCCESS
	note left
		Configuration found
	end note

	ADC_MGR -> ADC: ADC_configureADC
	 ADC -> ADC: configure ADC
	ADC_MGR <-- ADC: ADC_CONFIG_FAILURE
	note left
		Configuration found
	end note
@enduml
********************************************************/
ADC_configureADC(ADC_confType configuration)
{
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + REF2_5V + ADC10ON; /*VR+ = VREF+ and VR- = VSS, maximum sample-and-hold time, Turn internal refrence generator on, refrence voltage 2.5V */
	/* TODO: checkIfADCON functionality */
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
/*!******************************************************
** Enables conversion and starts it if ADC10 is not busy
** Usually called by ADC_measure
@startuml{ADC_STARTCONVERSION.png}
	ADC_measure -> ADC: ADC_startConversion
	note right
		ADC not busy
	end note
	ADC -> ADC: checkIfADCBusy
	ADC <-- ADC: 0
	ADC_measure <-- ADC: ADC_INIT_SUCCESS

	ADC_measure -> ADC: ADC_startConversion
	note right
		ADC  busy
	end note
	ADC -> ADC: checkIfADCBusy
	ADC <-- ADC: 1
	ADC_measure <-- ADC: ADC_BUSY

@enduml
**\return
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
/*!******************************************************
**
** Stop ADC conversion, disable internal refrence generator and ADC core
**
********************************************************/
{

  ADC10CTL0 &= ~ENC; /* Stop conversion */
  ADC10CTL0 &= ~(REFON + ADC10ON); /* Disable voltage refrence generator and ADC core */

}


uint16
ADC_getConversionResult()
/*!******************************************************
**
** Get ADC conversion result from ADC10MEM
**\return uint16 result
********************************************************/
{

  tulemus = ADC10MEM;
  return tulemus;

}

uint16
ADC_measure()
/*!******************************************************
** Measures synchronously, usual call made by ADCMGR
@startuml{ADC_MEASURE.png}
	ADC_MGR -> ADC: ADC_measure
	note right
		ADC not busy
	end note
	ADC -> ADC: ADC_startConversion
	ADC <--  ADC: ADC_INIT_SUCCESS
	... Delay ...
	ADC -> ADC: ADC_stopConversion
	ADC -> ADC: ADC_getConversionResult
	ADC_MGR <--  ADC: result

	ADC_MGR -> ADC: ADC_measure
	note right
		ADC busy
	end note
	ADC -> ADC: ADC_startConversion
	ADC <--  ADC: ADC_BUSY
	loop 10 times
		ADC -> ADC: ADC_startConversion
	end
	ADC <--  ADC: ADC_INIT_SUCCESS
	... Delay ...
		ADC -> ADC: ADC_stopConversion
	ADC -> ADC: ADC_getConversionResult
	ADC_MGR <--  ADC: result

@enduml
**Further calibration is needed based on ADC configuration
**\return uncalibrated ADC conversion result (range: 0 to 1023)
**\return ADC_INVALID_CONVERSION_RESULT if ADC busy or it could not be configured
********************************************************/
{

  //while(ADC_startConversion() != ADC_INIT_SUCCESS); /* if ADC busy try again */
	ADC_startConversion();
  __delay_cycles(20); /* TODO: non software delay */

  ADC_stopConversion();

  volatile uint16 result = ADC_getConversionResult();

  return result;

}
