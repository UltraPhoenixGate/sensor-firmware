#ifndef API_BASE_H
#define API_BASE_H

#include <ESPAsyncWebServer.h>

extern const char *PARAM_MESSAGE;

void handleRoot(AsyncWebServerRequest *request);
void handleJsonData(AsyncWebServerRequest *request);
void notFound(AsyncWebServerRequest *request);

#endif // API_BASE_H