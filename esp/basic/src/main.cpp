#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "router.h"
#include "secrets.h" // 参考 secrets_example.h

void connectToWiFi(const char *ssid, const char *password);

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);

  connectToWiFi(ssid, password);
  setupRoutes(server);

  server.begin();
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
  Serial.println(WiFi.localIP());
}