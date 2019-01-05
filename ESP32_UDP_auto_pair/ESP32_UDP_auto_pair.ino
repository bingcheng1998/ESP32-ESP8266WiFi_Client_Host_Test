

//#define ESP32_USED  //使用ESP32，注释掉即ESP8266
//#define WIFI_HOST   //使用WiFi热点
#define DEBUG_VERBOS  //详细串口输出
//----------------------------------------------------------
#ifdef ESP32_USED
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#ifdef WIFI_HOST
#define MAX_SRV_CLIENTS 1 //最大同时连接数，即可接入的设备数量的最大值，
#endif

#include <WiFiUdp.h>

WiFiUDP Udp;
unsigned int localPort = 1998;      // local port to listen on
IPAddress ESP_remoteIP;
int ESP_remotePORT;
uint8_t packetBuffer[255]; //buffer to hold incoming packet
uint8_t  ReplyBuffer[] = "I received:\t[";

//const char WiFiAPPSW[] = "12345678";    //设置AP模式下模块所发出的WIFI的密码



#ifdef WIFI_HOST
const char *ssid = "MyESP32AP";   //热点WiFi名称
const char *password = "12345678";
#else
const char * networkName = "fisher"; //中介WiFi名称
const char * networkPswd = "1234567899";
#endif

void setupWiFi()
{
#ifdef WIFI_HOST
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.softAPIP() );
#else
  connectToWiFi(networkName, networkPswd);
#endif
}

void setupUdp() {
  bool udp_setup_flag = false;
  int k = 0;
  Udp.begin(localPort);
  Serial.println("UDP connecting...");
  while (!udp_setup_flag) {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      Serial.println();
      ESP_remoteIP = Udp.remoteIP();
      ESP_remotePORT = Udp.remotePort();
      // read the packet into packetBuffer
      int len = Udp.read(packetBuffer, 255);
#ifdef DEBUG_VERBOS
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      Serial.print(ESP_remoteIP);
      Serial.print(", port ");
      Serial.println(ESP_remotePORT);
#endif
      if (packetBuffer[0] != 's') {
        Serial.print("You should sent \'s\' to start udp connection instead of ");
        Serial.println((char)packetBuffer[0]);
        continue;
      }
      uint8_t UDP_connected_reply[] = "UDP Connected";
      //      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

      Udp.beginPacket(ESP_remoteIP, ESP_remotePORT);
      Udp.write(UDP_connected_reply, 13);
      Udp.endPacket();
      udp_setup_flag = true;
    } else {
      Serial.print(".");
      delay(300);
      k++;
      if (k % 35 == 0) {
        Serial.print("\n");
      }
    }

  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println ("\n//---------Program Begin----------//");
  setupWiFi();
  Serial.println("WiFi connected");
  setupUdp();
  Serial.println("UDP connected");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
#ifdef DEBUG_VERBOS
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    Serial.print(Udp.remoteIP());
    Serial.print(", port ");
    Serial.println(Udp.remotePort());
#endif //DEBUG_VERBOS
    // read the packet into packetBuffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.print("message received:\t[");
    Serial.print((char*)packetBuffer);
    Serial.println("]");
    Udp.beginPacket(ESP_remoteIP, ESP_remotePORT);
    //     Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer, 13);
    Udp.write(packetBuffer, packetSize);
    Udp.write(']');
    Udp.endPacket();
  }
}
#ifndef WIFI_HOST
void connectToWiFi(const char * ssid, const char * pwd) {
  int k = 0;
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    k++;
    if (k % 35 == 0) {
      Serial.print("\n");
    }
  }
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
#endif //WIFI_HOST
