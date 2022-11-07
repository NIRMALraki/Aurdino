///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Tap Detect
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)

#include <Adafruit_CircuitPlayground.h>

#define TAP_THRESHOLD       10          // Tap detect threshold

bool tapDetected;

///////////////////////////////////////////////////////////////////////////////
void tapCallback() {
  tapDetected = true;
}

///////////////////////////////////////////////////////////////////////////////
void setup(void) {
  Serial.begin(9600);

  CircuitPlayground.begin();
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
  CircuitPlayground.setAccelTap(2, TAP_THRESHOLD);
  
  attachInterrupt(digitalPinToInterrupt(7), tapCallback, FALLING);

  tapDetected = false;
}

///////////////////////////////////////////////////////////////////////////////
void loop() {
  if (tapDetected) {
    Serial.println("TAP!");
    tapDetected = false;


    CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  CircuitPlayground.setAccelTap(2, TAP_THRESHOLD);
  
  attachInterrupt(digitalPinToInterrupt(7), tapCallback, FALLING);

  tapDetected = false;
  }
}
