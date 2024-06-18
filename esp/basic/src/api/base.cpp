#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "base.h"

const char *PARAM_MESSAGE = "message";

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

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}