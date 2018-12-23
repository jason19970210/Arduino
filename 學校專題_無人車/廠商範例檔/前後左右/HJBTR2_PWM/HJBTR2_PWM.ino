int pinLF=14;     // 定義14腳位 左前
int pinLB=15;     // 定義15腳位 左後

int pinRF=16;    // 定義16腳位 右前
int pinRB=17;    // 定義17腳位 右後

int PWMEN1=3;
int PWMEN2=5;

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
void advance(int a)     // 前進
    {
     digitalWrite(pinRF,HIGH);  // 使馬達（前進）動作
     digitalWrite(pinRB,LOW);
             analogWrite(PWMEN1,200);
             analogWrite(pinRB, 0);
     digitalWrite(pinLF,HIGH);  // 使馬達（前進）動作
     digitalWrite(pinLB,LOW);
             analogWrite(PWMEN2,250);
             analogWrite(pinLB,0);
     delay(a * 100);     
    }

void turnR(int d)        //左轉(雙輪)
    {
     digitalWrite(pinRF,HIGH);  // 使馬達（前進）動作
     digitalWrite(pinRB,LOW);
             analogWrite(PWMEN1,230);
             analogWrite(pinRB, 0);
     digitalWrite(pinLF,LOW);   
     digitalWrite(pinLB,HIGH);
             analogWrite(pinLF,0);
             analogWrite(PWMEN2,230);
     delay(d * 50);
    }
void turnL(int e)        //右轉(雙輪)
    {
     digitalWrite(pinRF,LOW);
     digitalWrite(pinRB,HIGH);   
             analogWrite(pinRF,0);
             analogWrite(PWMEN1,230);
     digitalWrite(pinLF,HIGH);   
     digitalWrite(pinLB,LOW);
             analogWrite(PWMEN1,230);
             analogWrite(pinLB,0);
     delay(e * 50);
    }    
void stopp(int f)         //停止
    {
     digitalWrite(pinRB,LOW);
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,LOW);
     digitalWrite(pinLF,LOW);
     delay(f * 100);
    }
void back(int g)          //後退 
 {
     digitalWrite(pinRF,LOW);  // 使馬達（後退）動作
     digitalWrite(pinRB,HIGH);
             analogWrite(pinRF,0);
             analogWrite(PWMEN1, 230);
     digitalWrite(pinLF,LOW);  // 使馬達（後退）動作
     digitalWrite(pinLB,HIGH);
             analogWrite(pinLF,0);
             analogWrite(PWMEN2,230);
     delay(g * 100);     
    }


void loop()
 {
    advance(1);              // 正常前進 
    delay(1000);
    back(1);                 // 正常後退
    delay(1000);
    turnL(1);                // 左轉
    delay(1000);    
    turnR(1);                // 右轉 
    delay(1000);
 }
