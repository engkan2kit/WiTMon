#include <cc1101.h>
#include <EEPROM.h>

const int LED0 = 4;
// The syncWord of sender and receiver must be the same
byte syncWord[] = {19, 9};
byte senderAddress = 4;
byte receiverAddress = 0;

// The connection to the hardware chip CC1101 the RF Chip
CC1101 cc1101;

// counter to get increment in each loop
byte counter;
/**
* Let the LED Output blink one time.
* 
* With small pause after the blink to see two consecutive blinks. 
*/
void blinker(){
      digitalWrite(LED0, HIGH);
      delay(100);
      digitalWrite(LED0, LOW);
      delay(100);
}

/**
* The setup method gets called on start of the system.
*/
void setup()
{
  Serial.begin(38400);
  Serial.println("start");

  // setup the blinker output
  pinMode(LED0, OUTPUT);
  digitalWrite(LED0, LOW);

  // blink once to signal the setup
  blinker();
  
  // reset the counter
  counter=0;
  
  // initialize the RF Chip
  cc1101.init();
  cc1101.setSyncWord(syncWord, false);
  cc1101.setDevAddress(senderAddress, false);
  Serial.println("device initialized");

  Serial.print("set sender address to ");
  Serial.println(senderAddress);
  Serial.println("done");
}

/**
* The loop method gets called on and on after the start of the system.
*/
void loop()
{
  Serial.println("loop");
  
  CCPACKET data;
  data.length=2;
  if(counter<10)
    counter++;
  else
    counter = 0;
  // the first byte in the data is the destination address
  // it must match the device address of the receiver
  Serial.println("set address to ");
  data.data[0]=receiverAddress;
  data.data[1]=counter;
  if(cc1101.sendData(data)){
    Serial.print("ok ");
    Serial.println(counter);
    for(int j=0; j<counter; j++){
      blinker();
    }
  }else{
    Serial.print("failed ");
    Serial.println(counter);    
    blinker();
    blinker();
  }  
  Serial.println("loop done");    
  delay(2000);
}
