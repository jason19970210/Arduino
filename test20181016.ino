#include <Servo.h>

Servo servo1; // create servo as an object, max servos = 12
Servo servo2;

int pos1 = 0;
int pos2 = 0;

void setup() {

  // Initiate Serial Communication as 9600 baud
  Serial.begin(9600);

  // declare servo pin
  servo1.attach(12);
  servo2.attach(13);
}

void loop() {
    
  for (pos1 = 0; pos1 <= 180; pos1 += 1){
    servo1.write(pos1);
    delay(100);
    Serial.println(pos1);
  }
  
  
  
  
//  digitalWrite(ledPin,HIGH);
//  Serial.println("HIGH");
//  delay(100);
//  digitalWrite(ledPin,LOW);
//  Serial.println("LOW");
//  delay(100);

}
