#include <Wire.h>

#include "regtable.h"
#include "panstamp.h"


#include "ADE7758.h"

//#include "ADE7758Dummy.h"



#define alertCounts 5


const int LED = 9;
byte alertOVAC_ctr=0;
byte alertOVBC_ctr=0;
byte alertUVAC_ctr=0;
byte alertUVBC_ctr=0;
byte alertOIAC_ctr=0;
byte alertOIBC_ctr=0;
byte alertsCounter=0;
unsigned int min_ctr=0;


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

void alertRoutine()
{
  long thresh=0,ADErms;
  ADErms = ADE.VRMS(PHASE_A);
  thresh = ((long)(regTable[REGI_THRESHOLD]->value[0]))<<16 | ((long)(regTable[REGI_THRESHOLD]->value[1]))<<8 | (regTable[REGI_THRESHOLD]->value[2]);
  if (ADErms>thresh) //high voltage AC
  {
     alertOVAC_ctr++;
  }
  thresh = ((long)(regTable[REGI_THRESHOLD]->value[6]))<<16 | ((long)(regTable[REGI_THRESHOLD]->value[7]))<<8 | (regTable[REGI_THRESHOLD]->value[8]);
  if (ADErms<thresh) //low voltage AC  
  {
     alertUVAC_ctr++;
  }
  
  ADErms = ADE.VRMS(PHASE_B);
  thresh = ((long)(regTable[REGI_THRESHOLD]->value[3]))<<16 | ((long)(regTable[REGI_THRESHOLD]->value[4]))<<8 | (regTable[REGI_THRESHOLD]->value[5]);
  if (ADErms>thresh) //high voltage BC
  {
     alertOVBC_ctr++;
  }
  
  thresh = ((long)(regTable[REGI_THRESHOLD]->value[9]))<<16 | ((long)(regTable[REGI_THRESHOLD]->value[10]))<<8 | (regTable[REGI_THRESHOLD]->value[11]);
  if (ADErms<thresh) //low voltage BC 
  {
     alertUVBC_ctr++;
  }
  ADErms = ADE.IRMS(PHASE_A);
  thresh = ((long)(regTable[REGI_THRESHOLD]->value[12]))<<16 | ((long)(regTable[REGI_THRESHOLD]->value[13]))<<8 | (regTable[REGI_THRESHOLD]->value[14]);
  if (ADErms>thresh) //high current A 
  {
     alertOIAC_ctr++;
  }

  ADErms = ADE.IRMS(PHASE_B);
  thresh = ((long)(regTable[REGI_THRESHOLD]->value[15]))<<16 | ((long)(regTable[REGI_THRESHOLD]->value[16]))<<8 | (regTable[REGI_THRESHOLD]->value[17]);
  if (ADErms>thresh) //high current B
  {
     alertOIBC_ctr++;
  }  
  
  if (alertOVAC_ctr > alertCounts || alertOVBC_ctr>alertCounts || alertUVAC_ctr>alertCounts || alertUVBC_ctr>alertCounts || alertOIAC_ctr>alertCounts || alertOIBC_ctr>alertCounts)
  {
      getRegister(REGI_ALERTS)->getData();
      alertsCounter=0;
      alertOVAC_ctr=0;
      alertOVBC_ctr=0;
      alertUVAC_ctr=0;
      alertUVBC_ctr=0;
      alertOIAC_ctr=0;
      alertOIBC_ctr=0;
  }
  alertsCounter++;
  if (alertsCounter>10)
  {
      alertsCounter=0;
      alertOVAC_ctr=0;
      alertOVBC_ctr=0;
      alertUVAC_ctr=0;
      alertUVBC_ctr=0;
      alertOIAC_ctr=0;
      alertOIBC_ctr=0;
  }
  
}

void setup()
{
  pinMode(LED,OUTPUT);
  ADE.begin();
  Serial.begin(38400);
  while(!Serial){};
  blinker();
  // Init panStamp
  panstamp.init();
  //panstamp.enableRepeater(4);
  if(panstamp.cc1101.devAddress == 0xFF){
    Serial.println("Setting Address to default 0x0A");
    panstamp.cc1101.setDevAddress(0x0A,true);
  }
  
  //rtc.begin();
  Serial.flush();
  Serial.println("MICE Initialized...");
  //Broadcast  Releveant Info @ start up
  getRegister(REGI_PRODUCTCODE)->getData();
  //getRegister(REGI_DEVADDRESS)->getData();
}

void loop(){
  delay(1000);
  min_ctr++;
  if (min_ctr>=1)
  {
    alertRoutine();
    getRegister(REGI_RMS)->getData();
    Serial.println("Sent");
    min_ctr=0;
  }
  blinker();
}

