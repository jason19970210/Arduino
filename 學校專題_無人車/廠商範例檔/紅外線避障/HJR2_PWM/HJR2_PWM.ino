int MotorRight1=14; //A0 IN1
int MotorRight2=15; //A1 IN2
int MotorLeft1=16;  //A2 IN3
int MotorLeft2=17;  //A3 IN4

int MotorRPWM=5;  //PWM  5
int MotorLPWM=3;  //PWM 3
const int SensorLeft = 12;      //左感測器輸入腳
const int SensorRight = 13;     //右感測器輸入腳
int SL;    //左感測器狀態
int SR;    //右感測器狀態

void setup()
{  
  Serial.begin(9600);
  pinMode(MotorRight1, OUTPUT);  // 腳位 14 (PWM)
  pinMode(MotorRight2, OUTPUT);  // 腳位 15 (PWM)
  pinMode(MotorLeft1,  OUTPUT);  // 腳位 16 (PWM) 
  pinMode(MotorLeft2,  OUTPUT);  // 腳位 17 (PWM)
  
  pinMode(MotorLPWM,  OUTPUT);  // 腳位 3 (PWM) 
  pinMode(MotorRPWM,  OUTPUT);  // 腳位 5 (PWM)
  
  pinMode(SensorLeft, INPUT); //定義左感測器
  pinMode(SensorRight, INPUT); //定義右感測器
}

void loop() 
 {
 SL = digitalRead(SensorLeft);
 SR = digitalRead(SensorRight);
       if (SL == HIGH&&SR==HIGH)//  前進
   { 
             digitalWrite(MotorRight1,HIGH);
             digitalWrite(MotorRight2,LOW);
             analogWrite(MotorRPWM,180); 
             
             digitalWrite(MotorLeft1,HIGH);
             digitalWrite(MotorLeft2,LOW);
             analogWrite(MotorLPWM,180);
           

         }      
       
       else 
      {  
         if (SL == HIGH & SR == LOW)
        {  
            delay(1);
            digitalWrite(MotorRight1,HIGH);
             digitalWrite(MotorRight2,LOW);
             analogWrite(MotorRPWM,250);
             
             digitalWrite(MotorLeft1,LOW);
             digitalWrite(MotorLeft2,HIGH);
             analogWrite(MotorLPWM,250);
        }
         else if (SR == HIGH & SL == LOW) 
        {  
          delay(1); 
             digitalWrite(MotorRight1,LOW);
             digitalWrite(MotorRight2,HIGH);
             analogWrite(MotorRPWM,250);
             
             digitalWrite(MotorLeft1,HIGH);
             digitalWrite(MotorLeft2,LOW);
             analogWrite(MotorLPWM,250);
          
        }
         else //  停止
        {    
       digitalWrite(MotorRight1,LOW);
        digitalWrite(MotorRight2,HIGH);
        analogWrite(MotorRPWM,180);
        digitalWrite(MotorLeft1,LOW);
        digitalWrite(MotorLeft2,HIGH);;
        analogWrite(MotorLPWM,180);
        delay(800); 
        
        digitalWrite(MotorRight1,HIGH);
        digitalWrite(MotorRight2,LOW);
        analogWrite(MotorRPWM,180);
       delay(500);
        }}}

