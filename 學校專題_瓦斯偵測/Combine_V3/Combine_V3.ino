// TODO : Break loop while count down


// \/ 7Segment Display connect with ESP32
/*
      23  22  21  19  18  5
      |   |   |   |   |   |
 ==============================
||    ---     ---     ---     ||
||   |   |   |   |   |   |    ||
||    ---     ---     ---     ||
||   |   |   |   |   |   |    ||
||    ---  .  ---  .  ---  .  ||
 ==============================
      |   |   |   |   |   |
     17  16   4   0   2   15
*/
// GWS Servo S35 STD
// Black - GND
// Red - +3.3V
// White - 26

// Buzzer
// Positive - pin33
// Nagitive - GND

// MQ-5 Sensor
// AD - SVP (A0)
// D0 - null
// GND - GND
// VCC - +5V


#include <ESP32_Servo.h> 
#include "esp32-hal-ledc.h" 
#include <MQ2.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial
#define d1 18
#define d2 19
#define d3 23

char auth[] = "xxxxxxxxxxxxxxxxxxxxxxxx";
char ssid[] = "xxxxxxxx";  // Wifi SSID Here
char pass[] = "xxxxxxxx";  // Wifi Password Here
int pos = 0;
int MQpin = A0;
const int dig[3] = {d1, d2, d3};
const int list[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}; //index of storage dicts
int t = 9; //second
int stovenStatus = 0;
int debounceDelay  = 200;
unsigned long lastMillis; // record last milis
int buzzerPin = 33;
int freq = 2000;
int resolution = 8;
long previousTime = 0;
long interval = 1000;

Servo servo;
MQ2 mq5(MQpin);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  //servo.attach(26);
  mq2.begin();
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);
  //pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);  
  ledcSetup(1, freq, resolution);
  ledcAttachPin(buzzerPin, 1);
  ledcSetup(2, 50, 16);
  ledcAttachPin(26, 2);
  // Recommanded PWM GPIO pins on ESP32 include 2,4,12-19,21-23,25-27,33,34
}


// Functions:
// turnOnStoven()
// turnOffStoven()
// high(int, delay)
// low(int, delay)
// shortBeep(delay,times)
// getGasValue()
void loop() {

  digitalWrite(dig[0],HIGH); // make the first digit not display
  digitalWrite(dig[2],HIGH); // make the second digit not display
  
  Blynk.run();

  
  //boolean state = digitalRead(buttonPin);
  //if(state == LOW){
  //  if(debounced()){
  //    state = !state;
  //    low(0,100);
  //    Serial.println("Pressed");
  //  }
  //}
}

BLYNK_WRITE(V2){
  int buttonStatus = param.asInt();
  Serial.print("Button send : ");
  Serial.println(buttonStatus);
  if(buttonStatus == 0){
    if(stovenStatus == 1){ //ERROR OPERATING
      turnOffStoven();
      stovenStatus = 0;
    }
  } else { // the situation of buttonStatus == 1
    if(stovenStatus == 0){
      turnOnStoven();
      stovenStatus = 1;
      // Count Down
      for(int i=t; i>=0; i--){
        float value = getGasValue();
        Blynk.virtualWrite(V1, value);
        if(value > 80){
          Serial.println("Alert and turning off the stoven");
          turnOffStoven();
          stovenStatus = 0;
          Blynk.virtualWrite(V2, LOW);
          Blynk.virtualWrite(V0, "https://maker.ifttt.com/trigger/GES_Notification/with/key/d0T3bbLTNeQTgEawRi79GBl7qIumaetxdNI3xvQ4cn2?value1=瓦斯外漏_瓦斯爐開啟狀態&value2=瓦斯爐已關閉！");
          shortBeep(200, 10);
          return;
        } else {
          high(i, 1000);
          low(i, 0);
        }
      }
      turnOffStoven();
      stovenStatus = 0;
      Blynk.virtualWrite(V2, LOW);
      Blynk.virtualWrite(V0, "https://maker.ifttt.com/trigger/GES_Notification/with/key/d0T3bbLTNeQTgEawRi79GBl7qIumaetxdNI3xvQ4cn2?value1=瓦斯爐已達設定時間且已關閉");
      shortBeep(300, 3);
    }
  }
}
BLYNK_READ(V2){
  if(stovenStatus == 0){
    Blynk.virtualWrite(V2, LOW);
  } else {
    Blynk.virtualWrite(V2, HIGH);
  }
}
BLYNK_READ(V1){
  float value = getGasValue();
  Blynk.virtualWrite(V1, value);
  if(value > 80){
    Serial.println("ALERT!!");
    if(stovenStatus == 0){
      Serial.println("Alert but stoven is off!!");
      shortBeep(300, 3);
      Blynk.virtualWrite(V0, "https://maker.ifttt.com/trigger/GES_Notification/with/key/d0T3bbLTNeQTgEawRi79GBl7qIumaetxdNI3xvQ4cn2?value1=瓦斯外漏_瓦斯爐關閉狀態");
      // Send Notification -> Gas Overflow
    } else { // stoven is on need to be turn off
      Serial.println("Alert and turning off the stoven");
      turnOffStoven();
      stovenStatus = 0;
      Blynk.virtualWrite(V2, LOW);
      Blynk.virtualWrite(V0, "https://maker.ifttt.com/trigger/GES_Notification/with/key/d0T3bbLTNeQTgEawRi79GBl7qIumaetxdNI3xvQ4cn2?value1=瓦斯外漏_瓦斯爐開啟狀態&value2=瓦斯爐已關閉！");
      shortBeep(200, 10);
      //Serial.println("Change Button Status on the App");
    }
  }
}


boolean debounced(){
  unsigned long currentMillis = millis();
  if((currentMillis - lastMillis) > debounceDelay){
    lastMillis = currentMillis; // update lastMillis with currentMillis
    return true; // debounced
  } else {
    return false; // not debounced
  }
}

void turnOffStoven(){
  for(int i=0; i<=5000; i+=145){
    //Serial.println(i);
    ledcWrite(2, i);
    delay(20);
  }
  ledcWrite(2,5000);
  /*
  for (double posDegrees = 0.0; posDegrees <= 90.0; posDegrees+=2.5) {
    servo.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
  */
}

void turnOnStoven(){
  for(int i=9950; i>=5000; i-=145){
    //Serial.println(i);
    ledcWrite(2, i);
    delay(20);
  }
  /*
  for (double posDegrees = 180.0; posDegrees >= 90.0; posDegrees-=2.4) {
    servo.write(posDegrees);
    Serial.println(posDegrees);
    delay(20);
  }
  */
}

float getGasValue(){
  float lpg = mq5.readLPG();
  if(100*lpg/2100000000 > 100){
    return 100;
  } else {
    return 100*lpg/2100000000;
  }
}

void shortBeep(int d, int times) {
  for(int i = 0; i < times; i++){
    float value = getGasValue();
    Blynk.virtualWrite(V1, value);
    ledcWriteTone(1, freq);
    delay(d);
    high(0,500);
    ledcWriteTone(1, 0);
    delay(d);
    low(0, 500);
  }
}

byte * int0(){
  static byte s[6];
  s[0] = 21;
  s[1] = 17;
  s[2] = 16;
  s[3] = 0;
  s[4] = 5;
  s[5] = 22;
  return s;
}
byte * int1() {
  static byte s[2];
  s[0] = 5;
  s[1] = 0;
  return s;
}
byte * int2() {
  static byte s[5];
  s[0] = 22;
  s[1] = 5;
  s[2] = 2;
  s[3] = 17;
  s[4] = 16;
  return s;
}
byte * int3() {
  static byte s[5];
  s[0] = 22;
  s[1] = 5;
  s[2] = 2;
  s[3] = 0;
  s[4] = 16;
  return s;
}
byte * int4() {
  static byte s[4];
  s[0] = 21;
  s[1] = 2;
  s[2] = 5;
  s[3] = 0;
  return s;
}
byte * int5() {
  static byte s[5];
  s[0] = 22;
  s[1] = 21;
  s[2] = 2;
  s[3] = 0;
  s[4] = 16;
  return s;
}
byte * int6() {
  static byte s[6];
  s[0] = 22;
  s[1] = 21;
  s[2] = 2;
  s[3] = 0;
  s[4] = 16;
  s[5] = 17;
  return s;
}
byte * int7() {
  static byte s[3];
  s[0] = 22;
  s[1] = 5;
  s[2] = 0;
  return s;
}
byte * int8() {
  static byte s[7];
  s[0] = 22;
  s[1] = 21;
  s[2] = 5;
  s[3] = 2;
  s[4] = 17;
  s[5] = 16;
  s[6] = 0;
  return s;
}
byte * int9() {
  static byte s[6];
  s[0] = 22;
  s[1] = 21;
  s[2] = 5;
  s[3] = 2;
  s[4] = 0;
  s[5] = 16;
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

} // end of low()
