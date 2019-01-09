int pinLF=17;     //  左前
int pinLB=16;     //  左後

int pinRF=15;    //  右前
int pinRB=14;    //  右後

int PWMEN1=5;   //左動力
int PWMEN2=3;   //右動力

// sonor sensor
int SonorIn = 9;
int SonorOut = 8;
int dist = 0;

// line sensor
const int LineRight = 2;
const int LineLeft = 6;
int LL;
int LR;

// IR sensor
const int IRRight = 12;
const int IRLeft = 13;
int IRR;
int IRL;


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
void getDist(){
  digitalWrite(SonorOut, LOW);
  delayMicroseconds(2);
  digitalWrite(SonorOut, HIGH);
  delayMicroseconds(10);
  digitalWrite(SonorOut, LOW);
  float Dist = pulseIn(SonorIn, HIGH);
  Dist = Dist / 5.8 / 10;  // Output as cm
  Serial.print("Dist:");
  Serial.print(Dist);
  dist = Dist;
}

void getLineStatus(){
  LL = digitalRead(LineLeft);
  LR = digitalRead(LineRight);
  Serial.print("  LL:");
  Serial.print(LL);
  Serial.print("  LR:");
  Serial.print(LR);
}

void getIR(){
  IRR = digitalRead(IRRight);
  IRL = digitalRead(IRLeft);
  Serial.print("  IRL:");
  Serial.print(IRL);
  Serial.print("  IRR:");
  Serial.print(IRR);
  //Serial.println(IRL);
  // only output 0 & 1
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
void stop()         //停止
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
void loop(){
  
    getDist();
    getLineStatus();
    getIR();

    if (IRL == 1 && IRR == 1){ // NORMAL STATUS
      if (LL == 0 && LR ==0){ //(0,0)
        //advance(100);
        Serial.println(" Go");
      } else if (LL == 0 && LR == 1){ //(0,1)
        //turnR(100);
        Serial.println(" TURN RIGHT");
      } else if (LL == 1 && LR == 0){ //(1,0)
        //turnL(100)
        Serial.println(" TURN LEFT");
      } else { //(1,1)
        //stop();
        Serial.println(" STOP");
      }
    } else if (IRL == 1 && IRR == 0){ // Right Dnager >> TURN LEFT
      Serial.println(" TURN LEFT");
    } else if (IRL == 0 && IRR == 1){ // Left Dnager >> TURN RIGHT
      Serial.println(" TURN RIGHT");
    } else if (IRL == 0 && IRR == 0){ // Both Danger
      Serial.println(" STOP");
    }



    
    /*
    if (LL == 0 && LR ==0){ //(0,0)
      //advance(100);
      Serial.println(" Go");
    } else if (LL == 0 && LR == 1){ //(0,1)
      //turnR(100);
      Serial.println(" TURN RIGHT");
    } else if (LL == 1 && LR == 0){ //(1,0)
      //turnL(100)
      Serial.println(" TURN LEFT");
    } else { //(1,1)
      //stop();
      Serial.println(" STOP");
    }
    */
    
    /*
    advance(100);              // 正常前進 
    delay(1000);
    back(100);                 // 正常後退
    delay(1000);
    turnL(100);                // 左轉
    delay(1000);    
    turnR(100);                // 右轉 
    delay(1000);
    */
    


}
