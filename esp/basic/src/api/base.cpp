#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "base.h"
#include "dht11.h"

#ifndef DHT11_PIN
#define DHT11_PIN GPIO_NUM_2
#endif

dht11 dht11Inst;

void handleRoot(AsyncWebServerRequest *request)
{
  request->send(200, "text/plain", "Hello!");
}

void handleMetadata(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  JsonObject metadata = root["metadata"].to<JsonObject>();
  metadata["name"] = "DHT11 温湿度传感器";
  metadata["description"] = "DHT11 温湿度传感器数据采集";
  metadata["version"] = 1;

  JsonArray entrypoints = root["entrypoints"].to<JsonArray>();
  JsonObject entrypoint = entrypoints.add<JsonObject>();
  entrypoint["path"] = "/data/json";
  entrypoint["description"] = "获取温湿度数据";
  entrypoint["method"] = "GET";
  entrypoint["type"] = "json";

  response->setLength();
  request->send(response);
}

void handleJsonData(AsyncWebServerRequest *request)
{
  dht11Inst.read(DHT11_PIN);
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  JsonObject data = root["data"].to<JsonObject>();
  data["temperature"] = dht11Inst.temperature;
  data["humidity"] = dht11Inst.humidity;

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