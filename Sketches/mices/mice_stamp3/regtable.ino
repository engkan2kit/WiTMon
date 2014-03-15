/**
 * regtable
 *
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
 * Creation date: 12/28/2011
 */

#include <EEPROM.h>
#include "product.h"
#include "panstamp.h"
#include "regtable.h"

/**
 * Declaration of common callback functions
 */
DECLARE_COMMON_CALLBACKS()

/**
 * Definition of common registers
 */
DEFINE_COMMON_REGISTERS()

/*
 * Definition of custom registers
 */
byte poleId[1];
REGISTER regPoleId(poleId,sizeof(poleId),&updtPoleId,&setPoleId,SWDTYPE_OTHER,EEPROM_POLE_ID);
byte location[8];
REGISTER regLocation(location,sizeof(location),&updtLocation,&setLocation,SWDTYPE_OTHER,EEPROM_LOCATION);
byte rms[18]; //RMS values of Vac,Vbc, Iac, Ibc 
REGISTER regRms(rms,sizeof(rms),&updtRms,NULL);
byte energy[18]; //real energies, reactive energies and complex energies for AC and BC
REGISTER regEnergy(energy,sizeof(energy),&updtEnergy,NULL);



/**
 * Initialize table of registers
 */
DECLARE_REGISTERS_START()
  &regPoleId,
  &regLocation,
  &regRms,
  &regEnergy
DECLARE_REGISTERS_END()

/**
 * Definition of common getter/setter callback functions
 */
DEFINE_COMMON_CALLBACKS()

/**
 * Definition of custom getter/setter callback functions
 */
const void setPoleId(byte rId,byte *pId){
  memcpy(regTable[rId]->value,pId,sizeof(*regTable[rId]->value)); 
  Serial.print("MICE Pole ID Changed to: ");
  Serial.println(*regTable[rId]->value,HEX);
}

const void updtPoleId(byte rId){
  Serial.print("MICE Pole ID is: ");
  Serial.println(*(regTable[rId]->value),HEX);
}

const void setLocation(byte rId,byte *pId){
  memcpy(regTable[rId]->value,pId,sizeof(*regTable[rId]->value)*8);
  //regTable[rId]->setValueFromBeBuffer(pId); big endian
  ufloat lat,lon;
  for(int i=0;i < 8;i++){
    if(i<4)
      lat.u = lat.u<<8 | *(regTable[rId]->value + i);
    else
      lon.u = lon.u<<8 | *(regTable[rId]->value + i);
  }
  //lon.u = (*regTable[rId]->value) & 0x00000000FFFFFFFF;
  //lat.u = ((*regTable[rId]->value)>>32) & 0x00000000FFFFFFFF;
  Serial.print("MICE location changed to: ");
  //Serial.println(value,HEX);
  Serial.print(lat.f);
  Serial.print(",");
  Serial.println(lon.f);
}

const void updtLocation(byte rId){
  ufloat lat,lon;
  for(int i=0;i < 8;i++){
    if(i<4)
      lat.u = lat.u<<8 | *(regTable[rId]->value + i);
    else
      lon.u = lon.u<<8 | *(regTable[rId]->value + i);
  }
  Serial.print("MICE location is: ");
  //Serial.println(value,HEX);
  Serial.print(lat.f);
  Serial.print(",");
  Serial.println(lon.f);
}

const void updtRms(byte rId){
  // read RMS values of Vac,Vbc, Iac, Ibc
}

const void updtEnergy(byte rId){
  //read 
  
}
