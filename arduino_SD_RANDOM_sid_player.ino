#include <string.h>
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

String playlist[20];
char num_files=0;


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
void read_directory(File dir, int numTabs) {
  while (1) {

    // Get next file entry
    File entry =  dir.openNextFile();

    // End of files
    if (! entry) {
      break;
    } else {

   
      // Is it a directory?
      if (!entry.isDirectory() && entry.size()>0) {

        // Filename
        String filename = String(entry.name());

        if(filename.indexOf(".DMP") > 0 || filename.indexOf(".dmp") > 0) {

        // Print the filename
        Serial.print(filename + " ");
        Serial.println(entry.size());
        playlist[num_files] = filename;
        num_files++;
        }

      }


    }

    // Done with this entry
    entry.close();

  }
}

// Open the file for reading:
int load_sid(char sid_file[14]) {

  // Load the file
  myFile = SD.open(sid_file);

  if (myFile) {
    Serial.println("OPENED file:" + String(sid_file));
    return 0;
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file " + String(sid_file));
    return 1;
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
  Serial.println("\n\nReading root directory ...\n\n");

  // Open root directory and display the results
  root = SD.open("/");
  read_directory(root, 0);
  char chosen_file[13];
  randomSeed(analogRead(A0));
  playlist[random(num_files-1)].toCharArray(chosen_file, 13);
  Serial.println("Directory read. Loading tune " + String(chosen_file));

  // open random sid dump
  int res=load_sid(chosen_file);

} 

// Main loop
void loop() {


    // read from the file until there's nothing else in it:
    if (myFile.available()) {
      myFile.read((uint8_t *)sidData, 25);
      for(uint8_t sidRegister=0;sidRegister<=24;sidRegister++){
        mySid.set_register(sidRegister,sidData[sidRegister]);
      }
      sleep(19);
    } else {
      // close the file:
      myFile.close();
    }

}

