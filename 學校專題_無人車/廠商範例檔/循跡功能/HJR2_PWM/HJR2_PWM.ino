#include <Servo.h>

// motor pin
int MotorRight1=14; //A0 IN1
int MotorRight2=15; //A1 IN2
int MotorLeft1=16;  //A2 IN3
int MotorLeft2=17;  //A3 IN4

int MotorRPWM=5;  //PWM 5
int MotorLPWM=3;  //PWM 3

// LineSensor pin
const int SensorLeft = 2;      //左感測器輸入腳
const int SensorRight = 6;     //右感測器輸入腳
int SL;    //左感測器狀態
int SR;    //右感測器狀態
// 0 as white
// 1 as black
// if right sensor goes to 1 as black
// the robot should go right
// if left sensor goes to 1 as black
// the robot should go left

// SonorSensor pin
int inputPin = 9;
int outputPin = 8;


/*
// Ways to go
int Fgo = 8; // 前進
int Rgo = 6; // 右轉
int Lgo = 4; // 左轉
int Bgo = 2; // 倒車
*/

void setup()
{  
  Serial.begin(9600);
  pinMode(MotorRight1, OUTPUT);  // 腳位 14 (PWM)
  pinMode(MotorRight2, OUTPUT);  // 腳位 15 (PWM)
  pinMode(MotorLeft1,  OUTPUT);  // 腳位 16 (PWM) 
  pinMode(MotorLeft2,  OUTPUT);  // 腳位 17 (PWM)
  
  pinMode(MotorLPWM,  OUTPUT);  // 腳位 3 (PWM) 
  pinMode(MotorRPWM,  OUTPUT);  // 腳位 5 (PWM)

  //LineSensor
  pinMode(SensorLeft, INPUT); //定義左感測器
  pinMode(SensorRight, INPUT); //定義右感測器
  //SonorSensor
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);

  
}

// Functions
// Read distence
  // F
void getDistanceFront(){
  digitalWrite(outputPin, LOW);//讓超聲波發射低電壓2μs
  delayMicroseconds(2);
  //讓超聲波發射高電壓10μs at least 10μs
  digitalWrite(outputPin, HIGH);
  delayMicroseconds(10);
      
  digitalWrite(outputPin, LOW);    // 維持超聲波發射低電壓
  float Fdistance = pulseIn(inputPin, HIGH);//讀差相差時間
  Fdistance = Fdistance/5.8/10; //將時間轉為距離 cm
  //Serial.print("F distance: ");//輸出距離 cm
  //Serial.println(Fdistance); 
  }
  // L
    // rotate car to left
    // getDistanceFront()
    // Ldistance = Fdistance/5.8/10;
  // R
    // rotate car to right
    // getDistanceFront()
    // Rdistance = Fdistance/5.8/10;



void loop() {
 SL = digitalRead(SensorLeft);
 SR = digitalRead(SensorRight);
 getDistanceFront(); //void getDistanceFront()
 
 //print value of two sensors
 Serial.print("R: ");
 Serial.print(SL);
 Serial.print(" ,L: ");
 Serial.print(SR);
 Serial.print(" ,FDist: ");
 Serial.println(Fdistance);
 
       // 前進
       if (SL == LOW&&SR==LOW){ 
             digitalWrite(MotorRight1,HIGH);
             digitalWrite(MotorRight2,LOW);
             analogWrite(MotorRPWM,130); //0---100--250
             
             digitalWrite(MotorLeft1,HIGH);
             digitalWrite(MotorLeft2,LOW);
             analogWrite(MotorLPWM,130);
         } // end of if
         else {  
         if (SL == HIGH & SR == LOW){  
            delay(1);
             digitalWrite(MotorRight1,HIGH);
             digitalWrite(MotorRight2,LOW);
             analogWrite(MotorRPWM,130);
             
             digitalWrite(MotorLeft1,LOW);
             digitalWrite(MotorLeft2,HIGH);
             analogWrite(MotorLPWM,130);
          } else if (SR == HIGH & SL == LOW) {  
          delay(1); 
             digitalWrite(MotorRight1,LOW);
             digitalWrite(MotorRight2,HIGH);
             analogWrite(MotorRPWM,130);
             
             digitalWrite(MotorLeft1,HIGH);
             digitalWrite(MotorLeft2,LOW);
             analogWrite(MotorLPWM,130);
          
          } else if (SR == HIGH & SL == HIGH) {    
        digitalWrite(MotorRight1,LOW);
        digitalWrite(MotorRight2,LOW);
        analogWrite(MotorRPWM,0);
        digitalWrite(MotorLeft1,LOW);
        digitalWrite(MotorLeft2,LOW);;
        analogWrite(MotorLPWM,0);
          } // end of else if
        } // end of else
} // end of void loop
