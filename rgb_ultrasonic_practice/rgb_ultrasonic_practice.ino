#define echoPin 2 
#define trigPin 3

int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;

long duration;
int distance; 
void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  //RGB_color(87, 255, 255); // White


  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  delay(500);
  digitalWrite(trigPin, LOW);

   duration = pulseIn(echoPin, HIGH);
   distance = duration * 0.034 / 2;
   Serial.print("Distance: ");
   Serial.print(distance);
   Serial.print(" cm");
  if(distance < 10)
  {
    RGB_color(255, 0, 0);
  }
  else if(distance <20)
  {
    RGB_color(255, 255, 0); // Yellow
  }
  else
  {
    RGB_color(0, 255, 0); // Green
  }








//  
//  RGB_color(255, 0, 0); // Red
//  delay(50);
//  RGB_color(0, 255, 0); // Green
//  delay(50);
//  RGB_color(0, 0, 255); // Blue
//  delay(50);
//  RGB_color(255, 255, 125); // Raspberry
//  delay(50);
//  RGB_color(0, 255, 255); // Cyan
//  delay(50);
//  RGB_color(255, 0, 255); // Magenta
//  delay(50);
//  RGB_color(255, 255, 0); // Yellow
//  delay(50);
//  RGB_color(255, 255, 255); // White
//  delay(50);
  
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
