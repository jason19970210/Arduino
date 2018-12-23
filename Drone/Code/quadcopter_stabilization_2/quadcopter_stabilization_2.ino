#include "I2Cdev.h"
#include <Servo.h>
#include <SPI.h>
#include "RF24.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
//we need this to see nrf24l01 configuration in serial
#include "printf.h"



//end of libraries ###############################################

MPU6050 mpu;


float x_rotation, y_rotation, z_rotation;
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
bool first_loop = true;
//radio
RF24 radio(9,10);
uint8_t data[6];
const uint64_t pipe = 0xE8E8F0F0E1LL;
long last_received;
int controll_number = 159;

//values = 5.2, 0.02, 1500
//variables for movement and positions ###########################################
//for my quadcopter this are the best settings for pid
float x_kp = 5, x_ki = 0.02, x_kd = 1100; //values for PID X axis
int max_pid = 300;
float x_p_out, x_i_out, x_d_out, x_output; //outputs for PID
float x_now, x_lasttime = 0, x_timechange;
float x_input, x_lastinput = 0, x_setpoint = 0;
float x_error, x_errorsum = 0, x_d_error, x_lasterror;


//values = 5.2, 0.02, 1500
float y_kp = 5, y_ki = 0.02, y_kd = 1100; //values for PID Y axis
float y_p_out, y_i_out, y_d_out, y_output; //outputs for PID
float y_now, y_lasttime = 0, y_timechange;
float y_input, y_lastinput = 0, y_setpoint = 0;
float y_error, y_errorsum = 0, y_d_error, y_lasterror;

float z_kp = 2, z_ki = 0, z_kd = 0; //values for PID Z axis
float z_p_out, z_i_out, z_d_out, z_output; //outputs for PID
float z_now, z_lasttime = 0, z_timechange;
float z_input, z_lastinput = 0, z_setpoint = 0;
float z_error, z_errorsum = 0, z_d_error, z_lasterror;


//set it to 0 and see on serial port what is the value for x and y rotation, use only if your flightcontroller board is not perfevtly leveled. If your board is perfectly leveled set it to 0
float x_level_error = 0;
float y_level_error = 0;


/*
 * 
 * 
 * JUNE 2016 - APRIL 2017
 * C by Nikodem Bartnik
 * nikodem.bartnik@gmail.com
 * nikodembartnik.pl
 * 
 * 
 * 
 */

#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
int motor1_power;
int motor2_power;
int motor3_power;
int motor4_power;

float allmotors_power = 600;


// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container

VectorFloat gravity;    // [x, y, z]            gravity vector

float rotation[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
int safe_lock = 1;




volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}


void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

printf_begin();

    Serial.begin(115200);

    Serial.println("Initializing I2C devices...");
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
//    bmp.begin();  
    radio.begin();
    delay(1000);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);

    radio.openReadingPipe(1,pipe);
    radio.startListening();
    
   

    // load and configure the DMP
    Serial.println("Initializing DMP...");
    devStatus = mpu.dmpInitialize();

    // gyro offsets here
    mpu.setXGyroOffset(87);
    mpu.setYGyroOffset(77);
    mpu.setZGyroOffset(110);
    mpu.setZAccelOffset(2287); 
    mpu.setYAccelOffset(-1283);
    mpu.setXAccelOffset(-3083);

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {

        Serial.println("Enabling DMP...");
        mpu.setDMPEnabled(true);

        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

      
        dmpReady = true;

        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print("DMP Initialization failed (code ");
        Serial.print(devStatus);
        Serial.println(")");
    }

    motor1.attach(5);
    motor2.attach(8);
    motor3.attach(7);
    motor4.attach(4);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    digitalWrite(A0, LOW);
    motor1.write(0);
    motor2.write(0);
    motor3.write(0);
    motor4.write(0);

radio.printDetails();
}




void loop() {

    if (radio.available()) {
    
    bool done = false;
    while (!done){
     
     done = radio.read(data, sizeof(data));

    // Serial.print("Controll number: ");
     //Serial.println(data[0]);
     
      if((millis()-last_received) < 3000){
        if(data[0] == controll_number){
          Serial.print("DATA1: ");
          Serial.println(data[1]);
          allmotors_power = map(data[1], 0, 255, 800, 1500);
          if(allmotors_power < 0){
            allmotors_power = 0;
          }

          
     //allmotors_power = map(data[1], 0, 255, 800, 1600);
     x_setpoint = data[3] - 20;
     y_setpoint = data[2] - 20;
     Serial.print("PID OUT X: ");
     Serial.print(x_rotation);
     Serial.print(" PID OUT Y: ");
     Serial.print(y_rotation);
     Serial.print("Z NOW: ");
     Serial.println(z_rotation);
     Serial.print(" TIME: ");
     Serial.println(millis());

Serial.print("MOTORS POWER: ");
Serial.println(allmotors_power);
  
     
        }
     }
     // Serial.println(data[1]);
      if(done == true){
      last_received = millis();
      }
  }   
 }

 if((millis()-last_received) > 3000 && allmotors_power > 0){
    safe_lock = 0;
     }
 
    // if programming failed, don't try to do anything
   // if (!dmpReady) return;

   
    while (!mpuInterrupt && fifoCount < packetSize) {
     
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
       

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

    if(safe_lock == 1){
   
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(rotation, &q, &gravity);

          x_rotation = rotation[1] * 180/M_PI - x_level_error;
            y_rotation = rotation[2] * 180/M_PI - y_level_error;
            z_rotation = rotation[0] * 180/M_PI;

/*
          if(pressure_loop_number == 10){
           // Serial.print("Preasure: ");
            //Serial.println(bmp.readAltitude());
            pressure_loop_number = 0; 
            allmotors_power = 1000;
           }
            pressure_loop_number++;  
*/

           if(first_loop == true){
            z_setpoint = z_rotation;
          //  current_altitude = bmp.readAltitude();
            //set_altitude = current_altitude;
            first_loop = false;
           }
          
            
            
        motor1_power = allmotors_power;
        motor2_power = allmotors_power;
        motor3_power = allmotors_power;
        motor4_power = allmotors_power;
          if(allmotors_power > 1500){
               allmotors_power = 1500;
                
                
                }

                 
                 x_output = calculatePID(0, x_rotation);
                 y_output = calculatePID(1, y_rotation);
                 z_output = calculatePID(2, z_rotation);

    

                 motor1_power += x_output/2;
                 motor1_power += z_output;
                 motor4_power -= x_output/2;
                 motor4_power += z_output;

                 motor2_power -= y_output/2;
                 motor2_power -= z_output;
                 motor3_power += y_output/2;
                 motor3_power -= z_output;
                 
             
                motor1.writeMicroseconds(motor1_power);
                motor4.writeMicroseconds(motor4_power); 
                motor2.writeMicroseconds(motor2_power);
                motor3.writeMicroseconds(motor3_power); 
                mpu.resetFIFO();
               
     
    }else{
                motor1.write(0);
                motor2.write(0);
                motor3.write(0);
                motor4.write(0);
    }
}
}




   float calculatePID(int _axis, float _angel){

      // X AXIS
      if(_axis == 0){
                 x_now = millis();
                 x_timechange = x_now - x_lasttime;
                 x_error = x_setpoint - _angel;
                 x_p_out = (x_kp * x_error);
                
                 x_errorsum = (x_errorsum + x_error);
                 if(x_errorsum > 1023){
                  x_errorsum = 1023;
                 }
                 if(x_errorsum < -1023){
                  x_errorsum = -1023;
                 }
                 x_i_out = x_ki * x_errorsum;
                 x_d_error = (x_error - x_lasterror) / x_timechange;
                 x_d_out = x_kd * x_d_error;
                 x_lasterror = x_error;
                 x_output = x_p_out + x_i_out + x_d_out;
                 if(x_output > max_pid){
                  x_output = max_pid;
                 }else if(x_output < -(max_pid)){
                  x_output = -(max_pid);
                 }
                 x_lasttime = millis();
                 return x_output;
      }

      // Y AXIS
      else if(_axis == 1){
                 y_now = millis();
                 y_timechange = y_now - y_lasttime;
                 y_error = y_setpoint - _angel;
                 y_p_out = (y_kp * y_error);

                 y_errorsum = (y_errorsum + y_error) * y_timechange;
                 if(y_errorsum > 1023){
                  y_errorsum = 1023;
                 }
                 if(y_errorsum < -1023){
                  y_errorsum = -1023;
                 }
                 y_i_out = y_ki * y_errorsum;
                 y_d_error = (y_error - y_lasterror) / y_timechange;
                 y_d_out = y_kd * y_d_error;
                 y_lasterror = y_error;
                 y_output = y_p_out + y_i_out + y_d_out;
                 if(y_output > max_pid){
                  y_output = max_pid;
                 }else if(y_output < -(max_pid)){
                  y_output = -(max_pid);
                 }
                 y_lasttime = millis();
                 return y_output;

                 // ALTITUDE
     // } else if(_axis == 2){
      //           return (set_altitude - current_altitude) * 20;
      }else if(_axis == 2){
                 z_now = millis();
                 z_timechange = z_now - z_lasttime;
                 z_error = z_setpoint - _angel;
                 z_p_out = (z_kp * z_error);

                 z_errorsum = (z_errorsum + z_error) * z_timechange;
                 if(z_errorsum > 1023){
                  z_errorsum = 1023;
                 }
                 if(z_errorsum < -1023){
                  z_errorsum = -1023;
                 }
                 z_i_out = z_ki * z_errorsum;
                 z_d_error = (z_error - z_lasterror) / z_timechange;
                 z_d_out = z_kd * y_d_error;
                 z_lasterror = y_error;
                 z_output = z_p_out + z_i_out + z_d_out;
                 if(z_output > max_pid){
                  z_output = max_pid;
                 }else if(z_output < -(max_pid)){
                  z_output = -(max_pid);
                 }
                 z_lasttime = millis();
                 return z_output;

                 // ALTITUDE
     // } else if(_axis == 2){
      //           return (set_altitude - current_altitude) * 20;
      }else{
        return 0;
      }


      
      
    }

