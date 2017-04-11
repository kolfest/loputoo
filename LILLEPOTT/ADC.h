/*
 * converter.h
 *
 *  Created on: 27. märts 2017
 *      Author: Karl
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "system.h"

#define ADC_MEASURE_TIMEOUT -1
#define ADC_INVALID_CONVERSION_RESULT -1
#define ADC_INIT_SUCCESS 0
#define ADC_TEMP 1
#define ADC_HUMIDITY 2
#define ADC_BATTERY 3
#define ADC_BUSY 5

extern uint8 c_ADC_REF_SETTLE;
extern uint8 c_INVALID_CONFIGURATION;
extern uint8 configuration;

enum
{
  ADC_CONFIG_FAILURE = 0, ADC_CONFIG_SUCCESS = 1, ADC_INVALID_INPUT = 2, NUMBER_OF_ADC_CONFIG_STATES
} commandType2;

float ADC_calibrateResult(uint16 *result);

uint8 checkIfADCBusy();

uint8 checkIfADCON();

uint8 checkIsBitSet(uint16 registerr, uint16 position);

uint8 ADC_configureADC(uint8 configuration);

float ADC_measure(uint8 configuration);

uint8 ADC_startConversion();

void ADC_cyclic();

#endif /* CONVERTER_H_ */
