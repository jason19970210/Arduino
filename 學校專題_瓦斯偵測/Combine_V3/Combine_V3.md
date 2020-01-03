## 瓦斯偵測與推播系統 Gas Detection & Notification with Blynk & IFTTT
#### 學校專題


## Hardware & Software Requirements
1. [ESP32 Devkit V4 Board Layout](https://raw.githubusercontent.com/jason19970210/MarkdownPhotos/master/47.jpg)
2. Arduino IDE
3. Buzzer with 2 pins
4. MQ-2 Gas Sensor
5. GWS Servo S35 STD
6. 3 Digits 7 Segment Display

## 接腳

![](https://raw.githubusercontent.com/jason19970210/MarkdownPhotos/master/46.png)

[詳細線路圖PDF](https://github.com/jason19970210/Arduino/blob/master/學校專題_瓦斯偵測/專題_瓦斯偵測.pdf)

## Code Explaination

Libraries
```cpp
#include <ESP32_Servo.h> 
#include "esp32-hal-ledc.h" 
#include <MQ2.h>
//#include <WiFi.h>
//#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
```

Declaration
```cpp
#define BLYNK_PRINT Serial
#define d1 18
#define d2 19
#define d3 23

char auth[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; //BLYNK Auth Token
char ssid[] = "WINLab-2.4Ghz"; // 
char pass[] = "error1234";
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
MQ2 mq2(MQpin);
```

Setup
```cpp
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
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
  ledcAttachPin(26, 2); // servo data pin connect to ESP32 pin 26
  // Recommanded PWM GPIO pins on ESP32 include 2,4,12-19,21-23,25-27,33,34
}
```
`ledc` is the controller with 16 channels to generate PWM signals with different properties.

Ref : https://randomnerdtutorials.com/esp32-pwm-arduino-ide/

```cpp
ledcAttachPin(GPIO, channel)
ledcWrite(channel, dutycycle)
```


Loop
```cpp
void loop(){

    digitalWrite(dig[0],HIGH); // make the first digit not display
    digitalWrite(dig[2],HIGH); // make the second digit not display
  
    Blynk.run();
}
```

Blynk Functions
- Check Blynk website : https://blynk.io/
- Document : https://docs.blynk.cc/
- Playground & Sample Code : https://examples.blynk.cc/?board=ESP8266&shield=ESP8266%20WiFi&example=GettingStarted%2FBlynkBlink
- Community : https://community.blynk.cc/

Functions
- Turn the servo
```cpp
// turn the servo right - Off
void turnOffStoven(){
  for(int i=0; i<=5000; i+=145){
    ledcWrite(2, i);
    delay(20);
  }
  ledcWrite(2,5000);
}


// turn the servo left - On
void turnOnStoven(){
  for(int i=9950; i>=5000; i-=145){
    //Serial.println(i);
    ledcWrite(2, i);
    delay(20);
  }
}
```

- Get value from MQ-2 sensor
```cpp
float getGasValue(){
  float lpg = mq2.readLPG();
  if(100*lpg/2100000000 > 100){
    return 100;
  } else {
    return 100*lpg/2100000000;
  }
}
```

- Control the buzzer with flag `d` as buzzer delay & `times` as the numbers to set buzzer
```cpp
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
```

- Control with the 7 segment number display
    - Assign the pin to assemble the number
        ```cpp
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
        ```
- high() & low() Function for display numbers
    ```cpp
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
    ```
