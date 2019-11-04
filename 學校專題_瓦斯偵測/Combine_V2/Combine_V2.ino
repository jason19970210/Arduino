// Usage : high(<int>, <int>)
// the first int will be the int number you want to display on the 7-segment display
// the second int is the `delay` time
// all pins goes to the digital pin
/*
      13  12  11  10  9   8
      |   |   |   |   |   |
 ==============================
||    ---     ---     ---     ||
||   |   |   |   |   |   |    ||
||    ---     ---     ---     ||
||   |   |   |   |   |   |    ||
||    ---  .  ---  .  ---  .  ||
 ==============================
      |   |   |   |   |   |
      2   3   4   5   6   7
*/

// Motor Pin
// Black : GND
// RED : 5V+
// WHITE : Digital Pin 33

// MQ-2 Sensor Pin
// AD : null
// DO : pin A8
// GND : GND
// VCC : 3.3V+ or 5V+

#include <Servo.h> 
//#include <WiFi.h>
Servo servo;  

int pos = 0;                                   // 設定 Servo 位置的變數
int airValue = A8;                            //線接位置A8
int t = 9; //second
const byte buttonPin = 31;
boolean state = LOW;
int debounceDelay  = 200;
unsigned long lastMillis; // record last milis
int sensorValue = 0; // MQ-2


#define d1 13
#define d2 10
#define d3 9

const int seg[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int dig[3] = {d1, d2, d3};
const int list[10] = {7, 2, 5, 5, 4, 5, 6, 3, 7, 6}; //index of storage dicts

void setup() {
  Serial.begin(9600);
  pinMode(airValue,OUTPUT); // 這裡設定所要發出警告的PIN腳模式
  servo.attach(33); // 將 servo 物件連接到 pin 33

  for(int i=2; i<14; i++){
    pinMode(i, OUTPUT);
  }
  
  pinMode(buttonPin, INPUT_PULLUP); // activate the internal pull-up resistor

  for (pos = 0; pos <= 90; pos++){           //關閉瓦斯旋鈕    
    servo.write(pos);                        // 告訴 servo 走到 'pos' 的位置
    delay(10);
    Serial.println("OFF");
  }

}

void loop() {
  
  
  digitalWrite(dig[0],HIGH); // make the first digit not display
  digitalWrite(dig[2],HIGH); // make the second digit not display
  
  // if you want to display `10`, you should make the second digit display `1`, then show `0` on the third digit

  /*
  // Count Down
  if(t != 0){
    high(t,1000);
    low(t, 0);
    t--;
  } else { // t ==0
    Serial.println("Times out");
    high(t,1000);
    low(t, 0);
  }*/


  boolean state = digitalRead(buttonPin);
  
  if(state == LOW){
    if(debounced()){
      state = !state;
      low(0,100);
      Serial.println("Pressed");
      Serial.println("Stove Turn On");
      // rotate motor to simulate turning on the stove
      turnOnStoven();
      delay(500); // waiting motor moving
      
      for(int i=t; i>=0; i--){ //for loop begin
        if(i != 0){
          high(i,1000);
          low(i, 0);
          getSensorValue();
          if(sensorValue < 30){
            Serial.println("Alert");
            // buzzer
            // turn off the stoven
            turnOffStoven();
            break; // jump out of the for loop
          } else {
            Serial.println("Safe");           
          }
        } else { // i ==0
          Serial.println("Times out");
          turnOffStoven();
          /////////////////////
          for(int i=0; i<5; i++){
            high(0,500);
            low(0, 500);
          }
          high(0,1000);
          
        }
      } // end of for loop
      
      Serial.println("BREAK");
      //do other thing after this
    } // if(debounced())
  } // if(state == LOW)
} // end of loop



int getSensorValue(){
  sensorValue = analogRead(airValue);      //讀取值
  Serial.println(sensorValue);
  return sensorValue;
}


void turnOffStoven(){
  for (pos = 0; pos <= 90; pos++){           //關閉瓦斯旋鈕    
    servo.write(pos);                        // 告訴 servo 走到 'pos' 的位置
    delay(10);
    Serial.println("OFF");
  }
}
void turnOnStoven(){
  for (pos = 180; pos >= 90; pos-=1){           //開啟瓦斯旋鈕     
    servo.write(pos);                        // 告訴 servo 走到 'pos' 的位置
    delay(10);                                 // 等待 10ms 讓 servo 走到指定位置
    Serial.println("ON");
  }
}


// button detection
boolean debounced(){
  unsigned long currentMillis = millis();
  if((currentMillis - lastMillis) > debounceDelay){
    lastMillis = currentMillis; // update lastMillis with currentMillis
    return true; // debounced
  } else {
    return false; // not debounced
  }
}


byte * int0() {
  static byte s[6];
  s[0] = 2;
  s[1] = 3;
  s[2] = 5;
  s[3] = 8;
  s[4] = 11;
  s[5] = 12;
  return s;
}
byte * int1() {
  static byte s[2];
  s[0] = 5;
  s[1] = 8;
  return s;
}
byte * int2() {
  static byte s[5];
  s[0] = 2;
  s[1] = 3;
  s[2] = 6;
  s[3] = 8;
  s[4] = 12;
  return s;
}
byte * int3() {
  static byte s[5];
  s[0] = 3;
  s[1] = 5;
  s[2] = 6;
  s[3] = 8;
  s[4] = 12;
  return s;
}
byte * int4() {
  static byte s[4];
  s[0] = 5;
  s[1] = 6;
  s[2] = 8;
  s[3] = 11;
  return s;
}
byte * int5() {
  static byte s[5];
  s[0] = 3;
  s[1] = 5;
  s[2] = 6;
  s[3] = 11;
  s[4] = 12;
  return s;
}
byte * int6() {
  static byte s[6];
  s[0] = 2;
  s[1] = 3;
  s[2] = 5;
  s[3] = 6;
  s[4] = 11;
  s[5] = 12;
  return s;
}
byte * int7() {
  static byte s[3];
  s[0] = 5;
  s[1] = 8;
  s[2] = 12;
  return s;
}
byte * int8() {
  static byte s[7];
  s[0] = 2;
  s[1] = 3;
  s[2] = 5;
  s[3] = 6;
  s[4] = 8;
  s[5] = 11;
  s[6] = 12;
  return s;
}
byte * int9() {
  static byte s[6];
  s[0] = 3;
  s[1] = 5;
  s[2] = 6;
  s[3] = 8;
  s[4] = 11;
  s[5] = 12;
  return s;
}


int high(int num, int d){

  if(num == 0){
    byte *pt = int0();
      for (byte i = 0; i < list[num]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 1){
    byte *pt = int1();
      for (byte i = 0; i < list[1]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 2){
    byte *pt = int2();
      for (byte i = 0; i < list[2]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 3){
    byte *pt = int3();
      for (byte i = 0; i < list[3]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 4){
    byte *pt = int4();
      for (byte i = 0; i < list[4]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 5){
    byte *pt = int5();
      for (byte i = 0; i < list[5]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 6){
      byte *pt = int6();
      for (byte i = 0; i < list[6]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 7){
    byte *pt = int7();
      for (byte i = 0; i < list[7]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 8){
    byte *pt = int8();
      for (byte i = 0; i < list[8]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 9){
    byte *pt = int9();
      for (byte i = 0; i < list[9]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else {
      //none
  }

} // end of high()


int low(int num, int d){

  if(num == 0){
    byte *pt = int0();
      for (byte i = 0; i < list[0]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 1){
    byte *pt = int1();
      for (byte i = 0; i < list[1]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 2){
    byte *pt = int2();
      for (byte i = 0; i < list[2]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 3){
    byte *pt = int3();
      for (byte i = 0; i < list[3]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 4){
    byte *pt = int4();
      for (byte i = 0; i < list[4]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 5){
    byte *pt = int5();
      for (byte i = 0; i < list[5]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 6){
      byte *pt = int6();
      for (byte i = 0; i < list[6]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 7){
    byte *pt = int7();
      for (byte i = 0; i < list[7]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 8){
    byte *pt = int8();
      for (byte i = 0; i < list[8]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 9){
    byte *pt = int9();
      for (byte i = 0; i < list[9]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else {
      //none
  }

}
