#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif ESP8266
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

#ifdef OLED
#include "screen.h"
#endif

#include <ESPAsyncWebServer.h>
#include "router.h"
#include "secrets.h" // 参考 secrets_example.h

void connectToWiFi(const char *ssid, const char *password);
void screenStatus();

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

IPAddress localIp;
AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);

#ifdef OLED
  setupScreen();
  setScreenMessage("Booting...");
#endif

  connectToWiFi(ssid, password);
  setupRoutes(server);
  server.begin();
  screenStatus();
}

void loop()
{
}

void connectToWiFi(const char *ssid, const char *password)
{
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  localIp = WiFi.localIP();
  Serial.println(localIp);
}

void screenStatus()
{
#ifdef OLED
  if (WiFi.status() == WL_CONNECTED)
  {
    setScreenMessage(localIp.toString());
  }
  else
  {
    setScreenMessage("disconnected");
  }
#endif
}
