int servoPinRight = 11;
int servoPinLeft = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(servoPinRight, OUTPUT);
  pinMode(servoPinLeft, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(servoPinRight, HIGH);
  digitalWrite(servoPinLeft, HIGH);
  //delayMicroseconds(100);
  digitalWrite(servoPinRight,LOW);
  digitalWrite(servoPinLeft, LOW);
  delay(20);
}
