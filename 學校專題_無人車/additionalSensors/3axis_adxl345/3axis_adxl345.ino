//REF:http://arduino365.com/2018/11/22/3axisadxl345/

#include <Wire.h>
#define Register_ID 0 //16進制 0x00 10進制 0
#define Register_2D 0x2D //省電控制
#define Register_X0 0x32 //x軸數值0
#define Register_X1 0x33 //x軸數值1
#define Register_Y0 0x34 //y軸數值0
#define Register_Y1 0x35 //y軸數值1
#define Register_Z0 0x36 //z軸數值0
#define Register_Z1 0x37 //z軸數值1

//映射地址
int ADXAddress = 0xA7 >> 1;//轉換位碼
int reading = 0; 
int val=0;
int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
double Xg,Yg,Zg;


void setup()
{
   Wire.begin(); //初始化I2C協定          
   Serial.begin(9600);  //初始化串口
   delay(100);
   // enable to measute g data
   Wire.beginTransmission(ADXAddress); //begin
   Wire.write(Register_2D);//write ADXL345 寄存器映射地址
   Wire.write(8);
   Wire.endTransmission(); // end
}

void loop()
{
// X
   Wire.beginTransmission(ADXAddress);
   Wire.write(Register_X0);
   Wire.write(Register_X1);
   Wire.endTransmission();
   Wire.requestFrom(ADXAddress,2); //request 2個字節
   if(Wire.available()<=2)
   {
     X0 = Wire.read();
     X1 = Wire.read(); 
     X1=X1<<8;
     X_out=X0+X1;   
   }

// Y
   Wire.beginTransmission(ADXAddress); // 开启发送
   Wire.write(Register_Y0);//写入ADXL345寄存器映射地址
   Wire.write(Register_Y1);//写入ADXL345寄存器映射地址
   Wire.endTransmission();//结束发送
   Wire.requestFrom(ADXAddress,2); //请求ADXL345二个字节
   if(Wire.available()<=2)   //获取<=2个数据
   {
     Y0 = Wire.read();
     Y1 = Wire.read(); 
     Y1=Y1<<8;
     Y_out=Y0+Y1;
   }
   
// Z
   Wire.beginTransmission(ADXAddress); // 开启发送
   Wire.write(Register_Z0);//写入ADXL345寄存器映射地址
   Wire.write(Register_Z1);//写入ADXL345寄存器映射地址
   Wire.endTransmission();//结束发送
   Wire.requestFrom(ADXAddress,2); //请求ADXL345二个字节
   if(Wire.available()<=2)   //获取<=2个数据
   {
     Z0 = Wire.read();
     Z1 = Wire.read(); 
     Z1=Z1<<8;
     Z_out=Z0+Z1;
   }
   /*
   Xg=X_out/256.0;
   Yg=Y_out/256.0;
   Zg=Z_out/256.0;
   */
    Xg=X_out;  
    Yg=Y_out;  
    Zg=Z_out;  
   Serial.print("X= ");
   Serial.print(Xg);
   Serial.print("       ");
   Serial.print("Y= ");
   Serial.print(Yg);
   Serial.print("       ");
   Serial.print("Z= ");
   Serial.print(Zg);
   Serial.println("  ");
   delay(200);
}
