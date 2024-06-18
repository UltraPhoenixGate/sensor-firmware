#include "router.h"
#include "api/base.h"

void setupRoutes(AsyncWebServer &server)
{
  server.on("/", HTTP_GET, handleRoot);
  server.on("/data/json", HTTP_GET, handleJsonData);
  server.onNotFound(notFound);
}