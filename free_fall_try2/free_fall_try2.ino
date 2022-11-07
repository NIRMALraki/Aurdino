#include <Adafruit_CircuitPlayground.h>


float X, Y, Z;



//const int maxChange = 10;
//int x_init = 0;
//int y_init = 0;
//int z_init = 0;
//boolean firstRun = 1;
//int maxCalls = 1;
//int calls = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
   CircuitPlayground.clearPixels();
   X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
   Z = CircuitPlayground.motionZ();

  float at=sqrt(X*X+Y*Y+Z*Z);
  Serial.print(X);
  Serial.print("\t");
  Serial.print(Y);
  Serial.print("\t");
  Serial.print(Z);
  Serial.print("\n\r");
  Serial.println("at =");
  Serial.println(at);

 if(at<1)
 {
  Serial.println("fall");
  CircuitPlayground.setPixelColor(0, 255,   0,   0);
  CircuitPlayground.setPixelColor(1, 128, 128,   0);
  CircuitPlayground.setPixelColor(2,   0, 255,   0);
  CircuitPlayground.setPixelColor(3,   0, 128, 128);
  CircuitPlayground.setPixelColor(4,   0,   0, 255);
  
  CircuitPlayground.setPixelColor(5, 0xFF0000);
  CircuitPlayground.setPixelColor(6, 0x808000);
  CircuitPlayground.setPixelColor(7, 0x00FF00);
  CircuitPlayground.setPixelColor(8, 0x008080);
  CircuitPlayground.setPixelColor(9, 0x0000FF);
  delay(5000);
 }
// else
// {
//    CircuitPlayground.strip.clear();
//
// }

//  if(!firstRun)
//  {
//     if ((abs(X-x_init)>=maxChange)||(abs(Y-y_init)>=maxChange)||(abs(Z-z_init)>=maxChange)) 
//     {
//         if (calls < maxCalls) {
//        Serial.println("free fall");
//        calls++;
//        } 
//      } 
//        
//        delay(2500);
//     }
//  
//  else
//  {
//    x_init = X;
//    y_init = Y;
//    z_init = Z;
//    firstRun = 0;
//  }
}
