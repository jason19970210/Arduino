#include<WiFi.h>
#include<WiFiClient.h>
#include<dht.h>

#define dht_dpin 5
dht DHT;

const char * ssid = "";
const char * password = "";


//IFTTT Key
const char * key = "fqAgzAy4KQWGJzQ1AvgXg5oHxjBgy02qWrJRqW1qUsm";

const char * host = "maker.ifttt.com";
const char * event = "notify_me";
const int * httpsPort = 80;

WiFiClient client;


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(.);
    }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

}

void loop() {
  Serial.println("Connecting to ");
  Serial.println(host);
  DHT.readall(dft_dpin);
  float temp = DHT.temperature;
  float humi = DHT.humidity;

  if (!client.connect(host, httpsPort)){
    Serial.println("Connection Failed!!");
    return;
    }

  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += key;
  url += "?value1=Temperature:";
  url += temp;


  Serial.print("Request URL : ");
  Serial.println(url);

  client.print(String("GET ") + url + "HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: Close\r\n\r\n");
                
  while (client.connected()){
    String line = client.readStringUntil("\n");
    if (line == "\r"){
      break;
    }
  }

  String line = client.readStringUntil("\n");
  Serial.print("Reply : ");
  Serial.println(line);
  Serial.println("Closing Connection !!");
  Serial.println();

  delay(10000);

}
