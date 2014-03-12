#include <Wire.h>
#include "rtc.h"
#include <Arduino.h>
 
#ifdef __AVR__
 #include <avr/pgmspace.h>
 #define WIRE Wire
#else
 #define PROGMEM
 #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
 #define WIRE Wire1
#endif

#define DS1307_ADDRESS 0x68

#define SECONDS_PER_DAY 86400L
#define SECONDS_FROM_1970_TO_2000 946684800

const uint8_t daysInMonth [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 };

//Utility Codes
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);
    if (m > 2 && y % 4 == 0)
        ++days;
    return days + 365 * y + (y + 3) / 4 - 1;
}

static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24L + h) * 60 + m) * 60 + s;
}


//*******************************TSTAMP Class*********************************************************//
TSTAMP::TSTAMP(uint8_t year, uint8_t month, uint8_t day,uint8_t hour =0, uint8_t min =0, uint8_t sec =0){
		ss = sec;		//00-59
		mm = min;		//00-59
		hh = hour;		//00-23
		dd = 0;			//01-07
		d = day;		//01-31
		m = month;		//01-12
		y = year;		//00-99	
				
}
	
TSTAMP::TSTAMP(uint32_t t){
		
	t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

    ss = t % 60;
    t /= 60;
    mm = t % 60;
    t /= 60;
    hh = t % 24;
    uint16_t days = t / 24;
    uint8_t leap;
    for (y = 0; ; ++y) {
        leap = y % 4 == 0;
        if (days < 365 + leap)
            break;
        days -= 365 + leap;
    }
    for (m = 1; ; ++m) {
        uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
        if (leap && m == 2)
            ++daysPerMonth;
        if (days < daysPerMonth)
            break;
        days -= daysPerMonth;
    }
	dd = 0;
    d = days + 1;

}

uint32_t TSTAMP::unixtime(void) const {
  uint32_t t;
  uint16_t days = date2days(y, m, d);
  t = time2long(days, hh, mm, ss);
  t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

  return t;
}
	
	
//*************************DS1307 class*******************************//
static uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4); }
static uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10); }

uint8_t DS1307::begin(void) {
  return 1;
}



uint8_t DS1307::isrunning(void) {
  WIRE.beginTransmission(DS1307_ADDRESS);
  WIRE.write(0);
  WIRE.endTransmission();

  WIRE.requestFrom(DS1307_ADDRESS, 1);
  uint8_t ss = WIRE.read();
  return !(ss>>7);
}

void DS1307::adjust(const TSTAMP& ts) {
    WIRE.beginTransmission(DS1307_ADDRESS);
    WIRE.write(0);
    WIRE.write(bin2bcd(ts.ss));
    WIRE.write(bin2bcd(ts.mm));
    WIRE.write(bin2bcd(ts.hh));
    WIRE.write(bin2bcd(0));
    WIRE.write(bin2bcd(ts.d));
    WIRE.write(bin2bcd(ts.m));
    WIRE.write(bin2bcd(ts.y));
    WIRE.write(0);
    WIRE.endTransmission();
}

TSTAMP DS1307::now() {
  WIRE.beginTransmission(DS1307_ADDRESS);
  WIRE.write(0);	
  WIRE.endTransmission();

  WIRE.requestFrom(DS1307_ADDRESS, 7);
  uint8_t ss = bcd2bin(WIRE.read() & 0x7F);
  uint8_t mm = bcd2bin(WIRE.read());
  uint8_t hh = bcd2bin(WIRE.read());
  WIRE.read();
  uint8_t d = bcd2bin(WIRE.read());
  uint8_t m = bcd2bin(WIRE.read());
  uint8_t y = bcd2bin(WIRE.read());
  
  return TSTAMP (y, m, d, hh, mm, ss);
}



