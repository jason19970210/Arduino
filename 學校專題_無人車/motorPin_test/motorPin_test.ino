

int motorPin = 3;
//int speed = 225;
//REF:https://learn.adafruit.com/adafruit-arduino-lesson-13-dc-motors/breadboard-layout
void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed from 0 to 255");

}

void loop() {
//  if (Serial.available()){
//    int speed = Serial.parseInt();
//    if (speed >= 0 && speed <= 255){
//      Serial.println(speed);
//      analogWrite(motorPin,speed);
//      }
//    }
analogWrite(motorPin,speed);

}
