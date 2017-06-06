/*
 * main.h
 *
 *  Created on: 06.02.2015
 *  Modifiedon: 10.04.2015
 *  Author: Mairo Leier, Maksim Gorev
 *
 *  Version: 0.1		10.04.2015
 *  TODO:
 *  *an array to see if the specific leaf has received the new watchdog conf?
 *  *buffer for configurating leaf nodes on request from the PI(configuration header data bits )
 *
 */

/** @file
**	\brief
**
@startuml{AJU.png}
group MEASUREMENT MODE
 LILLEPOTT->AJU:saada m66mised + RSSI n2itajad(esmasel saatmisel sisubaidid nullid)
 LILLEPOTT<-AJU:saadetud paketi RSSI n2itajad
 ... viide 5 minutit ...
 LILLEPOTT->AJU:saada m66mised + RSSI n2itajad
 LILLEPOTT<-AJU:saadetud paketi RSSI n2itajad
end

group ON DEMAND

end

group CONFIGURATION MODE
 LILLEPOTT->AJU:PCKT_TYPE_CONF (bit 0 set ehk update)
 note left
  aktiveerub poole
  magamisperioodi pealt
  pole implementeeritud
 end note
 LILLEPOTT<-AJU:PCKT_TYPE_CONF(korraliku sisuga)
end
@enduml
**
**
**/
/***************************************************************************************************
 *	        Include section					                       		   					       *
 ***************************************************************************************************/

#include "system.h"
#include "network.h"
#include "general.h"

// Drivers
#include "uart.h"
#include "spi.h"
#include "radio.h"

/***************************************************************************************************
 *	        Define section					                       		   					       *
 ***************************************************************************************************/


/***************************************************************************************************
 *	        Prototype section					                       							   *
 ***************************************************************************************************/
crc MISC_crc(uint8 const message[], int nBytes);

/***************************************************************************************************
 *	        Global Variable section  				                            				   *
 ***************************************************************************************************/
uint8 error;
uint8 payload_length;
uint8 cntr;
typedef uint16 crc;
#define POLYNOMIAL 0xBAAD
#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))
/***************************************************************************************************
 *         Main section                                                                            *
 ***************************************************************************************************/
void main(void) {
	error = 0;

	System_Init(&error);
	__enable_interrupt();

	while (1) {

/* TX part */
#if (TRANSMITTER)
		payload_length = 0;

			// Construct the packet
			TxPacket[payload_length++] = 0x01;
			TxPacket[payload_length++] = 0x02;
			TxPacket[payload_length++] = 0x03;

			// Send data over radio
			Radio_Tx(TxPacket, payload_length, ADDR_REMOTE, &error);

			// Print out packet that was sent
			UART_Send_Data("\r\nSending:");
			for (cntr = 0; cntr < payload_length; cntr++) {
				UART0_Send_ByteToChar(&TxPacket[cntr]);
			}

			// Add some delay (around 1sec)
			__delay_cycles(2000000*SYSTEM_SPEED_MHZ);
		}
#endif	/* END: TRANSMITTER */

#if (RECEIVER)
		uint8 len;
		uint8 rssi_env;
		uint8 rssi_rx;
		uint8 payload_length = 0;

		// Put radio into RX mode
		Radio_Set_Mode(RADIO_RX);

		// Receive data from Radio
		if (Radio_Rx(RxPacket, &len, 1000, &rssi_rx, &error)) { //wait for 20ms

			// If error
			if (error == ERR_RX_WRONG_LENGTH) {
				UART_Send_Data("!RF reInit!\r\n");
				Radio_Init(RF_DATA_RATE, TX_POWER, RF_CHANNEL, &error);
			}

		} else { // No error

			/*parse received packet's address and return rssi info */
			uint8 addr_offset = 2; /* offset index for addr parsing */
			uint8 remote_addr = 0; /* received message's note's source address */
			if(MISC_crc(RxPacket, sizeof(RxPacket)) == 0)
			{
				rssi_env = Radio_Get_RSSI(); /* Get RSSI reading (channel noise?) */
				remote_addr = RxPacket[addr_offset];
				TxPacket[payload_length++] = PKCT_TYPE_RSSI;
				TxPacket[payload_length++] = rssi_rx;
				TxPacket[payload_length++] = rssi_env;
				uint16 crc = MISC_crc(TxPacket, sizeof(TxPacket));
				baidid[0] = crc;
				baidid[1] = (crc >> 8);
				Radio_Tx(TxPacket, payload_length, remote_addr, &error);
				TxPacket[payload_length++] = baidid[0];
				TxPacket[payload_length++] = baidid[1];
				 
				for (cntr = 0; cntr < len; ++cntr)
				{
					UART0_Send_ByteToChar(&(RxPacket[cntr]));
				}
			}
			#if (DEBUG_RF)
				UART_Send_Data("\r\nRSSI env | rx: ");
				UART0_Send_ByteToChar(&(rssi_env));
				UART_Send_Data(" ");
				UART0_Send_ByteToChar(&(rssi_rx));
			#endif
		}
	}	/* END: while loop */
#endif	/* RECEIVER */

}		/* END: main */

crc
MISC_crc(uint8 const message[], int nBytes)
{
    crc  remainder = 0;	

    for (int byte = 0; byte < nBytes; ++byte)
    {

        remainder ^= (message[byte] << (WIDTH - 8));
        for (uint8 bit = 8; bit > 0; --bit)
        {

            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    return (remainder);
}
