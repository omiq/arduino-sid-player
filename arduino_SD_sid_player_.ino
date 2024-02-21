#include <SPI.h>
#include <SD.h>
/*
 SD card via SPI:
 * MOSI - pin 11
 * MISO - pin 12
 * CLK - pin 13
 * CS - pin 4 
*/
File myFile;
File root;

/* Audio out: Connect PIN 9, 10 + ground */
#include <SID.h>           // sid-arduino-lib: 
SID mySid;                 // https://github.com/cybernesto/sid-arduino-lib
char sidData[25];

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

// Print the contents of a directory
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    } else {

      // Filename
      Serial.print(entry.name());
    

      if (entry.isDirectory()) {

        // Indicate a directory
        Serial.println("/");

      } else {

        // file size
        Serial.print("\t\t\t\t");
        Serial.println(entry.size(), DEC);
     
      }
    }

    // Close the file
    entry.close();
  }
}

// Once on boot
void setup()  { 

  // Initialize the SID library
  mySid.begin();

  // Open serial and wait:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port 
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // Open root directory and display the results
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("done!");

  // 
  // Open the file for reading:
  myFile = SD.open("COMMA~76.DMP");
  if (myFile) {
    Serial.println("OPENED COMMA~76.DMP:");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening COMMA~76.DMP");
  }

} 

// Main loop
void loop() {


    // read from the file until there's nothing else in it:
    if (myFile.available()) {
      myFile.read((uint8_t *)sidData, 25);
      for(uint8_t sidRegister=0;sidRegister<=24;sidRegister++){
        mySid.set_register(sidRegister,sidData[sidRegister]);
      }
      sleep(20);
    } else {
      // close the file:
      myFile.close();
    }

}

