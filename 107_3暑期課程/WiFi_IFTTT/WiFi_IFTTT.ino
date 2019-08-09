// VCC : vin
// Data : D5
// GND : GND

#include <WiFi.h>
#include <WiFiClient.h>
#include <dht.h>

#define dht_dpin 5 
dht DHT;

const  char *  ssid  =  "5F B050C"; 
const  char *  password  = "im5fb050c";

// IFTTT Key
const  char *  key  =  "hXmytxHquotaEQw593DchDHxE1y0JqNPOKYJQDGAXIf";


const char* host = "maker.ifttt.com";
const char* event   = "notify_me";
const int httpsPort = 80;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("connecting to ");
  Serial.println(host);
  DHT.read11(dht_dpin);
  float temp = DHT.temperature;
  float humi = DHT.humidity;

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  // maker.ifttt.com/trigger/{event}/with/key/{key}
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += key;
  url +="?value1=Temperature:";
  url +=temp;

  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  String line = client.readStringUntil('\n');
  Serial.print("reply: ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println();

  delay(10000);
}
