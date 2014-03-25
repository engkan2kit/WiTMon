#include "Arduino.h"
#include "spi.h"
#include "ADE7758Dummy.h"
#include <avr/wdt.h>
int potpin0 =0;
int potpin1 =1;
//public
ADE7758Dummy::ADE7758Dummy(int SSpin):
    _SSpin(SSpin)
{
	
}

void ADE7758Dummy::begin()
{
	

}

int ADE7758Dummy::WattHR(char phase)
{
	return 20000;
}

int ADE7758Dummy::VARHR(char phase)
{
	return 5000;
}

int ADE7758Dummy::VAHR(char phase)
{
	return 25000;
}

long ADE7758Dummy::VRMS(char phase)
{
  char i=0;
  long volts=0;
  volts = analogRead(potpin0) * 2048;
  //average
  return volts;
}

long ADE7758Dummy::IRMS(char phase)
{
  char i=0;
  long current=0;
  current = analogRead(potpin1) * 2048;
  //average
  return current;
}

//private

void ADE7758Dummy::enableChip()
{
    digitalWrite(_SSpin, LOW);
}

void ADE7758Dummy::disableChip()
{
    digitalWrite(_SSpin, HIGH);
}


	
ADE7758Dummy ADE(ADE_SS);