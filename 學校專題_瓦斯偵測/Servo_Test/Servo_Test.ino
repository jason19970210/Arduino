#include <ESP32_Servo.h>             //Servo library
 
Servo servo;        //initialize a servo object for the connected servo  
int pos = 0;

void setup() { 
  Serial.begin(115200);
  servo.attach(26); // attach the signal pin of servo to pin9 of arduino
} 
  
void loop() { 
  for(pos = 0; pos <= 180; pos+=1){
    servo.write(pos);
    delay(15);
  }
}

void turnOffStoven(){
  for (double posDegrees = 0.0; posDegrees <= 90.0; posDegrees+=2.5) {
    servo.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}

void turnOnStoven(){
  for (double posDegrees = 180.0; posDegrees >= 90.0; posDegrees-=2.4) {
    servo.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
}
