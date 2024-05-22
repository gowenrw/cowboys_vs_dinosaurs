#include "cvd_adventure.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <esp_wifi_types.h>
#include <esp_wifi.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>

#include "webserverUtils.h"

// DEBUG SET HERE AND IN webserverUtils.h
//#define DEBUGLEVEL DEBUGLEVEL_ERRORS //For production
#define DEBUGLEVEL DEBUGLEVEL_DEBUGGING 
//#define DEBUGLEVEL DEBUGLEVEL_ERRORS
#include "debug.h"

// Touch Definitions
#define CVDA_TCH04_PIN 13 // Society
int CVDA_Touch04_Threshold = 19;
int CVDA_Touch04_Value = 21;
int CVDA_Touch04_LoopCount = 0;
int CVDA_Touch04_Loop_Threshold = 6;

// DNS Configuration
//
DNSServer dnsServer;

// WIFI Configurations
//
#define WIFI_AP_MODE true  // AP Mode required but setting false allows use of client mode
//
// Define AP ssid var
String ap_ssid;  // This gets set below to CvD-badge-<wifi_mac>
//
// Set AP password
const char* ap_password = ""; // Open - No Pass
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
  String ap_ssid = "CvD-badge-" + String(wifi_mac[3], HEX) + String(wifi_mac[4], HEX) + String(wifi_mac[5], HEX);
  //
  if (WIFI_AP_MODE) {
    // AP Mode
    Serial.println("Setting up AP Mode");
    Serial.println("*** AP MODE ***");
    WiFi.mode(WIFI_AP);     // This is set by default in the main badge code
    delay(250);
    WiFi.softAP(ap_ssid, ap_password);
    WiFi.softAPConfig(ap_Local_IP, ap_Gateway_IP, ap_Subnet);
    delay(1500);
    Serial.println(".... ");
    WiFi.softAPIP();
    delay(1500);
    Serial.println("........ ");
    IPAddress IP = WiFi.softAPIP();
    debuglnD("AP - ESP32 SSID: " + ap_ssid);
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
  debugD("      AP SSID: "); debuglnD(ap_ssid);
  debugD("     STA SSID: "); debuglnD(WiFi.SSID());
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
  /* Setup the DNS server redirecting all the domains to the apIP */  
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", WiFi.softAPIP());

  /////////////////////////////////////
  // Configure Web Servers
  debuglnD("Configuring Webservers ...");
  server80 = new AsyncWebServer(80);
  server443 = new AsyncWebServer(443);
  configureWebServer80();
  configureWebServer443();

  /////////////////////////////////////
  // Start Web Servers
  debuglnD("Starting Webservers ...");
  server80->begin();
  server443->begin();

  // Setup Complete
  Serial.println(".....: Setup complete :.....");

  // LOOP
  while (cvdAdventureActive) {
    // DNS Loop to answer any requests with AP IP (Captive portal like behavior)
    for(int d=0; d<9; d++){
      // DNS Checks
      dnsServer.processNextRequest();
      delay(250);
    }
    // Capacitive Touch Dynamic Threshold Adjustment
    // Adjust thresholds UP to account for assembly conditions and battery vs usb
    CVDA_Touch04_Value = touchRead(CVDA_TCH04_PIN);
    if ( (CVDA_Touch04_Value / CVDA_Touch04_Threshold) > 2 ) { CVDA_Touch04_Threshold = int(CVDA_Touch04_Threshold * 1.8); }
    // Print Serial Message About Mode
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("****** ADVENTURE GAME MODE ACTIVE ******");
    Serial.println("****************************************");
    Serial.println("*** ACTIVATED BY LONG TOUCH ON TCH04 ***");
    Serial.println("***      THE SOCIETY TEXT BUTTON     ***");
    Serial.println("****************************************");
    Serial.println("** LONG PRESS AGAIN TO EXIT THIS MODE **");
    Serial.println("****************************************");
    Serial.println("****************************************");
    CVDA_Touch04_Value = touchRead(CVDA_TCH04_PIN);
    if (CVDA_Touch04_Value < CVDA_Touch04_Threshold) {
      Serial.print("TCH04_TOUCHED="); Serial.print(CVDA_Touch04_Value);
      Serial.print("/"); Serial.print(CVDA_Touch04_Threshold);
      Serial.print("-"); Serial.println(CVDA_Touch04_LoopCount);
      // STUFF - TCH04_PIN TOUCHED
      CVDA_Touch04_LoopCount++;
    } else {
      // STUFF - TCH04_PIN NOT TOUCHED
      CVDA_Touch04_LoopCount = 0;
    }
    // break out if touch loop threshold met
    if (CVDA_Touch04_LoopCount > CVDA_Touch04_Loop_Threshold) {
      cvdAdventureActive = false;
    }
  }
}
