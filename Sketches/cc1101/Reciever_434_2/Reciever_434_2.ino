#include <cc1101.h>
#include <EEPROM.h>



// The LED is wired to the Arduino Output 4 (physical panStamp pin 19)
#define LEDOUTPUT 4
// The syncWord of sender and receiver must be the same
byte syncWord[] = {19, 9};
byte receiverAddress = 6;

// The connection to the hardware chip CC1101 the RF Chip
CC1101 cc1101;

// a flag that a wireless packet has been received 
volatile boolean packetAvailable = false;         

/**
* Let the LED Output blink one time.
* 
* With small pause after the blink to see two consecutive blinks. 
*/
void blinker(){
      digitalWrite(LEDOUTPUT, HIGH);
      delay(100);
      digitalWrite(LEDOUTPUT, LOW);
      delay(100);
}

/**
* Handle interrupt from CC1101 (INT0)
*/
void cc1101signalsInterrupt(void){
  // set the flag that a package is available
  packetAvailable = true;
}

/**
* The setup method gets called on start of the system.
*/
void setup()
{
  Serial.begin(38400);
  Serial.println("start");

  // setup the blinker output
  pinMode(LEDOUTPUT, OUTPUT);
  digitalWrite(LEDOUTPUT, LOW);

  // blink once to signal the setup
  blinker();
  
  // initialize the RF Chip
  cc1101.init();
  cc1101.writeReg(0x02,0x06);
  cc1101.setSyncWord(syncWord, false);
  
  // this device address need to match the target address in the sender
  cc1101.setDevAddress(receiverAddress, false);
  cc1101.enableAddressCheck(); // you can skip this line, because the default is to have the address check enabled
  cc1101.setRxState();
  // Enable wireless reception interrupt
  attachInterrupt(0, cc1101signalsInterrupt, RISING);
  Serial.println("device initialized");

  Serial.println("setup done");
  
  //Serial.print("CC1101_PARTNUM"); //cc1101=0
  //Serial.println(cc1101.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
  //Serial.print("CC1101_VERSION"); //cc1101=4
  //Serial.println(cc1101.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
  //Serial.print("CC1101_MARCSTATE");
  //Serial.println(cc1101.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);
}

//routine for reading LQI
void ReadLQI()
{
  byte lqi=0;
  byte value=0;
  lqi=(cc1101.readReg(CC1101_LQI, CC1101_STATUS_REGISTER));
  value = 0x3F - (lqi & 0x3F);
  Serial.print("CC1101_LQI: ");
  Serial.println(value);
}

//routine for reading RSSI
void ReadRSSI()
{
  byte rssi=0;
  byte value=0;
  
  rssi=(cc1101.readReg(CC1101_RSSI, CC1101_STATUS_REGISTER));
  
  if (rssi >= 128)
  {
    value = 255 - rssi;
    value /= 2;
    value += 74;
  }else{
    value = rssi/2;
    value += 74;
  }
  Serial.print("CC1101_RSSI: ");
  Serial.println(value);
}




/**
* The loop method gets called on and on after the start of the system.
*/
void loop()
{
  if(packetAvailable){
    // clear the flag
    packetAvailable = false;
    
    CCPACKET packet;
    
    // Disable wireless reception interrupt
    detachInterrupt(0);
    if(cc1101.receiveData(&packet) > 0){
      if (packet.crc_ok && packet.length > 1){
        Serial.print("packet: len");
        Serial.print(packet.length);
        Serial.print(" data1: ");
        Serial.println(packet.data[1]);
        for(int j=0; j<packet.data[1]; j++){
          blinker();
        }
        ReadLQI();
        ReadRSSI();
      }
    }
    
    // Enable wireless reception interrupt
    attachInterrupt(0, cc1101signalsInterrupt, FALLING);
  }
}


