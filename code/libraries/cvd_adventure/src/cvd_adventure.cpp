#include "cvd_adventure.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>

#include "webserverUtils.h"

// DEBUG SET HERE AND IN webserverUtils.h
//#define DEBUGLEVEL DEBUGLEVEL_ERRORS //For production
#define DEBUGLEVEL DEBUGLEVEL_DEBUGGING 
//#define DEBUGLEVEL DEBUGLEVEL_ERRORS
#include "debug.h"

// DNS Configuration
//
DNSServer dnsServer;

// WIFI Configurations
//
#define WIFI_AP_MODE true  // AP Mode required but setting false allows use of client mode
//
// Define AP ssid var
String ap_ssid;  // This gets set below to Cowboys-vs-Dinosaurs-<wifi_mac>
//
// Set AP password
const char* ap_password = "3000";
//
// Set Wifi Client mode ssid/password (to connect to)
const char* wifi_ssid     = "guest_network";     // change this for your own network
const char* wifi_password = "XXXXXXXXXXX";       // change this for your own network
//
// Set AP Static IP Addresses
IPAddress ap_Local_IP(192, 168, 1, 31);
IPAddress ap_Gateway_IP(192, 168, 1, 1);
IPAddress ap_Subnet(255, 255, 255, 0);

void cvdAdventureMain() {
  // Adventure Mainline

  // Print Serial Welcome Once
  Serial.println("****************************************");
  Serial.println("**** WELCOME TO THE ADVENTURE MODE *****");
  Serial.println("****************************************");
  Serial.println("*** ACTIVATED BY LONG TOUCH ON BADGE ***");
  Serial.println("****************************************");
  Serial.println("****************************************");
  Serial.println("**** POWER CYCLE TO EXIT THIS MODE *****");
  Serial.println("****************************************");

  // Set cvdAdventureActive - use this to allow for mode exit conditions
  bool cvdAdventureActive = true;

  /////////////////////////////////////
  // Configure Wifi
  //
  // Get MAC Address for AP ssid uniqueness
  byte wifi_mac[6]; 
  WiFi.macAddress(wifi_mac);
  //
  // Set AP ssid name using mac
  String ap_ssid = "Cowboys-vs-Dinosaurs-" + String(wifi_mac[3], HEX) + String(wifi_mac[4], HEX) + String(wifi_mac[5], HEX);
  //
  if (WIFI_AP_MODE) {
    // AP Mode
    Serial.println("Setting up AP Mode");
    Serial.println("*** AP MODE ***");
    //WiFi.mode(WIFI_AP);     // This is set by default in the main badge code
    WiFi.softAP(ap_ssid, ap_password);
    WiFi.softAPConfig(ap_Local_IP, ap_Gateway_IP, ap_Subnet);
    Serial.println();
    WiFi.softAPIP();
    IPAddress IP = WiFi.softAPIP();
    debuglnD("AP - ESP32 device IP address: " + IP.toString());
    debuglnD("Successfully Turned ON the device ESP32's Wifi-hotpspot...");
  } else {
    // Client Mode
    Serial.println("Setting up Client Mode");
    Serial.println("*** Client MODE ***");
    WiFi.mode(WIFI_STA);
    delay(500);
    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);
    Serial.println("*** WIFI CLIENT BEGIN ***");
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  debuglnD("\n\nNetwork Configuration:");
  debuglnD("----------------------");
  debugD("         SSID: "); debuglnD(WiFi.SSID());
  debugD("  Wifi Status: "); debuglnD(WiFi.status());
  debugD("Wifi Strength: "); debugD(WiFi.RSSI()); debuglnD(" dBm");
  debugD("          MAC: "); debuglnD(WiFi.macAddress());
  debugD("           IP: "); debuglnD(WiFi.localIP().toString());
  debugD("       Subnet: "); debuglnD(WiFi.subnetMask().toString());
  debugD("      Gateway: "); debuglnD(WiFi.gatewayIP().toString());
  debugD("        DNS 1: "); debuglnD(WiFi.dnsIP(0).toString());
  debugD("        DNS 2: "); debuglnD(WiFi.dnsIP(1).toString());
  debugD("        DNS 3: "); debuglnD(WiFi.dnsIP(2).toString());
  debuglnD();

  /////////////////////////////////////
  // Configure DNS
  debuglnD("Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());

  /////////////////////////////////////
  // Configure Web Servers
  debuglnD("Configuring Webservers ...");
  server80 = new AsyncWebServer(80);
  configureWebServer80();

  /////////////////////////////////////
  // Start Web Servers
  debuglnD("Starting Webservers ...");
  server80->begin();

  // Captive Portal Config
  // maybe later

  // Setup Complete
  Serial.println(".....: Setup complete :.....");

  // LOOP
  while (cvdAdventureActive) {
    delay(2000);
    Serial.println("****************************************");
    Serial.println("******** ADVENTURE MODE ACTIVE *********");
    Serial.println("***** POWER CYCLE TO EXIT THIS MODE *****");
    Serial.println("****************************************");
  }
}
