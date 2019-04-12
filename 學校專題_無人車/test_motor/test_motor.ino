int pin = 36;
int PWM = 5;


void test_motor(int power){                   //左退
  digitalWrite(pin,HIGH);  
  analogWrite(PWM,power);  //power:0~250
}

void setup() {
  pinMode(pin,OUTPUT);
  pinMode(PWM,OUTPUT);
}

void loop() {
  test_motor(200);

}
