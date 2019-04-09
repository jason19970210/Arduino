// https://github.com/winlinvip/SimpleDHThttps://github.com/winlinvip/SimpleDHT
// humid & temp sensor
// download library `SimpleDHT`
// Sketch > Include Library > Manage Libraries > Filter

// Using `AVR ISP` for Programmer

#include <SimpleDHT.h>

// for DHT11
//   |-- VCC: 5V > Orange
//   |-- GND: GND > Yellow
//   |-- DATA: D2 (Digital) > Green
int pinDHT11 = 2; // put 
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed with error code: "); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print((int)temperature); Serial.print(" 'C, ");
  Serial.print((int)humidity); Serial.println(" RH");
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}
