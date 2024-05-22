#ifndef WEBSERVER443_H
#define WEBSERVER443_H

#include "webserverUtils.h"

#include <Arduino.h>
#include <WiFi.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>

#include "webpages443.h"
//#include "webcommon.h"

const String usr443 = "admin";
const String pwd443 = "adminsrule";

// configure web server
void configureWebServer443() {

  // if url isn't found
  server443->onNotFound(notFound);

  server443->on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();
    Serial.println(logmessage);
    request->send_P(200, "text/html", index_html443, processor);
  });

  server443->on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();
    Serial.println(logmessage);
    request->send_P(200, "text/html", index_html443, processor);
  });

}

#endif