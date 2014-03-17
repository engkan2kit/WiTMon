/*
 * mice_stamp
 *
 * Copyright (c) 2011 Daniel Berenguer <dberenguer@usapiens.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panLoader  is free software; you can redistribute it and/or modify
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
 * Creation date: 12/28/2011
 */
 
#include "regtable.h"
#include "panstamp.h"
#include "pins.h"

/**
 * setup
 *
 * Arduino setup function
 */
const int LED = 4;

void blinker(){
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
} 

void setup()
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  while(!Serial){};
  blinker();
  // Init panStamp
  panstamp.init();
  panstamp.swapAddress = 0x0A;
  Serial.println("MICE Initialized...");
  // Transmit product code
  getRegister(REGI_PRODUCTCODE)->getData();
}

/**
 * loop
 *
 * Arduino main loop
 */
void loop()
{
  blinker();
}

