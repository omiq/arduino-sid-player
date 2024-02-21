/* Connect PIN 9, 10 + ground */
#include <avr/pgmspace.h>  // Lib to store data in the flash rom
#include <SID.h>           // sid-arduino-lib: Brian Tucker 1-5-2015
SID mySid;                 // https://code.google.com/p/sid-arduino-lib/ 


// Our SID music file converted into a C header file containing an array
#include "commando_sid.h"  // SID register data file in flash memory

#define LED 13

// Non-blocking sleep function
void sleep(int sleep_time)
{
  long start_time = millis();

  while(millis() < start_time + sleep_time)
  {
    // do nothing
  }
}

// Once on boot
void setup()  { 

  // Initialize the SID library
  mySid.begin();
} 

// Main loop
void loop() {

  // Get the next SID register data and set in the SID class
  for(uint16_t sidPointer=0;sidPointer<=sidLength;sidPointer++){
    for(uint8_t sidRegister=0;sidRegister<=24;sidRegister++){
      mySid.set_register(sidRegister, (pgm_read_byte(&sidData[(sidPointer+sidRegister)])));
    };

    // Wait before moving the pointer forward
    sleep(19);
    sidPointer=sidPointer+24;
  };
}

