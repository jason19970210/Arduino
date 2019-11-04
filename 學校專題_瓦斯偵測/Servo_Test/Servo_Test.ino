#include <Servo.h>             //Servo library
 
Servo servo_test;        //initialize a servo object for the connected servo  
                
int angle = 0;    
 
void setup() { 
  Serial.begin(9600);
  servo_test.attach(33); // attach the signal pin of servo to pin9 of arduino
  servo_test.writeMicroseconds (1405); //rotate to right
  delay(1000);
  servo_test.writeMicroseconds (1500);
  delay(1000);
  servo_test.writeMicroseconds (1600);
  delay(1000);
  servo_test.writeMicroseconds (1500);
  
} 
  
void loop() { 

  
  
//  servo_test.writeMicroseconds (2240); // rotate to left 
//  delay (1005);

//    servo_test.write(45);
//    delay(250);
//    servo_test.write(90);
//    delay(2000);
//
//    servo_test.write(135);
//    delay(300);
//    servo_test.write(92);
//    delay(2000);
//  for(angle = 0; angle <= 90; angle += 1){    // command to move from 0 degrees to 180 degrees                           
//    servo_test.write(angle);                 //command to rotate the servo to the specified angle
//    Serial.println(angle);
//    delay(15);                       
//  } 
 
  
//  for(angle = 180; angle>=1; angle-=5)     // command to move from 180 degrees to 0 degrees 
//  {                                
//    servo_test.write(angle);              //command to rotate the servo to the specified angle
//    delay(5);                       
//  } 
//
//    delay(1000);
}
