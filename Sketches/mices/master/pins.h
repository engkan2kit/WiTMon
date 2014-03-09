#ifndef _PINS_H
#define _PINS_H

#include "Arduino.h"

/**
 * SPI pins -- Modified for GIZDUINO-X
 */

//#define MEGA



#define LED0	6	
#define LED1	7	
#define LED2	8	


#ifdef MEGA

#define SPI_SS   10     // PB0 = SPI_SS Pin_10
#define SPI_MOSI 11     // PB2 = MOSI Pin_11
#define SPI_MISO 12     // PB3 = MISO
#define SPI_SCK  13     // PB1 = SCK
#define GDO0     2     // PE4= INT0

#define PORT_SPI_MISO  PINB
#define BIT_SPI_MISO  3

#define PORT_SPI_SS  PORTB
#define BIT_SPI_SS   0

#define PORT_GDO0  PINE
#define BIT_GDO0 4



 //ADE SS pin
#define ADE_SS 9

 //ADE IRQ pin
#define ADE_IRQ 3

#else

#define SPI_SS   10     // PB2 = SPI_SS Pin_10
#define SPI_MOSI 11     // PB3 = MOSI Pin_11
#define SPI_MISO 12     // PB4 = MISO
#define SPI_SCK  13     // PB5 = SCK
#define GDO0     2     // PD2 = INT0

#define PORT_SPI_MISO  PINB
#define BIT_SPI_MISO  4

#define PORT_SPI_SS  PORTB
#define BIT_SPI_SS   3

#define PORT_GDO0  PIND
#define BIT_GDO0 2



 //ADE SS pin
#define ADE_SS 9    //PB1 = ADESS

 //ADE IRQ pin
#define ADE_IRQ 3   //PD3 = INT1

#endif


#endif