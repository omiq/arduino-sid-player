// SID Commander: pushes data to SID i2c receiver
// Uno: TWI: A4 (SDA) pin and A5 (SCL) pin

#include <stdlib.h>
#include <Wire.h>

#define VOICE1	0
#define VOICE2	7
#define VOICE3	14

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

// Enhance SID 
class RSID {
  public:
    void initI2CAsMaster(int device);
    uint8_t set_register(uint8_t regnum, uint8_t value);
    void playTune();
    void loadPiano(uint8_t voice);
    void configVoice(uint8_t voice, uint8_t waveform, uint16_t pulsewidth /*12bit*/, uint8_t attackDecay, uint8_t sustainRelease, uint8_t releasePoint);
    uint16_t  midi2Sid(int midin);
    void play(uint8_t voice, uint16_t freq);
  protected:
    int device;
};
RSID i2c_SID;

// join i2c bus 
void RSID::initI2CAsMaster(int deviceI){
  Wire.begin();
  device=deviceI;
}

// set a sid register over i2c
uint8_t RSID::set_register(uint8_t regnum, uint8_t value){
  Wire.beginTransmission(device);
  Wire.write(regnum);
  Wire.write(value);
  Wire.endTransmission();
}

// Convert midi to sid
uint16_t  RSID::midi2Sid(int midin){
  switch(midin){
  case 60:return 0x122A;  // C4$	277.18	4650	122A 
  case 61:return 0x133F;  
  case 62:return 0x1464;  
  case 63:return 0x159A;
  case 64:return 0x16E3; 
  case 65:return 0x183F;  // FA
  case 66:return 0x1981;
  case 67:return 0x1B38;
  case 68:return 0x1CD6;
  case 69:return 0x1E80;
  case 70:return 0x205E;
  case 71:return 0x224B; // 
  case 72:return 0x2455; // C5$	554.37	9301	2455
  default:return 0x0;
    }
}

void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
}
 
void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  delay(325);
 
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);
}

void beep(int note, int duration)
{

  i2c_SID.play(VOICE1,note);
  delay(duration);
  Serial.println(note);
  i2c_SID.play(VOICE1,0);
 
}

// Play sound
void RSID::play(uint8_t voice, uint16_t freq){
  byte low = freq & 0x00FF;
  byte high= freq >>8;
  set_register(voice+0,low);
  set_register(voice+1,high);
}




void setup()
{
  Serial.begin(9600); 
  i2c_SID.initI2CAsMaster(23);
  Serial.println("Sid commander ready");

  // MAX VOLUME
  i2c_SID.set_register(24,15); 
}

void loop()
{

  firstSection();
  secondSection();
  delay(2000);
}


