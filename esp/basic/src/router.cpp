#include "router.h"
#include "api/base.h"

void setupRoutes(AsyncWebServer &server)
{
  server.on("/", HTTP_GET, handleRoot);
  server.on("/data/json", HTTP_GET, handleJsonData);
  server.on("/data/metrics", HTTP_GET, handleMetricsData);
  server.onNotFound(notFound);
}