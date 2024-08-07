#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "base.h"
#include "mq2.h"

void handleRoot(AsyncWebServerRequest *request)
{
  request->send(200, "text/plain", "Hello!");
}

void handleJsonData(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  JsonObject data = root["data"].to<JsonObject>();
  data["lpg"] = mq2.readLPG();
  data["co"] = mq2.readCO();
  data["smoke"] = mq2.readSmoke();

  JsonObject labels = root["labels"].to<JsonObject>();

  response->setLength();
  request->send(response);
}

void handleMetricsData(AsyncWebServerRequest *request)
{
  String metrics = "";
  metrics += "temperature 25.0\n";
  metrics += "humidity 50.0\n";
  // 设置响应头
  AsyncWebServerResponse *metricsResponse = request->beginResponse(200, "text/plain", metrics);
  request->send(metricsResponse);
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}