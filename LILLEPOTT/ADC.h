/*
 * converter.h
 *
 *  Created on: 27. m�rts 2017
 *      Author: Karl
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "system.h"
#include "misc.h"

#define ADC_INIT_SUCCESS 0
//#define ADC_TEMP 1
//#define ADC_HUMIDITY 2
//#define ADC_BATTERY 3
#define ADC_BUSY 5

extern uint8 configuration;
uint8 tuli;

typedef enum ADC_confType
{
  ADC_IDLE = 0,
  ADC_TEMP = 1,
  ADC_HUMIDITY = 2,
  ADC_BATTERY = 3
} ADC_confType;

enum
{
  ADC_MEASURE_TIMEOUT = -2,
  ADC_INVALID_CONVERSION_RESULT = -1
} commandType3;

enum
{
  ADC_CONFIG_FAILURE = 0,
  ADC_CONFIG_SUCCESS = 1,
  ADC_INVALID_INPUT = 2,
  NUMBER_OF_ADC_CONFIG_STATES
} commandType2;

float ADC_calibrateResult(uint16 *result);

uint8 checkIfADCBusy();

uint8 checkIfADCON();

uint8 ADC_configureADC(ADC_confType configuration);

float ADC_measure();

uint8 ADC_startConversion();

int16
ADC_getConversionResult();

void ADC_stopConversion();


void ADC_cyclic();

#endif /* CONVERTER_H_ */
