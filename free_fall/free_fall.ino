//Circuit Playground Freefall Deck
//created by John Park for Adafruit Industries
//a sealed deck of cards is tossed in the air or dropped, at which point it reveals a Morse code message
//Freefall detection by Phil Burgess
//Morse table by Usman Muzaffar
////////////////////////////////////////
#include "Adafruit_CircuitPlayground.h"

volatile boolean interruptHappened = false;
//*******************************************************//
//Morse code playback variables
//Adjust PITCH to your liking and DOT for speed faster/slower 
const int PITCH = 600; // Morse code audio is sent at 600-800 Hz. 680 is quite nice
const int DOT = 200;   //time duration in millis, change this to adjust transmission speed

const int DASH = 3 * DOT; //Morse standard dash is 3x longer than dot
const int GAP = DOT; //Morse inter-element gap within a character is same length as dot
const int INTER_LETTER = 3 * DOT; //Morse short gap between letters is 3x dot length
const int INTER_WORD = 7 * DOT; //Morse medium gap between words is 7x dot length
//*******************************************************//
void setup() {

  CircuitPlayground.begin();
  CircuitPlayground.strip.clear();
  //CircuitPlayground.strip.show();
  Serial.begin(9600);

  // Bypass library and brute-force LIS3DH registers for freefall detect.
  // From ST App Note AN3308 w/changes to threshold & duration.
  writeReg8(LIS3DH_REG_CTRL1  , 0xA7); // Sensor on, enable X,Y,Z, 100 Hz
    delay(2000);
  Serial.println("wrote");

  writeReg8(LIS3DH_REG_CTRL2  , 0x00); // Disable high-pass filter
  writeReg8(LIS3DH_REG_CTRL3  , 0x40); // Enable I1_INT1 interrupt gen
  writeReg8(LIS3DH_REG_CTRL4  , 0x00); // 2G
  writeReg8(LIS3DH_REG_CTRL5  , 0x00); // Interrupt not latched
  writeReg8(LIS3DH_REG_INT1THS, 0x0A); // ~160 mG threshold
  writeReg8(LIS3DH_REG_INT1DUR, 0xFF); // Duration
  writeReg8(LIS3DH_REG_INT1CFG, 0x95); // Configure free-fall recognition

  //pinMode(27, INPUT_PULLUP); // LIS3DH INT1 is connected to D7
  attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), interruptHandler, FALLING);
}

void writeReg8(uint8_t reg, uint8_t value) {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CPLAY_LIS3DH_CS, LOW);
  SPI.transfer(reg & 0x7F);
  SPI.transfer(value);
  digitalWrite(CPLAY_LIS3DH_CS, HIGH);
  Serial.println("done");
  SPI.endTransaction();
}

void interruptHandler() {
  interruptHappened = true;
}

void loop() {
  if (interruptHappened) { //Accelerometer has detected free fall, do something here
    //*******************************************************//
    //Place your message here.
    //Each letter or number on one line.
    //Spaces between words are denoted with a slash / symbol.
    //Only use A-Z 0-9 
    //Other characters will cause trouble!
    Serial.println("free_fall");
  }
  else
  {
    CircuitPlayground.redLED(HIGH);
    CircuitPlayground.setPixelColor(0, 255,   0,   0);
    Serial.println("no");
  delay(50);
  }
    
//    playMorseLetter('/');//good to have a slight delay at the beginning
//    
//    playMorseLetter('O');
//    playMorseLetter('N');
//    playMorseLetter('/');
//    playMorseLetter('P'); 
//    playMorseLetter('A');
//    playMorseLetter('G'); 
//    playMorseLetter('E');
//    playMorseLetter('/'); 
//    playMorseLetter('X');
//
//    //*******************************************************//
//    interruptHappened = false;
//  }
//}
//
//void playMorseLetter(char letter) {
//  // Morse table by Usman Muzaffar
//  // Adapted from: http://stackoverflow.com/a/28058216
//  // Define two tables of strings one for letters and one for numbers,
//  // that return the Morse encoding. By using two separate tables, we
//  // can just offset the ASCII value of either a number or letter as
//  // the index to look up the Morse encoding.
//  static const char *ALPHA_TABLE[] = {
//    ".-",   //A
//    "-...", //B
//    "-.-.", //C
//    "-..",  //D
//    ".",    //E
//    "..-.", //F
//    "--.",  //G
//    "....", //H
//    "..",   //I
//    ".---", //J
//    "-.-",  //K
//    ".-..", //L
//    "--",   //M
//    "-.",   //N
//    "---",  //O
//    ".--.", //P
//    "--.-", //Q
//    ".-.",  //R
//    "...",  //S
//    "-",    //T
//    "..-",  //U
//    "...-", //V
//    ".--",  //W
//    "-..-", //X
//    "-.--", //Y
//    "--..", //Z
//  };
//  static const char *NUM_TABLE[] = {
//    "-----", //0
//    ".----", //1
//    "..---", //2
//    "...--", //3
//    "....-", //4
//    ".....", //5
//    "-....", //6
//    "--...", //7
//    "---..", //8
//    "----.", //9
//  };
//    if(letter == '/'){// use "/" as space between words
//        delay(INTER_WORD);
//        return;
//    }
//
//    // Look up the morseCode string for this letter
//    // by finding the right table.
//
//    char* morseCode;
//    if (isalpha(letter)) {
//        morseCode = ALPHA_TABLE[letter - 'A'];
//    } else {
//        morseCode = NUM_TABLE[letter - '0'];
//    }
//
//    for (int i = 0; i < strlen(morseCode); i++){
//        int duration = morseCode[i] == '-' ? DASH : DOT;
//        CircuitPlayground.playTone(PITCH, duration);
//        delay(GAP);
//    }
//    delay(INTER_LETTER);
}
