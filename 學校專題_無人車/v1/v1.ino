// motor
int pinRF = 14;
int pinRB = 15;
int pinLF = 16;
int pinLB = 17;

int PWM1 = 3;
int PWM2 = 5;

int speed = 100;

// sonor sensor
int SonorIn = 9;
int SonorOut = 8;
int dist = 0;

// line sensor
const int LineRight = 2;
const int LineLeft = 6;
int LL; //left line sensor
int LR; //right line sensor
// 0 as white LOW
// 1 as black HIGH
// if right sensor goes to 1 as black
  // => R : 1
// the robot should go left

// if left senor goes to 1 as black
  // => L : 1
// the robot should go right

// IR sensor
const int IRRight = 12;
const int IRLeft = 13;
int IRR;
int IRL;


// FINCTIONS
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
  Serial.print(" L:");
  Serial.print(LL);
  Serial.print(" R:");
  Serial.print(LR);
  }
void getIR(){
  IRR = digitalRead(IRRight);
  IRL = digitalRead(IRLeft);
  Serial.print(" IRR: ");
  Serial.print(IRR);
  Serial.print(" IRL: ");
  Serial.println(IRL);
  // only output 0 & 1
  }
void forward(int f){
  digitalWrite(pinRF,HIGH);
  digitalWrite(pinRB,LOW);
    analogWrite(PWM1,200);
    analogWrite(pinRB, 0);
  digitalWrite(pinLF,HIGH);
  digitalWrite(pinLB,LOW);
    analogWrite(PWM2,250);
    analogWrite(pinLB,0);
   delay(f * 100);
  }
void backward(int b){
  
    delay(b * 100);
  }
void right(int l){
  
  delay(l * 50);
  }
void left(int r){
  
  delay(r * 50);
  }
void stop(int s){
  digitalWrite(pinRB,LOW);
  digitalWrite(pinRF,LOW);
  digitalWrite(pinLB,LOW);
  digitalWrite(pinLF,LOW);
  delay(s * 100);
  }
void test(int a){

}

void setup() {
  Serial.begin(9600);
  //sonor sensor
  pinMode(SonorIn, INPUT);
  pinMode(SonorOut, OUTPUT);
  //line sensor
  pinMode(LineLeft, INPUT);
  pinMode(LineRight, INPUT);
  //IR sensor
  pinMode(IRRight,INPUT);
  pinMode(IRLeft,INPUT);
  //motor
  pinMode(pinRF,OUTPUT); // 14
  pinMode(pinRB,OUTPUT); // 15
  pinMode(pinLF,OUTPUT); // 16
  pinMode(pinLB,OUTPUT); // 17
  pinMode(PWM1,OUTPUT); // 3
  pinMode(PWM2,OUTPUT); // 5

  // touch start line
  // forward
  /*
  if (LR == LOW && LL == LOW){
    forward(1);
    } else if (LR == HIGH && LL == HIGH){
      stop();
      } // end of if-else
  */

} // end of setup()


  
void loop(){
  
  getDist();
  getLineStatus();
  getIR();

  // 0 as white LOW
  // 1 as black HIGH
  
  // when dist < 20 stop the car
  // when LineSensor is (1,1), stop the car > LL && LR == HIGH
  // when IRL & IRR are (0,0), stop the car > IRR && IRL == LOW

  /*
  if (LL == HIGH && LR == HIGH || dist < 8 || IRL == LOW || IRR == LOW){
    Serial.print("STOP!!");
    // call stop()
    stop();
    
  } else if (LL == HIGH && LR == LOW){ // HIGH as black , LOW as white
    // turn left
    } else if (LL == LOW && LR == HIGH){
      // turn right
      } else { // LL == LOW && LR == LOW
        } // end of if-else
  */
  /*
  forward(1);
  stop();
  delay(1000);
  backward(1);
  stop();
  delay(1000);
  */

    
} // end of loop
