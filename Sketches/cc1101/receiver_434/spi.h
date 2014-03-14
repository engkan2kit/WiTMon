/**
 * Copyright (c) 2011 Daniel Berenguer <dberenguer@usapiens.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panLoader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panLoader; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 03/03/2011
 */

#ifndef _SPI_H
#define _SPI_H

#include "Arduino.h"

/**
 * SPI pins
 */
#define SPI_SS   10     // PB0 = SPI_SS Pin_10
#define SPI_MOSI 11     // PB2 = MOSI Pin_11
#define SPI_MISO 12     // PB3 = MISO 
#define SPI_SCK  13     // PB1 = SCK
#define GDO0     21     // PD2 = INT0

#define PORT_SPI_MISO  PINB
#define BIT_SPI_MISO  3

#define PORT_SPI_SS  PORTB
#define BIT_SPI_SS   0

#define PORT_GDO0  PIND
#define BIT_GDO0  0

/**
 * Macros
 */
// Wait until SPI operation is terminated
#define wait_Spi()  while(!(SPSR & _BV(SPIF)))

/**
 * Class: SPI
 * 
 * Description:
 * Basic SPI class
 */
class SPI
{
  public:
    /**
     * init
     * 
     * SPI initialization
     */
    void init();

    /**
     * send
     * 
     * Send byte via SPI
     * 
     * 'value'  Value to be sent
     * 
     * Return:
     *  Response received from SPI slave
     */
    byte send(byte value);
};
#endif


