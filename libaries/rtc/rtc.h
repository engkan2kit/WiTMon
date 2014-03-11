#ifndef _RTC_H_
#define _RTC_H_


class TSTAMP{
	public:	
	
		//Constructor, w/ POSIX time as a parameter
	    //TSTAMP (uint32_t t =0);
		
		//Constructor
		TSTAMP (uint8_t year, uint8_t month, uint8_t day,
                uint8_t hour, uint8_t min, uint8_t sec);
				
		uint8_t ss;		//00-59
		uint8_t mm;		//00-59
		uint8_t hr;		//00-23
		uint8_t dd;		//01-07
		uint8_t d;		//01-31
		uint8_t m;		//01-12
		uint8_t y;		//00-99
};

class DS1307{
	public:
		static uint8_t begin(void);
		static void adjust(const TSTAMP& ts);
		uint8_t isrunning(void);
		static TSTAMP now();
};

#endif