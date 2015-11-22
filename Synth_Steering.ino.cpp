#include <DigitalPin.h>

const int xPin = A0;
const int yPin = A1;
const int zPin = A2;
const int speakerPin = 9;    // connect speaker to pin 9
const int pitchPin = 0;
const int buttonPin = 1; 
DigitalPin right(5);
DigitalPin left(4);
DigitalPin fo(7);
DigitalPin ba(6);

//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 265;
int maxVal = 402;
int buttonState = 0;
//to hold the caculated values
double x;
double y;
double z;

void setup(){
   pinMode(buttonPin, INPUT); 
  Serial.begin(9600); 
}


void loop(){


  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);
  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);
  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  x -= 180;
  x = abs(x);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  y -= 180;
  y = abs(y);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
  z -= 180;
  z = abs(z);

  //Output the caculations
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" | y: ");
  Serial.print(y);
  Serial.print(" | z: ");
  Serial.println(z);
  
 left.on();
 right.on();
 fo.on();
 ba.on();
 
  //Output right or left
  if (z >= 150) {
    Serial.println("Right");
     left.off();
     right.on();
     
  }
    else if (z <= 30) {
    Serial.println("Left");
     right.off();
     left.on();
      
  }
  else {
    Serial.println("Straight");
     left.on();
     right.on();
     
  }
  //Output foward or back if button pressed
   
     if (x >= 155) {
      Serial.println("Forward");
       fo.on();
       ba.off();
       
    }
      else if (x <= 25) {
      Serial.println("Backward");
       fo.off();
       ba.on();
       
    }
    else {
      Serial.println("Stationary");
         fo.on();
         ba.on();
        
    }
 
    
    int sensor0Reading = 2*z ;    // read input to set frequency
   // map the analog readings to a meaningful range
   int frequency  = map(sensor0Reading, 0, 1023, 100,1000); // 100Hz to 5kHz
   int duration = 400-2*x ;   // how long the tone lasts
   tone(speakerPin, frequency, duration); // play the tone
  delay(1000);//just here to slow down the serial output - Easier to read
}
