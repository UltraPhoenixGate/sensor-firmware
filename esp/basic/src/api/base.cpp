#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "base.h"

void handleRoot(AsyncWebServerRequest *request)
{
  request->send(200, "text/plain", "Hello!");
}

void handleJsonData(AsyncWebServerRequest *request)
{
  AsyncJsonResponse *response = new AsyncJsonResponse();
  JsonObject root = response->getRoot();

  JsonObject data = root["data"].to<JsonObject>();
  data["temperature"] = 25.0;
  data["humidity"] = 50.0;

  JsonObject labels = root["labels"].to<JsonObject>();
  labels["id"] = "a6p3tya59uqYBZ";
  labels["area"] = "区域A";

  response->setLength();
  request->send(response);
}

void handleMetricsData(AsyncWebServerRequest *request)
{
  String metrics = "";
  String labels = "id=\"a6p3tya59uqYBZ\",area=\"区域A\"";
  metrics += "temperature{" + labels + "} 25.0\n";
  metrics += "humidity{" + labels + "} 50.0\n";
  // 设置响应头
  AsyncWebServerResponse *metricsResponse = request->beginResponse(200, "text/plain", metrics);
  request->send(metricsResponse);
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}