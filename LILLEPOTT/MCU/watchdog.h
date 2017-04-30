/*
 * watchdog.h
 *
 *  Created on: 28. märts 2017
 *      Author: Karl
 */
#include "system.h"

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#define WDT_SUCCESS 1
#define WDT_ERR 2

void WDT_configure();

uint8 WDT_setWatchdog(uint32 period);

uint32 WDT_getCurrentPeriod();

#endif /* WATCHDOG_H_ */
