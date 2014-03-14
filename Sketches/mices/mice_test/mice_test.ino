#include "mices.h"

void blinker(){
  digitalWrite(LED0,HIGH);
  delay(500);
  digitalWrite(LED0,LOW);
  delay(500);
}

void testPins(){
  digitalWrite(MOSI,HIGH);
  digitalWrite(SS,HIGH);
  digitalWrite(SCK,HIGH);
}
void setup(){
  pinMode(LED0,OUTPUT);
  pinMode(MOSI,OUTPUT);
  pinMode(SS,OUTPUT);
  pinMode(SCK,OUTPUT);
  testPins();
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Initializing...");
  delay(2000);
  blinker();
}

void loop(){
  Serial.println("i'm alive");
  blinker();
}
