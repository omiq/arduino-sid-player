// SID Receiver
// Receives I2C/TWI sound register data 


#include <Wire.h>
#include <inttypes.h>
#include <SID.h>
#include <String.h>
SID mySid;
bool ledOn=false;

void setup()
{
  Wire.begin(23);                // join i2c bus with address #23
  Wire.onReceive(receiveEvent); // register event  
  mySid.begin();
  pinMode(LED_BUILTIN, OUTPUT); // TRUE ON ONBULK SEND
  mySid.loadPiano(VOICE1_Right);
  mySid.loadPiano(VOICE2_Left);  
}

void loop()
{  
  if(ledOn) {
      digitalWrite(LED_BUILTIN, HIGH); 
  }else{
      digitalWrite(LED_BUILTIN, LOW); 
  }   
}

// I2C is a blocking interface.
void receiveEvent(int howMany)
{  
  if( Wire.available() >2 ){
    ledOn=true;
  }else{
    ledOn=false;
  }
  while ( Wire.available()) // loop through all 
  {
    uint8_t reg = Wire.read(); 
    uint8_t val = Wire.read();    
    mySid.set_register(reg,val);        
  }
}
