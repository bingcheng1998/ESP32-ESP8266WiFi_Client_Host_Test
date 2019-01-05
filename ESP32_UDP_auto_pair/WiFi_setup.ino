#include "para_preset.h"

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
  Serial.println("localPort: ");
  Serial.println(localPort);
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
      if (len > 0) {
        packetBuffer[len] = 0;
      }
#ifdef DEBUG_VERBOS
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      Serial.print(ESP_remoteIP);
      Serial.print(", port ");
      Serial.println(ESP_remotePORT);
#endif
      if ((String)(char*)packetBuffer != "UDP_START") {
        Serial.print("You should sent \'s\' to start udp connection instead of ");
        Serial.println((char*)packetBuffer);
        continue;
      }
      uint8_t UDP_connected_reply[] = "UDP Connected";
      Udp.beginPacket(ESP_remoteIP, ESP_remotePORT);
      Udp.write(UDP_connected_reply, 13);
      Udp.endPacket();
      Udp.beginPacket(ESP_remoteIP, ESP_remotePORT);
      
      Udp.write(WiFi.localIP()[0]);
      Udp.write(WiFi.localIP()[1]);
      Udp.write(WiFi.localIP()[2]);
      Udp.write(WiFi.localIP()[3]);
      Udp.endPacket();
//      Udp.beginPacket(ESP_remoteIP, ESP_remotePORT);
//      
//      Udp.write(localPort/100);
//      Udp.write(localPort%100);
//      Udp.endPacket();
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
