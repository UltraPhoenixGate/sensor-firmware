#include "router.h"
#include "api/base.h"

void setupRoutes(AsyncWebServer &server)
{
  server.on("/", HTTP_GET, handleRoot);
  server.on("/metadata", HTTP_GET, handleMetadata);
  server.on("/data/light", HTTP_GET, handleLightData);
  server.on("/data/soil", HTTP_GET, handleSoilData);
  server.onNotFound(notFound);
}