int runTimer = 1; 
int runFor = 10; //set timer (count in seconds)

void setup() {
   Serial.begin(9600);
}

void loop() {
  Serial.println("loop");
   if(runTimer == 1){
    
      //Start timer
      timer();
      
   }

   //when timer alert
   runTimer = 0;
   delay(1000);
   // or call other function here when timer alert 
   
}

// Function

void timer() {

   // Countdown and print value
   for(int timer = runFor; timer > 0; --timer){ // --timer => timer = timer -1
      Serial.print(timer);
      Serial.println(" SECOND!");
      delay(1000);
   }
   
   // When Countdown goes to 0
   Serial.println("TIME ALERT!!");
   
   //Add Other Function Here!!! eg. Notification
}
