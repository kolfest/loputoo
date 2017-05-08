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
[*] --> INIT
        INIT--> APP_MEASURE_TEMP
	APP_MEASURE_TEMP --> APP_MEASURE_HUM
        APP_MEASURE_TEMP --> APP_MEASURE_TEMP
        APP_MEASURE_HUM --> APP_MEASURE_HUM
	APP_MEASURE_HUM--> APP_MEASURE_BATTERY
	APP_MEASURE_BATTERY --> TRANSMIT
        APP_MEASURE_BATTERY --> APP_MEASURE_BATTERY
	TRANSMIT -->  RECEIVE
        RECEIVE --> PARSE_HEADERS
	PARSE_HEADERS --> PREPARE_TO_SLEEP
        PREPARE_TO_SLEEP --> SLEEP
        SLEEP -> INIT
@enduml
**
**
**/

#include <wdt.h>
#include "application.h"
#include "ADCMGR.h"
#include "network.h"
#include "general.h"

// Drivers
#include "uart.h"
#include "spi.h"
#include "radio.h"

typedef enum APP_State
{

  SLEEP = 0,
  INIT = 1,
  TRANSMIT = 2,
  RECEIVE = 3,
  APP_MEASURE_TEMP = 4,
  APP_MEASURE_HUM = 5,
  APP_MEASURE_BATTERY = 6,
  ADJUST_RF_POWER = 7,
  PREPARE_TO_SLEEP = 8,
  PARSE_HEADERS = 9,
  NUMBER_OF_APP_STATES

}APP_State;

static uint8 parsed[3]; /**< temporary received command buffer, global for the ease of debugging */
static uint8 payload_length = 0; /**< */
static APP_State state = INIT;

//TimerStruct esimene; /**< timer variable for system work cycle measuring */
static uint8 rssi_ENV = 0; /**< Channel noise RSSI value? */ /*transfer to local scope if dBm will be modified right after receiving it */
static uint8 rssi_rX = 0; /**< Signal RSSI value? */ /*transfer to local scope if dBm will be modified right after receiving it */
static uint8 rssi_RX = 0;
static uint32 system_sleep_period_in_min = 1; /**< current sleep period in minutes, default 1 minute */ /*transfer to local scope if no data permanence needed */
static uint8 len; /**< length of received package */

void
APP_cyclic()
{
	switch(state)
	{
		case SLEEP:
		{

			state = INIT;
			break;

		}

		case INIT:
		{
			payload_length = 0;
			rssi_ENV = Radio_Calculate_RSSI(Radio_Get_RSSI());
			Radio_Set_Mode(RADIO_SLEEP);
			cmdQueue_t  *queue = ADCMGR_getCmdQueue();

			ADCMGR_addCmdToQueue(queue, MEASURE_TEMP);
			ADCMGR_addCmdToQueue(queue, MEASURE_HUMIDITY);
			ADCMGR_addCmdToQueue(queue, MEASURE_BATTERY);

			state = APP_MEASURE_TEMP;
			break;
		}

		case APP_MEASURE_TEMP:
		{
			uint16 temperature = ADCMGR_getTemp();
			if( temperature != 0 ) /* temperature measured? */
			{

				if((payload_length + 3) < RF_BUFFER_SIZE)/*see if data can be added to packet */
				{

					uint8 baidid[2]; /* array for measurement partitioning, clearing needed? */
					baidid[0] = (temperature >> 8); /* upper byte of measurement */
					baidid[1] = temperature; /* lower byte of measurement */
					temperature = 0; /**/

					/* add to packet */
					TxPacket[payload_length++] = PKCT_TYPE_TEMPERATURE;
					TxPacket[payload_length++] = baidid[0];
					TxPacket[payload_length++] = baidid[1];
					state = APP_MEASURE_HUM;
					break;
				}

			}


			//if(payload_length == 6)/* workaround for now */
			//{
			//	state =  APP_MEASURE_BATTERY;
			//	break;
			//}
			state = APP_MEASURE_TEMP;
			break;
		}
		case  APP_MEASURE_HUM:
		{
			uint16 humidity = ADCMGR_getHum();
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
						state = APP_MEASURE_BATTERY;
						break;
					}

				}
				state = APP_MEASURE_HUM;
				break;
		}

		case  APP_MEASURE_BATTERY:
		{
			uint16 battery = ADCMGR_getBattery();

			if(battery != 0)/* battery voltage level measured?*/
			{

					if((payload_length + 3) < RF_BUFFER_SIZE)
					{

						uint8 baidid[2];
						baidid[0] = (battery >> 8);
						baidid[1] = battery;
						battery = 0;

						/* add to packet */
						TxPacket[payload_length++] = PCKT_TYPE_VOLTAGE;
						TxPacket[payload_length++] = baidid[0];
						TxPacket[payload_length++] = baidid[1];
						state = TRANSMIT;
						break;
					}

				}

			state = APP_MEASURE_BATTERY;
			break;
		}
		case TRANSMIT:
		{

			/* add previous communications' RSSI data to packet, adds zeroes on first system cycle */
			TxPacket[payload_length++] = PKCT_TYPE_RSSI;
			TxPacket[payload_length++] = rssi_ENV;
			TxPacket[payload_length++] = rssi_RX;

			/* Send data over radio */
			Radio_Set_Mode(RADIO_STANDBY);
			Radio_Tx(TxPacket, payload_length, ADDR_REMOTE, &error);

			state = RECEIVE;
			break;
		}
		case RECEIVE:
		{

			Radio_Set_Mode(RADIO_RX);
			/* get sent packet and its  RSSI values */
			if (Radio_Rx(RxPacket, &len, 5, &rssi_rX, &error)) {

				/* If error */
				if (error == ERR_RX_WRONG_LENGTH) {
					UART_Send_Data("!RF reInit!\r\n");
					Radio_Init(RF_DATA_RATE, TX_POWER, RF_CHANNEL, &error);
				}

			} else
			{ /* No error */
				//rssi_ENV = Radio_Calculate_RSSI(Radio_Get_RSSI());


				#if (DEBUG_RF) /* debug */
					UART_Send_Data("\r\nRSSI env | rx: ");
					UART0_Send_ByteToChar(&(rssi_ENV));
					UART_Send_Data(" ");
					UART0_Send_ByteToChar(&(rssi_RX));
				#endif
				Radio_Set_Mode(RADIO_SLEEP);
			}
			state = PARSE_HEADERS;
			break;
		}
		case PARSE_HEADERS:
		{
			#if (DEBUG_RF) /* debug */
				UART_Send_Data("\r\nReceived:");
				for (cntr = 0; cntr < len; ++cntr)
				{

					UART0_Send_ByteToChar(&(RxPacket[cntr]));

				}
			#endif

			uint8 parsed_len = 0; /* parsed command lists length */
			uint8 offset = 3; /* data start offset */

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

							break;
										/*TODO: change the watchdog timer interval*/
						}
						if(RxPacket[header_index] == 0x04) /*check if  header matches the sleep period one, TODO: add period changing PCKT type to configuration header */
							{

								uint8 off = (header_index + 1);
								rssi_RX = RxPacket[off];
								break;
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
			#endif

			state = PREPARE_TO_SLEEP;
			break;
		}

		case PREPARE_TO_SLEEP:

		{	uint8 loendur;
			for (loendur = 11; loendur > 0; loendur--)
			{
				TxPacket[loendur] = 0;
			}
			for (loendur = 11; loendur > 0; loendur--)
			{
				RxPacket[loendur] = 0;
			}
			WDT_setWatchdog(system_sleep_period_in_min); /* set watchdog period */
			state = SLEEP;
			_BIS_SR(LPM3_bits + GIE);

		}
	}
}
