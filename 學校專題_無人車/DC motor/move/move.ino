#include <Servo.h> 
int pinLF=17;     //  左前
int pinLB=16;     //  左後

int pinRF=15;    //  右前
int pinRB=14;    //  右後

int PWMEN1=5;   //左動力
int PWMEN2=3;   //右動力

void setup()
 {
  Serial.begin(9600);     // 定義馬達輸出腳位 
  pinMode(pinLB,OUTPUT); // 腳位 6 
  pinMode(pinLF,OUTPUT); // 腳位 9 
  pinMode(pinRB,OUTPUT); // 腳位 10 
  pinMode(pinRF,OUTPUT); // 腳位 11 
  
  pinMode(PWMEN1,OUTPUT); // 腳位 3 (PWM) 
  pinMode(PWMEN2,OUTPUT); // 腳位 5 (PWM)

 }
 
//#####################################################
 
void Lback(int power){                   //左退
  digitalWrite(pinLF,HIGH);  
  digitalWrite(pinLB,LOW);
            analogWrite(PWMEN1,power);  //power:0~250
            analogWrite(pinRB, 0);
}
void Lgo(int power){                       //左進
  digitalWrite(pinLF,LOW);  
  digitalWrite(pinLB,HIGH);
             analogWrite(PWMEN1,power);
             analogWrite(pinRF, 0);
}
void Rgo(int power){
  digitalWrite(pinRF,HIGH);   
  digitalWrite(pinRB,LOW);
             analogWrite(pinRB,0);
             analogWrite(PWMEN2,power);
}
void Rback(int power){
  digitalWrite(pinRF,LOW);   
  digitalWrite(pinRB,HIGH);
             analogWrite(pinRF,0);
             analogWrite(PWMEN2,power);
}
void stopp()         //停止
    {
     digitalWrite(pinRB,LOW);
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,LOW);
     digitalWrite(pinLF,LOW);
    }

//################################################//

void advance(int power){
  Lgo(power);
  Rgo(power);
}
void back(int power){
  Lback(power);
  Rback(power);
}
void turnL(int power){
  Lback(power);
  Rgo(power);
}
void turnR(int power){
  Lgo(power);
  Rback(power);
}

//#######################################################//
void loop()
{
    advance(100);              // 正常前進 
    delay(1000);
    back(100);                 // 正常後退
    delay(1000);
    turnL(100);                // 左轉
    delay(1000);    
    turnR(100);                // 右轉 
    delay(1000);


}
