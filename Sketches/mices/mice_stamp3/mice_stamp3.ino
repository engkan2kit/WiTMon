#include "regtable.h"
#include "panstamp.h"

const int LED = 4;

union ufloat{
  float f;
  unsigned long int u;
};

void blinker(){
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
}

void setup()
{
  pinMode(LED,OUTPUT);
  Serial.begin(38400);
  while(!Serial){};
  blinker();
  // Init panStamp
  panstamp.init();
  if(panstamp.cc1101.devAddress == 0xFF){
    Serial.println("Setting Address to default 0x0A");
    panstamp.cc1101.setDevAddress(0x0A,true);
  }
  Serial.flush();
  Serial.println("MICE Initialized...");
  //Broadcast  Releveant Info @ start up
  getRegister(REGI_PRODUCTCODE)->getData();
  //getRegister(REGI_DEVADDRESS)->getData();
}

void loop(){
  delay(1000);
  blinker();
}

