  #include <Adafruit_CircuitPlayground.h>

#define COLOR         0x0f0f0f    // change this to your favorite color
#define FLASH_RATE    2000        // lower is faster
int value;

///////////////////////////////////////////////////////////////////////////////
void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  
  // Make it bright!
  CircuitPlayground.setBrightness(50);
}


///////////////////////////////////////////////////////////////////////////////
void loop() {
  // Turn on all the pixels to COLOR
//  for (int pixel=0; pixel<10; pixel++) {
//    CircuitPlayground.setPixelColor(pixel, COLOR);    
//  }
  value = CircuitPlayground.lightSensor();
  Serial.println(value);
  if(value<30)
  {
    
  CircuitPlayground.setPixelColor(0, 0xff0000);
  CircuitPlayground.setPixelColor(1, 0xff0000);
  CircuitPlayground.clearPixels();
  
  
  }
   else if(value>40)
  {
    CircuitPlayground.setPixelColor(4, 0x00ff1e);
  CircuitPlayground.setPixelColor(8, 0x00ff1e);
    CircuitPlayground.clearPixels();

 
  }
  else
  {
     CircuitPlayground.clearPixels();
  
  }
  

  
  
  
  // Leave them on for a little bit  
  //delay(FLASH_RATE);

  // Turn off all the NeoPixels
 // CircuitPlayground.clearPixels();

  // Leave them off for a little bit
  
}
