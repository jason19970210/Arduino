// 太陽能板：
//    - 紅線：A0
//    - 黑線：GND


const int solar_analogIn = A0;
const int batteru_analohIn = A1;
double solar_Voltage = 0;
double battery_Voltage = 0;
int solar_RawValue = 0;
int battery_RawValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  //Serial.println("Hello World"); // Hello World
  //Serial.println('Hello World'); // 27748
  solar_RawValue = analogRead(solar_analogIn);
  solar_Voltage = (solar_RawValue / 1024.0) * 5000; // Gets you mV
  //Serial.print("Raw Value = " ); // shows pre-scaled value
  //Serial.print(solar_RawValue);
  Serial.print("solar_Voltage = "); // shows the voltage measured
  Serial.print(solar_Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
  Serial.println(" mV");
  delay(1000);

  // 空電阻值：1450 ~ 1480 上下
  // 室內光：約 2500 mV
  // 手電筒：約 5000 mV

  // 智慧農業應用
    // 日照長度
}
