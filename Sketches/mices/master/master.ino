#include "regtable.h"
#include "panstamp.h"

const int LED = 4;

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
  Serial.println("MICE Initialized...");
  //Broadcast  Releveant Info @ start up
  for(int i = REGI_PRODUCTCODE;i < REGI_TXINTERVAL;i++){
    getRegister(i)->getData();
    Serial.print("<<::");
    Serial.println(i);
  }
  

}

void loop(){
  
}
