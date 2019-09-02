#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

// 設定電磁閥開關及紅綠燈Pin 值
int mSwitch = 2;
int LEDRed = 3;
int LEDGreen = 4;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // 建立 MFRC522.

void setup()
{
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDGreen, OUTPUT);
  pinMode(mSwitch, OUTPUT);

  Serial.begin(9600);   // 設定串列通訊速率
  SPI.begin();      // 設定  SPI bus
  mfrc522.PCD_Init();   // 設定 MFRC522
  Serial.println(" Put your card close to the reader...");
  Serial.println();
}
void loop()
{
  digitalWrite(LEDGreen, LOW);
  digitalWrite(LEDRed, LOW);
  digitalWrite(mSwitch, LOW);
  // 是否為新卡？
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // 選擇一張卡
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("Card No. :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print(" Message : ");
  content.toUpperCase();

  //需要改成可通行的卡號
  if (content.substring(1) == "70 BA 96 28")
  {
    Serial.println(" Pass... ");
    Serial.println();
    // 亮綠燈, 電磁閥開
    digitalWrite(LEDGreen, HIGH);
    digitalWrite(LEDRed, LOW);
    digitalWrite(mSwitch, HIGH);
    delay(3000);
  }

  else   {
    Serial.println(" Stop...");
    // 亮紅燈, 電磁閥關
    digitalWrite(LEDGreen, LOW);
    digitalWrite(LEDRed, HIGH);
    digitalWrite(mSwitch, LOW);
    delay(3000);
  }
}
