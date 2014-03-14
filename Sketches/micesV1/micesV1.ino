#include "regtable.h"
#include "panstamp.h"

const int led = 4;

void setup(){

  
    Serial.begin(9600);
    while(!Serial){};
    Serial.println("SWAP STACK TEST");
    Serial.print("Device Product Code: ");
    Serial.println(getRegister(0)->value[0]);
    panstamp.init();
             
}

void loop(){}

