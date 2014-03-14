#include <Wire.h>
#include <rtc.h>


DS1307 RTC;

void setup(){
  Serial.begin(57600);
  while(!Serial);
  Serial.println("RTC test");
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()){
    Serial.println("RTC is NOT running!");
    //set date
    //TSTAMP ts=TSTAMP(92,11,14,0,0,0);
    //RTC.adjust(ts); 
  }else{
      
    TSTAMP ts = TSTAMP(1394592506);
    RTC.adjust(ts);
    Serial.println("RTC running!");
  } 
  
}

void loop(){
  TSTAMP now = RTC.now();
  Serial.print(now.unixtime());
  Serial.print("-->");
  Serial.print(now.y);
  Serial.print("-");
  Serial.print(now.m);
  Serial.print("-");  
  Serial.print(now.d);
  Serial.print("  ");
  Serial.print(now.hh);
  Serial.print(":");
  Serial.print(now.mm);
  Serial.print(":");
  Serial.println(now.ss);  
  delay(1000);
}





