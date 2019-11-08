//Buzzer Test

int buzzerPin = 33;
int freq = 2000;
int resolution = 8;
long previousTime = 0;
long interval = 1000;


void setup() {
  pinMode(buzzerPin, OUTPUT);
  ledcSetup(1, freq, resolution);
  ledcAttachPin(buzzerPin, 1);

//  for(int i=0; i<3; i++){
//    unsigned long currentTime = millis();
//    if(currentTime - previousTime > interval){ // over a second
//      if(freq == 2000){
//        freq = 0;
//      } else {
//      freq = 2000;
//      }
//    ledcWriteTone(1, freq);
//    previousTime = currentTime;
//    }
//  }
  unsigned long currentTime = millis();
  delay(1000);
  //unsigned long currentTime1 = millis();
  if(currentTime1 - currentTime > interval){ // over a second
    if(freq == 2000){
      freq = 0;
    } else {
      freq = 2000;
    }
    ledcWriteTone(1, freq);
    previousTime = currentTime;
  }
}

void loop() {
  /*
  unsigned long currentTime = millis();
  if(currentTime - previousTime > interval){ // over a second
    if(freq == 2000){
      freq = 0;
    } else {
      freq = 2000;
    }
    ledcWriteTone(1, freq);
    previousTime = currentTime;
  }*/
  
  // do other things here
}
