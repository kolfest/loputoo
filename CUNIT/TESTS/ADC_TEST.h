/*
 * ADC_TEST.h
 *
 *  Created on: 5. apr 2017
 *      Author: Karl
 */

#ifndef ADC_TEST_H_
#define ADC_TEST_H_

void
test_ADC_configureADC ();

void
test_ADC_measure();

void
test_ADC_startConversion();

void
test_checkIfADCON();

void
test_ADC_stopConversion();

void
test_ADC_getConversionResult();

void
test_checkIfADCBusy();

int
init_ADCsuite (void);

int
clean_ADCsuite (void);



#endif /* ADC_TEST_H_ */
