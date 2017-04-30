/*
 * application.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 *      TODO:
 *      	int to bytes function?
 *      	watchdog period configuration based on received conf from central node
 *			check global variables to see if they have to be globals
 *			create a buffer for measurement results and fix APP_cyclic logic for packet creation (currently synchronous result processing?)
 *			variables to proper scopes to free up RAM
 *			add configuration mode (sends config update request packet-> RF to receiver mode -> config watchdog period / dBM? based on response), do it twice as often as meaurement cycle?
 *			configuration mode configures: which measurements to make (cmdqueue)
 *										   wakeup period
 *										   RSSI?
 *										   on demand measurement
 *			configuration mode has a header, data bytes have special definitions: for example bit 0 - 2 tell which measurements to make bit 3 is on demand measurement(modifies the fMeasurement
 *			flag internally and so on
 *	Reminder: static storage class restricts variables scope to the file its declared in
 */

/** @file
**	\brief
**
@startuml{APP.png}
WDT->SYSTEM: 2rata
Applikatsioon -> Applikatsioon: lisa k2sud ADCMGR j2rjekorda
Applikatsioon -> Applikatsioon: kontrolli tulemuste muutujaid
Applikatsioon -> Applikatsioon: lisa tulemused saatmispaketti
Applikatsioon -> Applikatsioon: lisa eelmise 2rkveloleku RSSI n2itajad paketti
Applikatsioon -> MRF: 2rata RF Radio_Set_Mode(RADIO_STANDBY)
Applikatsioon -> MRF: saada moodustatud pakett Radio_Tx
Applikatsioon -> MRF: pane RF kuulama Radio_Set_Mode(RADIO_RX)/ Radio_Rx
... kuula 10ms ...
Applikatsioon -> MRF: Radio_Set_Mode(RADIO_SLEEP)
Applikatsioon -> Applikatsioon: parsi saadud pakett
Applikatsioon -> MRF: seadista dBm (pole valmis veel)
Applikatsioon -> Applikatsioon: seadista systeem (millised suurused m66ta, on demand m66mised (kumbki pole valmis veel))
Applikatsioon -> WDT: seadista magamisintervall (PCKT_TYPE_CONF p6his configureerimist pole valmis veel)
Applikatsioon -> SYSTEM: magama
@enduml
**
**
**/

#include "application.h"
#include "ADCMGR.h"
#include "watchdog.h"

#include "network.h"
#include "general.h"

// Drivers
#include "uart.h"
#include "spi.h"
#include "radio.h"

static uint8 parsed[3]; /**< temporary received command buffer, global for the ease of debugging */
uint8 payload_length = 0; /**< temporary received command buffer, global for the ease of debugging */
uint16 fMeasurement = 1; /**< measurement flag */
uint16 fCmdAdded = 0; /**< commands added flag */
uint16 fCofig = 0; /**< periodic configuration flag? not yet used*/
/*uint8 baidid[2];*/

TimerStruct esimene; /**< timer variable for system work cycle measuring */

static uint8 rssi_ENV = 0; /**< Channel noise RSSI value? */ /*transfer to local scope if dBm will be modified right after receiving it */
static uint8 rssi_RX = 0; /**< Signal RSSI value? */ /*transfer to local scope if dBm will be modified right after receiving it */
static uint32 system_sleep_period_in_min = 5; /**< current sleep period in minutes, default 1 minute */ /*transfer to local scope if no data permanence needed */

void
APP_cyclic()
{

	if(fMeasurement == 1)/* if measurement mode */
	{
		if(fCmdAdded == 0)
		{

			cmdQueue_t  *queue = ADCMGR_getCmdQueue();
			ADCMGR_addCmdToQueue(queue, MEASURE_TEMP);
			ADCMGR_addCmdToQueue(queue, MEASURE_TEMP);
			ADCMGR_addCmdToQueue(queue, MEASURE_BATTERY);
			fCmdAdded = 1; /* commands added */

		}

		if(temperature != 0) /* temperature measured? */
		{

			if((payload_length+3) < RF_BUFFER_SIZE)
			{

				uint8 baidid[2]; /* array for measurement partitioning, clearing needed? */
				baidid[0] = (temperature >> 8); /* upper byte of measurement */
				baidid[1] = temperature; /* lower byte of measurement */
				temperature = 0; /**/

				/* add to packet */
				TxPacket[payload_length++] = PKCT_TYPE_TEMPERATURE;
				TxPacket[payload_length++] = baidid[0];
				TxPacket[payload_length++] = baidid[1];

			}

		}

		if(battery != 0)/*battery voltage level measured?*/
		{

			if((payload_length+3) < RF_BUFFER_SIZE)
			{

				uint8 baidid[2];
				baidid[0] = (battery >> 8);
				baidid[1] = battery;
				battery = 0;

				/* add to packet */
				TxPacket[payload_length++] = PCKT_TYPE_VOLTAGE;
				TxPacket[payload_length++] = baidid[0];
				TxPacket[payload_length++] = baidid[1];

			}

		}

		if((humidity != 0))/*humidity measured?*/
		{

			if((payload_length+3) < RF_BUFFER_SIZE)
			{

				uint8 baidid[2];
				baidid[0] = (humidity >> 8);
				baidid[1] = humidity;
				humidity = 0;

				/* add to packet */
				TxPacket[payload_length++] = PKCT_TYPE_HUMIDITY;
				TxPacket[payload_length++] = baidid[0];
				TxPacket[payload_length++] = baidid[1];

			}

		}

		if(payload_length == 9) /* is the measurements packet ready to be sent? */
		{

		#if (TRANSMITTER)

					uint8 len;
					/* add previous communications' RSSI data to packet, adds zeroes on first system cycle */
					TxPacket[payload_length++] = PKCT_TYPE_RSSI;
					TxPacket[payload_length++] = rssi_ENV;
					TxPacket[payload_length++] = rssi_RX;

					/* Send data over radio */
					Radio_Set_Mode(RADIO_STANDBY);
					Radio_Tx(TxPacket, payload_length, ADDR_REMOTE, &error);
					payload_length = 0;
					/*get response */
					Radio_Set_Mode(RADIO_RX);
					timer_initCount(&esimene);
					/* get sent packet and its  RSSI values */
					if (Radio_Rx(RxPacket, &len, 10, &rssi_RX, &error)) {

						/* If error */
						if (error == ERR_RX_WRONG_LENGTH) {
							UART_Send_Data("!RF reInit!\r\n");
							Radio_Init(RF_DATA_RATE, TX_POWER, RF_CHANNEL, &error);
						}

					} else { /* No error */

						uint8 parsed_len = 0; /* parsed command lists length */
						uint8 offset = 3; /* data start offset */

						/* Print out received packet DEBUG */
						UART_Send_Data("\r\nReceiving:");
						for (cntr = 0; cntr < len; ++cntr)
						{
							#if (DEBUG_RF) /* debug */
								UART0_Send_ByteToChar(&(RxPacket[cntr]));
							#endif
							uint8 header_index = (cntr + offset);

							if( header_index < len) /* package parsing TODO: check if clause fits the occasion */
							{
								/* TODO: add dBm changing based on received RSSI, figure out the  algorithm to do it */
								if(RxPacket[header_index] == 0x06) /*check if  header matches the sleep period one, TODO: add period changing PCKT type to configuration header */
								{
									/*TODO: change the watchdog timer interval*/
								}
								parsed[cntr] = RxPacket[header_index]; /*get the parsed header from packet*/
								offset += 2;
								parsed_len++;

							}
						}

						#if (DEBUG_RF) /* debug */
							for (cntr = 0; cntr < parsed_len; ++cntr)
							{
								UART_Send_Data("\r\nParsed headers:");
								UART0_Send_ByteToChar(&(parsed[cntr]));
							}
							// Get RSSI reading

							rssi_ENV = Radio_Get_RSSI();
							UART_Send_Data("\r\nRSSI env | rx: ");
							UART0_Send_ByteToChar(&(rssi_ENV));
							UART_Send_Data(" ");
							UART0_Send_ByteToChar(&(rssi_RX));
							Radio_Set_Mode(RADIO_SLEEP);
						#endif

					}
		#endif	/* END: TRANSMITTER */
					timer_getElapsedTime(&esimene);
					uint8 loendur;

					/* clear the packet,as it's permanently stored in ram, find a better way to clear? */
					for (loendur = 11; loendur > 0; loendur--)
					{
						TxPacket[0] = 0;
					}

			WDT_setWatchdog(system_sleep_period_in_min); /* set watchdog period */
			fCmdAdded = 0; /* clear commands flag */
			fMeasurement = 0; /* clear measurement flag */
			_BIS_SR(LPM3_bits + GIE);

		}

	}

}
