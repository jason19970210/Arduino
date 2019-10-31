// Usage : high(<int>, <int>)
// the first int will be the int number you want to display on the 7-segment display
// the second int is the `delay` time
// all pins goes to the digital pin
/*
      13  12  11  10  9   8
      |   |   |   |   |   |
 ==============================
||    ---     ---     ---     ||
||   |   |   |   |   |   |    ||
||    ---     ---     ---     ||
||   |   |   |   |   |   |    ||
||    ---  .  ---  .  ---  .  ||
 ==============================
      |   |   |   |   |   |
      2   3   4   5   6   7
*/

int timer = 9; //second

#define d1 13
#define d2 10
#define d3 9

const int seg[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int dig[3] = {d1, d2, d3};
const int list[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}; //index of storage dicts

void setup() {
  Serial.begin(9600);

  for(int i=2; i<14; i++){
    pinMode(i, OUTPUT);
  }

}

void loop() {

  digitalWrite(dig[0],HIGH); // make the first digit not display
  digitalWrite(dig[1],HIGH); // make the second digit not display
  
  // if you want to display `10`, you should make the second digit display `1`, then show `0` on the third digit


  // Count Down
  for(int i=timer; i>=0; i--){
      if(i != 0){
        high(i,1000);
        low(i, 0);
      } else { // i ==0
        Serial.println("Times out");
      }
  }

}

byte * int0() {
  static byte s[6];
  s[0] = 2;
  s[1] = 3;
  s[2] = 5;
  s[3] = 8;
  s[4] = 11;
  s[5] = 12;
  return s;
}
byte * int1() {
  static byte s[2];
  s[0] = 5;
  s[1] = 8;
  return s;
}
byte * int2() {
  static byte s[5];
  s[0] = 2;
  s[1] = 3;
  s[2] = 6;
  s[3] = 8;
  s[4] = 12;
  return s;
}
byte * int3() {
  static byte s[5];
  s[0] = 3;
  s[1] = 5;
  s[2] = 6;
  s[3] = 8;
  s[4] = 12;
  return s;
}
byte * int4() {
  static byte s[4];
  s[0] = 5;
  s[1] = 6;
  s[2] = 8;
  s[3] = 11;
  return s;
}
byte * int5() {
  static byte s[5];
  s[0] = 3;
  s[1] = 5;
  s[2] = 6;
  s[3] = 11;
  s[4] = 12;
  return s;
}
byte * int6() {
  static byte s[6];
  s[0] = 2;
  s[1] = 3;
  s[2] = 5;
  s[3] = 6;
  s[4] = 11;
  s[5] = 12;
  return s;
}
byte * int7() {
  static byte s[3];
  s[0] = 5;
  s[1] = 8;
  s[2] = 12;
  return s;
}
byte * int8() {
  static byte s[7];
  s[0] = 2;
  s[1] = 3;
  s[2] = 5;
  s[3] = 6;
  s[4] = 8;
  s[5] = 11;
  s[6] = 12;
  return s;
}
byte * int9() {
  static byte s[6];
  s[0] = 3;
  s[1] = 5;
  s[2] = 6;
  s[3] = 8;
  s[4] = 11;
  s[5] = 12;
  return s;
}


int high(int num, int d){

  if(num == 0){
    byte *pt = int0();
      for (byte i = 0; i < list[num]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 1){
    byte *pt = int1();
      for (byte i = 0; i < list[1]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 2){
    byte *pt = int2();
      for (byte i = 0; i < list[2]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 3){
    byte *pt = int3();
      for (byte i = 0; i < list[3]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 4){
    byte *pt = int4();
      for (byte i = 0; i < list[4]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 5){
    byte *pt = int5();
      for (byte i = 0; i < list[5]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 6){
      byte *pt = int6();
      for (byte i = 0; i < list[6]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 7){
    byte *pt = int7();
      for (byte i = 0; i < list[7]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 8){
    byte *pt = int8();
      for (byte i = 0; i < list[8]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else if (num == 9){
    byte *pt = int9();
      for (byte i = 0; i < list[9]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), HIGH);
      }
      delay(d);
  } else {
      //none
  }

} // end of high()


int low(int num, int d){

  if(num == 0){
    byte *pt = int0();
      for (byte i = 0; i < list[0]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 1){
    byte *pt = int1();
      for (byte i = 0; i < list[1]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 2){
    byte *pt = int2();
      for (byte i = 0; i < list[2]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 3){
    byte *pt = int3();
      for (byte i = 0; i < list[3]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 4){
    byte *pt = int4();
      for (byte i = 0; i < list[4]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 5){
    byte *pt = int5();
      for (byte i = 0; i < list[5]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 6){
      byte *pt = int6();
      for (byte i = 0; i < list[6]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 7){
    byte *pt = int7();
      for (byte i = 0; i < list[7]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 8){
    byte *pt = int8();
      for (byte i = 0; i < list[8]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else if (num == 9){
    byte *pt = int9();
      for (byte i = 0; i < list[9]; i++) {
        //Serial.println(*(pt + i));
        digitalWrite(*(pt + i), LOW);
      }
      delay(d);
  } else {
      //none
  }

} // end of low()
