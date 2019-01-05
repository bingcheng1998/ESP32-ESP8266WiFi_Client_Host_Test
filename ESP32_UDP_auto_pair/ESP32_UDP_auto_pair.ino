#include "para_preset.h"

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
