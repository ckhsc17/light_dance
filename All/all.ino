#include <FastLED.h>
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi 設定
const char* ssid = "IMPR";
const char* password = "pierre2001";

// MQTT 伺服器設定
const char* mqtt_server = "172.20.10.10";  // 請確認MQTT伺服器IP
const char* mqtt_topic = "LED_TOPIC";

WiFiClient espClient;
PubSubClient client(espClient);

// 全局變量用於控制舞蹈
volatile bool danceRunning = false;
unsigned long nextBeatMillis = 0;