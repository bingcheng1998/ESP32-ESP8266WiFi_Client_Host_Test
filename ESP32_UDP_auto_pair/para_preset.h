
#ifndef PARA_PRESET
#define PARA_PRESET


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



#endif //PARA_PRESET
