/*
 * converter.h
 *
 *  Created on: 27. märts 2017
 *      Author: Karl
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "system.h"

#define ADC_TEMP 1
#define ADC_HUMIDITY 2
#define ADC_BATTERY 3

extern uint8 c_ADC_REF_SETTLE;
extern uint8 c_INVALID_CONFIGURATION;
extern uint8 configuration;

enum
{
  ADC_CONFIG_FAILURE = 0, ADC_CONFIG_SUCCESS = 1, NUMBER_OF_ADC_CONFIG_STATES
} commandType2;

uint8 ADC_configureADC(uint8 configuration);

void ADC_cyclic();

#endif /* CONVERTER_H_ */
