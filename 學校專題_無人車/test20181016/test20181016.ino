int pinLF = 14; //左前 14
int pinLB = 15; //左後 15
int pinRF = 16; //右前 16
int pinRB = 17; //右後 17

int PWM1 = 3;
int PWM2 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(pinLF,OUTPUT);
  pinMode(pinLB,OUTPUT);
  pinMode(pinRF,OUTPUT);
  pinMode(pinRB,OUTPUT);

  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
}

void rightMove(int a){
  digitalWrite(pinRF,HIGH);
  digitalWrite(pinRB,LOW);
  analogWrite(PWM1,200);
  analogWrite(pinRB,0);
  
  digitalWrite(pinLF,HIGH);
  //digitalWrite(pinLF,LOW); //NOT WORKING
  digitalWrite(pinLB,LOW);
  delay(a*100);
}
  
void leftMove(int b){
  digitalWrite(pinLF,HIGH);
  digitalWrite(pinLB,LOW);
  analogWrite(PWM2,200);
  analogWrite(pinLB,0);
  
  digitalWrite(pinRF,HIGH);
  //digitalWrite(pinRF,LOW); //NOT WORKING
  digitalWrite(pinRB,LOW);
  delay(b*100);
}

void stop(){
  digitalWrite(pinLF,LOW);
  digitalWrite(pinLB,LOW);
  digitalWrite(pinRF,LOW);
  digitalWrite(pinRB,LOW);
}

void loop() {

  //leftMove(10);
  //Serial.println("L");
  //stop();
  //delay(1000);
  
  rightMove(10);
  //Serial.println("R");
  stop();
  delay(1000);
    
}
