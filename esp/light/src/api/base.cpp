#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "base.h"

#ifndef LIGHT_PIN
#define LIGHT_PIN GPIO_NUM_0
#endif

#ifndef SOIL_PIN
#define SOIL_PIN A13
#endif

void handleRoot(AsyncWebServerRequest *request)
{
  request->send(200, "text/plain", "Hello!");
}

void handleMetadata(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  JsonObject metadata = root["metadata"].to<JsonObject>();
  metadata["name"] = "光照和土壤湿度传感器";
  metadata["description"] = "获取光照和土壤湿度数据";
  metadata["version"] = 1;

  JsonArray entrypoints = root["entrypoints"].to<JsonArray>();
  JsonObject entrypoint = entrypoints.add<JsonObject>();
  entrypoint["path"] = "/data/light";
  entrypoint["description"] = "获取光照数据";
  entrypoint["method"] = "GET";
  entrypoint["type"] = "json";

  JsonObject entrypoint2 = entrypoints.add<JsonObject>();
  entrypoint2["path"] = "/data/soil";
  entrypoint2["description"] = "获取土壤湿度数据";
  entrypoint2["method"] = "GET";
  entrypoint2["type"] = "json";

  response->setLength();
  request->send(response);
}

int lightValue = 0;

void handleLightData(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  JsonObject data = root["data"].to<JsonObject>();
  lightValue = digitalRead(LIGHT_PIN);
  data["light"] = lightValue;

  JsonObject labels = root["labels"].to<JsonObject>();

  response->setLength();
  request->send(response);
}

int soilValue = 0;
void handleSoilData(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  JsonObject data = root["data"].to<JsonObject>();
  soilValue = analogRead(SOIL_PIN);
  data["soil"] = soilValue;

  JsonObject labels = root["labels"].to<JsonObject>();

  response->setLength();
  request->send(response);
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}