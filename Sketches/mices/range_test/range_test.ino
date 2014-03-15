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
#include "swcommand.h"

/**
 * setup
 *
 * Arduino setup function
 */
const int LED = 4;
unsigned short int counter = 0;
boolean packetAvailable = false;
byte y = 0,x=0;
byte j[1];

void isrINT0event(void)
{
  packetAvailable = true;
  Serial.print("");
}

#define enableINT0irq()    attachInterrupt(0, isrINT0event, FALLING); digitalWrite(LED, LOW)
#define disableINT0irq()   detachInterrupt(0); digitalWrite(LED, HIGH)

void blinker(){
  delay(200);
  digitalWrite(LED,HIGH);
  delay(200);
  digitalWrite(LED,LOW);
} 


/*
void sendTestData(){
  SWPACKET swp;
  SWDATA swd;
  swp.destAddr = 0x0A;
  swp.srcAddr = 0x01;
  swp.function = SWAPFUNCT_CMD;
  swp.addrType = SWAPADDR_SIMPLE;
  swp.regAddr = 0x01;
  swp.regId = 0x0A;
  for(int i = 0;i < 100; i++){
    swp.value->data = &i;
    swp.value.length = sizeof(int);
    swp.value.type = 
  }
}
*/

void setup()
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  while(!Serial){};
  blinker();
  // Init panStamp
  panstamp.init();
  panstamp.cc1101.disableAddressCheck();
  enableINT0irq();
  Serial.println("Range Test:: Master");
  // Transmit product code
  //getRegister(REGI_PRODUCTCODE)->getData();
  //initialize
  blinker();
  blinker();
  blinker();  
}

/**
 * loop
 *
 * Arduino main loop
 */
void loop()
{
  if(x < 100){
    j[0]=x;
    SWCOMMAND cmd((char)0x0A,(byte)0x00, (char)0x0A, (byte)0x0B, j, sizeof(j));
    cmd.send();
    blinker(); 
    x++;  
  }
  if (packetAvailable)
  {
    
    // Disable wireless reception interrupt
    disableINT0irq();

    byte i;
    CCPACKET packet;
   
    packetAvailable = false;

    if (panstamp.cc1101.receiveData(&packet) > 0)
    {
      if (packet.crc_ok && packet.length > 5)
      {
        Serial.print("(");
        if (packet.rssi < 0x10)
          Serial.print("0");
        Serial.print(packet.rssi, HEX);
        if (packet.lqi < 0x10)
          Serial.print("0");
        Serial.print(packet.lqi, HEX);
        Serial.print(")");
        for(i=0 ; i<packet.length ; i++)
        {
          if (packet.data[i] < 0x10)
            Serial.print(0, HEX);    // Leading zero
          Serial.print(packet.data[i], HEX);
        }
        Serial.println("");
        y++;
      }
    }
    if(x>=100)
    {
       Serial.print("total packets sent: ");
       Serial.println(x);
       Serial.print("total packets received: ");
       Serial.println(y);
       Serial.print("% of packets loss: ");
       Serial.println(100-(y*100)/x);
    }
    // Enable wireless reception interrupt
    enableINT0irq(); 
  }

}

