/*
 * converter.c
 *
 *  Created on: 27. märts 2017
 *      Author: Karl
 *      TODO:
 *      implement dynamic Refrence settling delay based on timer
 */
#include "ADC.h"

uint8 c_ADC_REF_SETTLE = 0;
uint8 c_INVALID_CONFIGURATION = 1;
uint8 configuration = ADC_TEMP;

uint8
/*******************************************************
** returns error if refrence not settled, success otherwise
**
**
********************************************************/
ADC_configureADC(uint8 configuration)
{
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + REF2_5V; /*VR+ = VREF+ and VR- = VSS, maximum sample-and-hold time, Turn internal refrence generator on, refrence voltage 2.5V */



	if (c_INVALID_CONFIGURATION) /* configuration checking test double, needs proper implementation */
	{
		return ADC_CONFIG_FAILURE;
	}
	  if (c_ADC_REF_SETTLE)/* adc refrence settle test double, needs proper implementation */
	{
	    switch (configuration)
	    {

		    case ADC_TEMP:
			    ADC10CTL1 = INCH_10 + ADC10DIV_0; /* select channel for internal temp sensor */
			    return ADC_CONFIG_SUCCESS;
			    break;

		    case ADC_HUMIDITY:
			    ADC10CTL1 = INCH_10 + ADC10DIV_0; /* select A0 */
			    return ADC_CONFIG_SUCCESS;
			    break;

		    case ADC_BATTERY:
			    ADC10CTL1 = INCH_11 + ADC10DIV_0; 	/* Analog channel (Vcc-Vss)/2 */
			    return ADC_CONFIG_SUCCESS;
			    break;

	    }
	}
	return ADC_CONFIG_FAILURE;
}

void ADC_cyclic()
{

}
