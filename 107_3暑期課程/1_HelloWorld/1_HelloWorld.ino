// 太陽能板：
//    - 紅線：A0
//    - 黑線：GND


const int analogIn = A0;
double Voltage = 0;
int RawValue= 0;

void setup() {
  
  Serial.begin(9600);
  
  
}

void loop() {

  //Serial.println("Hello World"); // Hello World
  //Serial.println('Hello World'); // 27748
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Serial.print("Raw Value = " ); // shows pre-scaled value
  Serial.print(RawValue);
  Serial.print(" mV = "); // shows the voltage measured
  Serial.println(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
  delay(1000);

  // 室內光：500 mV
  // 手電筒：約 1000 mV  
}
