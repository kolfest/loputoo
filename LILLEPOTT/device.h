/*
 * device.h
 *
 *  Created on: 2. apr 2017
 *      Author: Karl
 */

#ifndef DEVICE_H_
#define DEVICE_H_



typedef unsigned long  uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

typedef signed long    int32;
typedef signed short   int16;
typedef signed char    int8;

/*
#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)

*/
/* system registers */

/* BCS+ */

extern uint16 DCOCTL; /* = 0x60;*/
extern uint16 BCSCTL1; /* = 0x87;*/
extern uint16 BCSCTL2; /* = 0x00; */
extern uint16 BCSCTL3; /*= 0x05;*/
extern uint16 SR; /*= 0x00;*/
extern uint16 IFG1; /*= 0x02; *//* reset with PUC */

/* WDT */
extern uint32 WDTCTL; /* WDTCTL = 0x6900; */

/* ADC */
uint16 ADC10CTL0;
uint16 ADC10CTL1;

/* TIMER */


/* system configuration bits */
//#define SCG1 (0x0080)
#define OFIFG (0x02)
#define CALBC1_1MHZ (0x86)
#define CALDCO_1MHZ (0xC0)
#define SELM_0 (0x00)
#define LFXT1S_0 (0x00)
#define DIVA_0 (0x00)

/* ADC */
#define SREF_1 		(1*0x2000u)
#define ADC10SHT_3 	(3*0x800u)
#define REFON	 	(0x020)
#define REF2_5V		(0x040)
#define ADC10DIV_0	(0*0x20u)
#define INCH_11		(11*0x1000u)
#define INCH_10		(10*0x1000u)

/* WDT */
#define WDTIE                  (0x01)
#define WDTPW                  (0x5A00)
#define WDTIS0                 (0x0001)
#define WDTIS1                 (0x0002)
#define WDTSSEL                (0x0004)
#define WDTCNTCL               (0x0008)
#define WDTTMSEL               (0x0010)
#define WDTNMI                 (0x0020)
#define WDTNMIES               (0x0040)
#define WDTHOLD                (0x0080)
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL)

/*
 * Stub for register setting
*/

//void _bis_SR_register_double(uint16);

#endif /* DEVICE_H_ */
