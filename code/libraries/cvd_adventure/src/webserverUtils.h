#ifndef WEBSERVERUTILS_H
#define WEBSERVERUTILS_H

// DEBUG SET HERE AND IN cvd_adventure.cpp
//#define DEBUGLEVEL DEBUGLEVEL_ERRORS //For production
#define DEBUGLEVEL DEBUGLEVEL_DEBUGGING 
//#define DEBUGLEVEL DEBUGLEVEL_ERRORS
#include "debug.h"

#include <Arduino.h>
#include <WiFi.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>

#define FIRMWARE_VERSION "v0.0.2"
bool shouldReboot = false;            // schedule a reboot

AsyncWebServer *server80;               // initialise webserver
AsyncWebServer *server443;              // initialise webserver

//web config values
const String httpadminuser = "admin";
const String httpadminpassword = "admin";

// used by server.on functions to discern whether a user has the correct httpapitoken OR is authenticated by username and password
bool checkUserWebAuth(AsyncWebServerRequest * request, String usr, String pwd) {
  bool isAuthenticated = false;

  if (request->authenticate(usr.c_str(), pwd.c_str())) {
    Serial.println("is authenticated via username and password");
    isAuthenticated = true;
  }
  return isAuthenticated;
}

// Make size of files human readable
// source: https://github.com/CelliesProjects/minimalUploadAuthESP32
String humanReadableSize(const size_t bytes) {
  if (bytes < 1024) return String(bytes) + " B";
  else if (bytes < (1024 * 1024)) return String(bytes / 1024.0) + " KB";
  else if (bytes < (1024 * 1024 * 1024)) return String(bytes / 1024.0 / 1024.0) + " MB";
  else return String(bytes / 1024.0 / 1024.0 / 1024.0) + " GB";
}

// parses and processes webpages
// if the webpage has %SOMETHING% or %SOMETHINGELSE% it will replace those strings with the ones defined
String processor(const String& var) {
  if (var == "FIRMWARE") {
    return FIRMWARE_VERSION;
  }
}

const char notfound_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="refresh" content="1; URL=http://192.168.1.31/" />
</head>
<body>
REDIRECT PERMANENT
</body>
</html>
)rawliteral";

// Commented this out to have onNotFound redirect to index on the web servers instead
void notFound(AsyncWebServerRequest *request) {
  String logmessage = "Client:" + request->client()->remoteIP().toString() + ":" + request->client()->remotePort() + " " + request->url();
  Serial.println(logmessage);
  request->send_P(200, "text/html", notfound_html, processor);
}
// void notFound(AsyncWebServerRequest *request) {
//   String logmessage = "Client:" + request->client()->remoteIP().toString() + ":" + request->client()->remotePort() + " " + request->url();
//   Serial.println(logmessage);
//   request->send(404, "text/plain", "Not found");
// }

#include "webserver80.h"
#include "webserver443.h"

#endif