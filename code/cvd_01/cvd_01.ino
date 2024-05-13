// cowbooys vs dinosaurs badge code rev01

// Include Libraries
#include <Arduino.h>
#include <WiFi.h>
#include "Adafruit_NeoPixel.h"
#include "SPI.h"

// Pin Definitions
//
// NeoPixel Data Pins
#define NEO01_DATA 17
#define NEO02_DATA 16
//
// One color LED Pins
#define LED_D1 14  // Green - Left Dino no hat
#define LED_D2 27  // Green - Right Dino hat
#define LED_D3 26  // Blue - Clubs 10
#define LED_D4 25  // Red - Hearts J
#define LED_D5 33  // Blue - Spades Q
#define LED_D6 32  // Red - Diamonds K

//
// Capacitive Touch Pins
#define TCH01_PIN 4
#define TCH02_PIN 2
#define TCH03_PIN 15
#define TCH04_PIN 13
#define TCH05_PIN 12

// NeoPixel Properties
//
// Define NeoPixel Strips - (Num pixels, pin to send signals, pixel type, signal rate)
Adafruit_NeoPixel NEO01 = Adafruit_NeoPixel(3, NEO01_DATA, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel NEO02 = Adafruit_NeoPixel(3, NEO02_DATA, NEO_RGB + NEO_KHZ800);
// Status NeoPixel LED color mode default=0 green=1 blue=2 red=3
int status_neo_mode = 0;

// PWM Properties
//
// Signal Frequency in Hz
const int freq = 1000;
// Duty Cycle Resolution in bits (1-16)
const int resolution = 8;
// PWM channel Assignment (0-15)
const int LED_D1_pwm = 1;
const int LED_D2_pwm = 2;
const int LED_D3_pwm = 3;
const int LED_D4_pwm = 4;
const int LED_D5_pwm = 5;
const int LED_D6_pwm = 6;

// Wireless Properties
//
// WIFI status codes
const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
  }
}

// Capacitive Touch Properties
//
// Touch Thresholds
int Touch01_Threshold = 19;
int Touch02_Threshold = 19;
int Touch03_Threshold = 19;
int Touch04_Threshold = 19;
int Touch05_Threshold = 19;
// Touch Initial Values
int Touch01_Value = 21;
int Touch02_Value = 21;
int Touch03_Value = 21;
int Touch04_Value = 21;
int Touch05_Value = 21;
//
// Touch Counters
//
// Touch Iteration Counter
int Touch01_IntCount = 0;
int Touch02_IntCount = 0;
int Touch03_IntCount = 0;
int Touch04_IntCount = 0;
int Touch05_IntCount = 0;
// Touch Loop Counter
int Touch01_LoopCount = 0;
int Touch02_LoopCount = 0;
int Touch03_LoopCount = 0;
int Touch04_LoopCount = 0;
int Touch05_LoopCount = 0;
// Touch Loop Threshold (Touch Held for X Loops of Main)
int Touch01_Loop_Threshold = 3;
int Touch02_Loop_Threshold = 3;
int Touch03_Loop_Threshold = 3;
int Touch04_Loop_Threshold = 3;
int Touch05_Loop_Threshold = 3;

// Loop Control Properties
//
// Main Loop LED Iteration Delay Time [in ms]
int LEDDelayTime = 20;
//
// Debug Serial - If set greater than 0 it writes to serial for debugging
// 0 = no debug text
// 1 = basic debug info once per main loop
// 2 = extra debug info
int DebugSerial = 2;

// //////////////////////////////////////////////////
//
// SETUP - RUN ONCE
//
// //////////////////////////////////////////////////
void setup(){
  // Add a delay to allow opening serial monitor
  delay(800);

  // setup the serial output baud rate
  Serial.begin(115200);

  if (DebugSerial >= 1) {
    Serial.println("Starting Setup");
  }

  // Turn Off WiFi/BT
  if (DebugSerial >= 2) {
    Serial.println("Turn Off WiFi / BlueTooth");
  }
  setModemSleep();

  // Configure LED PWM functionalitites per channel
  if (DebugSerial >= 2) {
    Serial.println("Configure PWM Channels");
  }
  ledcSetup(LED_D1_pwm, freq, resolution);
  ledcSetup(LED_D2_pwm, freq, resolution);
  ledcSetup(LED_D3_pwm, freq, resolution);
  ledcSetup(LED_D4_pwm, freq, resolution);
  ledcSetup(LED_D5_pwm, freq, resolution);
  ledcSetup(LED_D6_pwm, freq, resolution);

  // Attach the channel to the GPIO to be controlled
  if (DebugSerial >= 2) {
    Serial.println("Attach PWM Channels to LED Pins");
  }
  ledcAttachPin(LED_D1, LED_D1_pwm);
  ledcAttachPin(LED_D2, LED_D2_pwm);
  ledcAttachPin(LED_D3, LED_D3_pwm);
  ledcAttachPin(LED_D4, LED_D4_pwm);
  ledcAttachPin(LED_D5, LED_D5_pwm);
  ledcAttachPin(LED_D6, LED_D6_pwm);

  //Normal LED output
  if (DebugSerial >= 2) {
    Serial.println("Set Output for non-PWM LED Pins");
  }
  pinMode(LED_D2, OUTPUT);

  // Initialize the NeoPixels
  if (DebugSerial >= 2) {
    Serial.println("Initialize NeoPixels");
  }
  NEO01.begin();
  NEO02.begin(); 
  // Set Neopixel Brightness (0-255 scale)
  NEO01.setBrightness(170);
  NEO02.setBrightness(170);

  // Start all LEDs in OFF mode
  if (DebugSerial >= 2) {
    Serial.println("Turn OFF all LEDs");
  }
  ledAllOff();

  if (DebugSerial >= 1) {
    Serial.println(F("Setup Done!"));
  }

  // END OF SETUP
}

// //////////////////////////////////////////////////
//
// LOOP - MAIN 
//
// //////////////////////////////////////////////////
void loop(){
  if (DebugSerial >= 1) {
    Serial.println("******************** TOP OF MAIN LOOP ********************");
  }
  // Capacitive Touch Dynamic Threshold Adjustment
  // Adjust thresholds UP to account for assembly conditions and battery vs usb
  Touch01_Value = touchRead(TCH01_PIN);
  if ( (Touch01_Value / Touch01_Threshold) > 2 ) { Touch01_Threshold = int(Touch01_Threshold * 1.8); }
  Touch02_Value = touchRead(TCH02_PIN);
  if ( (Touch02_Value / Touch02_Threshold) > 2 ) { Touch02_Threshold = int(Touch02_Threshold * 1.8); }
  Touch03_Value = touchRead(TCH03_PIN);
  if ( (Touch03_Value / Touch03_Threshold) > 2 ) { Touch03_Threshold = int(Touch03_Threshold * 1.8); }
  Touch04_Value = touchRead(TCH04_PIN);
  if ( (Touch04_Value / Touch04_Threshold) > 2 ) { Touch04_Threshold = int(Touch04_Threshold * 1.8); }
  Touch05_Value = touchRead(TCH05_PIN);
  if ( (Touch05_Value / Touch05_Threshold) > 2 ) { Touch05_Threshold = int(Touch05_Threshold * 1.8); }

  // Iterate 0 to 254
  for(int i=0; i<255; i++){
    // Set position value to iteration value
    int pos = i;

    //
    // First of three position groups i 0-84
    if (pos < 85) {
      //
      // LED FUNCTIONS
      table_neo_colorshift(pos, 1);
      threeks_neo_colorshift(pos, 1);
      neo_show();
      ledPwmAlternate(pos, 1);
    // Second of three position groups i 85-169 (pos-85 = 0-84)
    } else if (pos < 170) {
      pos = pos - 85;
      //
      // LED FUNCTIONS
      table_neo_colorshift(pos, 2);
      threeks_neo_colorshift(pos, 2);
      neo_show();
      ledPwmAlternate(pos, 2);
    // Third of three position groups i 170-254 (pos-170 = 0-84)
    } else {
      pos = pos -170;
      //
      // LED FUNCTIONS
      table_neo_colorshift(pos, 3);
      threeks_neo_colorshift(pos, 3);
      neo_show();
      // Split third group 3/4 (pos 0-42) for even number of transitions
      if (pos <43) {
        //
        ledPwmAlternate(pos, 3);
      // Split third group 4/4 (pos 43-84) for even number of transitions
      } else {
        //
        ledPwmAlternate(pos, 4);
      }
    }

    // DEBUG - Print current Iteration value to serial console for troubleshooting
    if (DebugSerial >= 2) {
      Serial.print(" Iteration="); Serial.print(i);
      Serial.print(" Pos="); Serial.print(pos);
    }

    //
    // TOUCH
    //
    // Read Touch Values
    Touch01_Value = touchRead(TCH01_PIN);
    Touch02_Value = touchRead(TCH02_PIN);
    Touch03_Value = touchRead(TCH03_PIN);
    Touch04_Value = touchRead(TCH04_PIN);
    Touch05_Value = touchRead(TCH05_PIN);
    //
    // **************************************************************
    //
    // Do Stuff If We Detect a Touch on TCH01_PIN
    if (Touch01_Value < Touch01_Threshold) {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T01_TOUCH="); Serial.print(Touch01_Value);
        Serial.print("/"); Serial.print(Touch01_Threshold);
        Serial.print("-"); Serial.print(Touch01_IntCount);
        Serial.print("/"); Serial.print(Touch01_LoopCount);
      }
      // STUFF - TCH01_PIN TOUCHED
      if (Touch01_IntCount == 0){
        // Put stuff to happen once per iteration loop here
      }
      // Put stuff to happen every iteration here
      Touch01_IntCount = 1;
    //
    // Do Stuff If We DONT Detect a Touch on TCH01_PIN
    } else {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T01="); Serial.print(Touch01_Value);
        Serial.print("/"); Serial.print(Touch01_Threshold);
        Serial.print("-"); Serial.print(Touch01_IntCount);
        Serial.print("/"); Serial.print(Touch01_LoopCount);
      }
      // STUFF - TCH01_PIN NOT TOUCHED
    }
    //
    // **************************************************************
    //
    // Do Stuff If We Detect a Touch on TCH02_PIN
    if (Touch02_Value < Touch02_Threshold) {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T02_TOUCH="); Serial.print(Touch02_Value);
        Serial.print("/"); Serial.print(Touch02_Threshold);
        Serial.print("-"); Serial.print(Touch02_IntCount);
        Serial.print("/"); Serial.print(Touch02_LoopCount);
      }
      // STUFF - TCH02_PIN TOUCHED
      if (Touch02_IntCount == 0){
        // Put stuff to happen once per iteration loop here
      }
      // Put stuff to happen every iteration here
      Touch02_IntCount = 1;
    //
    // Do Stuff If We DONT Detect a Touch on TCH02_PIN
    } else {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T02="); Serial.print(Touch02_Value);
        Serial.print("/"); Serial.print(Touch02_Threshold);
        Serial.print("-"); Serial.print(Touch02_IntCount);
        Serial.print("/"); Serial.print(Touch02_LoopCount);
      }
      // STUFF - TCH02_PIN NOT TOUCHED
    }
    //
    // **************************************************************
    //
    // Do Stuff If We Detect a Touch on TCH03_PIN
    if (Touch03_Value < Touch03_Threshold) {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T03_TOUCH="); Serial.print(Touch03_Value);
        Serial.print("/"); Serial.print(Touch03_Threshold);
        Serial.print("-"); Serial.print(Touch03_IntCount);
        Serial.print("/"); Serial.print(Touch03_LoopCount);
      }
      // STUFF - TCH03_PIN TOUCHED
      if (Touch03_IntCount == 0){
        // Put stuff to happen once per iteration loop here
      }
      // Put stuff to happen every iteration here
      Touch03_IntCount = 1;
    //
    // Do Stuff If We DONT Detect a Touch on TCH03_PIN
    } else {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T03="); Serial.print(Touch03_Value);
        Serial.print("/"); Serial.print(Touch03_Threshold);
        Serial.print("-"); Serial.print(Touch03_IntCount);
        Serial.print("/"); Serial.print(Touch03_LoopCount);
      }
      // STUFF - TCH03_PIN NOT TOUCHED
    }
    //
    // **************************************************************
    //
    // Do Stuff If We Detect a Touch on TCH04_PIN
    if (Touch04_Value < Touch04_Threshold) {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T04_TOUCH="); Serial.print(Touch04_Value);
        Serial.print("/"); Serial.print(Touch04_Threshold);
        Serial.print("-"); Serial.print(Touch04_IntCount);
        Serial.print("/"); Serial.print(Touch04_LoopCount);
      }
      // STUFF - TCH04_PIN TOUCHED
      if (Touch04_IntCount == 0){
        // Put stuff to happen once per iteration loop here
      }
      // Put stuff to happen every iteration here
      Touch04_IntCount = 1;
    //
    // Do Stuff If We DONT Detect a Touch on TCH04_PIN
    } else {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T04="); Serial.print(Touch04_Value);
        Serial.print("/"); Serial.print(Touch04_Threshold);
        Serial.print("-"); Serial.print(Touch04_IntCount);
        Serial.print("/"); Serial.print(Touch04_LoopCount);
      }
      // STUFF - TCH04_PIN NOT TOUCHED
    }
    //
    // **************************************************************
    //
    // Do Stuff If We Detect a Touch on TCH05_PIN
    if (Touch05_Value < Touch05_Threshold) {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T05_TOUCH="); Serial.print(Touch05_Value);
        Serial.print("/"); Serial.print(Touch05_Threshold);
        Serial.print("-"); Serial.print(Touch05_IntCount);
        Serial.print("/"); Serial.print(Touch05_LoopCount);
      }
      // STUFF - TCH05_PIN TOUCHED
      if (Touch05_IntCount == 0){
        // Put stuff to happen once per iteration loop here
      }
      // Put stuff to happen every iteration here
      Touch05_IntCount = 1;
    //
    // Do Stuff If We DONT Detect a Touch on TCH05_PIN
    } else {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print(" T05="); Serial.print(Touch05_Value);
        Serial.print("/"); Serial.print(Touch05_Threshold);
        Serial.print("-"); Serial.print(Touch05_IntCount);
        Serial.print("/"); Serial.print(Touch05_LoopCount);
      }
      // STUFF - TCH05_PIN NOT TOUCHED
    }

    // DEBUG - Print status neopixel mode
    if (DebugSerial >= 2) {
      // Status NeoPixel LED color mode default=0 green=1 blue=2 red=3
      Serial.print(" Smode="); Serial.print(status_neo_mode);
    }

    // DEBUG - Print Carriage Return for iteration level debug output
    if (DebugSerial >= 2) {
      Serial.println();
    }

    // Pause the loop to display everything
    delay(LEDDelayTime);

    // END OF FOR ITERATION LOOP
  }

  // Touch Loop Counters - USE TBD
  if (Touch01_IntCount == 1) { Touch01_LoopCount++; Touch01_IntCount = 0; } else { Touch01_LoopCount = 0; }
  if (Touch02_IntCount == 1) { Touch02_LoopCount++; Touch02_IntCount = 0; } else { Touch02_LoopCount = 0; }
  if (Touch03_IntCount == 1) { Touch03_LoopCount++; Touch03_IntCount = 0; } else { Touch03_LoopCount = 0; }
  if (Touch04_IntCount == 1) { Touch04_LoopCount++; Touch04_IntCount = 0; } else { Touch04_LoopCount = 0; }
  if (Touch05_IntCount == 1) { Touch05_LoopCount++; Touch05_IntCount = 0; } else { Touch05_LoopCount = 0; }

  // Turn off all LEDs at end of loop (Optional)
  // ledAllOff();

  // END OF MAIN LOOP
}

// //////////////////////////////////////////////////
//
// FUNCTIONS
//
// //////////////////////////////////////////////////
//
// WiFi & BT Functions
// //////////////////////////////////////////////////
void disableWiFi(){
    WiFi.disconnect(true);  // Disconnect from the network
    WiFi.mode(WIFI_OFF);    // Switch WiFi off
    Serial.println("WiFi disabled!");
}
//
void disableBluetooth(){
    btStop();
    Serial.println("Bluetooth stopped!");
}
//
void setModemSleep() {
    disableWiFi();
    disableBluetooth();
    setCpuFrequencyMhz(80);
}
//
void enableWiFi(){
    delay(200);
    // Switch Wifi ON in mode AP/STA/AP_STA
    WiFi.mode(WIFI_AP); // Defaulting to AP mode
    delay(200);
    Serial.println("WiFi Started!");
}
//
void wakeModemSleep() {
    setCpuFrequencyMhz(240);
    enableWiFi();
}
// //////////////////////////////////////////////////
//
// LED Functions
// //////////////////////////////////////////////////
void ledAllOff() {
  ledcWrite(LED_D1_pwm, 0);
  ledcWrite(LED_D2_pwm, 0);
  ledcWrite(LED_D3_pwm, 0);
  ledcWrite(LED_D4_pwm, 0);
  ledcWrite(LED_D5_pwm, 0);
  ledcWrite(LED_D6_pwm, 0);
  NEO01.setPixelColor(0, 0, 0, 0);
  NEO01.setPixelColor(1, 0, 0, 0);
  NEO01.setPixelColor(2, 0, 0, 0);
  NEO01.show();
  NEO02.setPixelColor(0, 0, 0, 0);
  NEO02.setPixelColor(1, 0, 0, 0);
  NEO02.setPixelColor(2, 0, 0, 0);
  NEO02.show();
}
//
void ledPwmAlternate(uint8_t pos, uint8_t pass) {
  //
  // Alternate pulses between blue&red and the two green
  // blue full on = red full off and green1 on = green2 off
  //
  // D1 = Green - Left Dino no hat
  // D2 = Green - Right Dino hat
  // D3 = Blue - Clubs 10
  // D4 = Red - Hearts J
  // D5 = Blue - Spades Q
  // D6 = Red - Diamonds K
  //
  // Pass 1 pos 0-84
  // D1/3/5 ON->OFF
  // D2/4/6 OFF->ON
  if (pass == 1){
    ledcWrite(LED_D1_pwm, int(255 - (pos*3)));
    ledcWrite(LED_D3_pwm, int(255 - (pos*3)));
    ledcWrite(LED_D5_pwm, int(255 - (pos*3)));
    ledcWrite(LED_D2_pwm, int(pos*3));
    ledcWrite(LED_D4_pwm, int(pos*3));
    ledcWrite(LED_D6_pwm, int(pos*3));
  }
  // Pass 2 pos 0-84
  // D1/3/5 OFF->ON
  // D2/4/6 ON->OFF
  if (pass == 2){
    ledcWrite(LED_D1_pwm, int(pos*3));
    ledcWrite(LED_D3_pwm, int(pos*3));
    ledcWrite(LED_D5_pwm, int(pos*3));
    ledcWrite(LED_D2_pwm, int(255 - (pos*3)));
    ledcWrite(LED_D4_pwm, int(255 - (pos*3)));
    ledcWrite(LED_D6_pwm, int(255 - (pos*3)));
  }
  // Pass 3 pos 0-42
  // D1/3/5 ON->OFF
  // D2/4/6 OFF->ON
  if (pass == 3){
    ledcWrite(LED_D1_pwm, int(255 - ((pos-43)*6)));
    ledcWrite(LED_D3_pwm, int(255 - ((pos-43)*6)));
    ledcWrite(LED_D5_pwm, int(255 - ((pos-43)*6)));
    ledcWrite(LED_D2_pwm, int((pos-43)*6));
    ledcWrite(LED_D4_pwm, int((pos-43)*6));
    ledcWrite(LED_D6_pwm, int((pos-43)*6));
  }
  // Pass 4 pos 43-84
  // D1/3/5 OFF->ON
  // D2/4/6 ON->OFF
  if (pass == 4){
    ledcWrite(LED_D1_pwm, int((pos-43)*6));
    ledcWrite(LED_D3_pwm, int((pos-43)*6));
    ledcWrite(LED_D5_pwm, int((pos-43)*6));
    ledcWrite(LED_D2_pwm, int(255 - ((pos-43)*6)));
    ledcWrite(LED_D4_pwm, int(255 - ((pos-43)*6)));
    ledcWrite(LED_D6_pwm, int(255 - ((pos-43)*6)));
  }
}
//
void neo_show() {
  // Display neopixel colors set by other functions
  NEO01.show();
  NEO02.show();
}
//
void table_neo_colorshift(uint8_t pos, uint8_t pass) {
  // Pass 1 pos 0-84
  if (pass == 1){
    // Red 255-0 Green 0-255
    NEO01.setPixelColor(0, int(255 - (pos*3)), int(pos*3), 0);
    NEO02.setPixelColor(0, int(255 - (pos*3)), int(pos*3), 0);
    // Green 255-0 Blue 0-255
    NEO01.setPixelColor(1, 0, int(255 - (pos*3)), int(pos*3));
    NEO02.setPixelColor(1, 0, int(255 - (pos*3)), int(pos*3));
    // Blue 255-0 Red 0-255
    NEO01.setPixelColor(2, int(pos*3), 0, int(255 - pos*3));
  }
  // Pass 2 pos 0-84
  if (pass == 2){
    // Red 255-0 Green 0-255
    NEO01.setPixelColor(2, int(255 - (pos*3)), int(pos*3), 0);
    // Green 255-0 Blue 0-255
    NEO01.setPixelColor(0, 0, int(255 - (pos*3)), int(pos*3));
    NEO02.setPixelColor(0, 0, int(255 - (pos*3)), int(pos*3));
    // Blue 255-0 Red 0-255
    NEO01.setPixelColor(1, int(pos*3), 0, int(255 - pos*3));
    NEO02.setPixelColor(1, int(pos*3), 0, int(255 - pos*3));
  }
  // Pass 3 pos 0-84
  if (pass == 3){
    // Red 255-0 Green 0-255
    NEO01.setPixelColor(1, int(255 - (pos*3)), int(pos*3), 0);
    NEO02.setPixelColor(1, int(255 - (pos*3)), int(pos*3), 0);
    // Green 255-0 Blue 0-255
    NEO01.setPixelColor(2, 0, int(255 - (pos*3)), int(pos*3));
    // Blue 255-0 Red 0-255
    NEO01.setPixelColor(0, int(pos*3), 0, int(255 - pos*3));
    NEO02.setPixelColor(0, int(pos*3), 0, int(255 - pos*3));
  }
}
//
void threeks_neo_colorshift(uint8_t pos, uint8_t pass) {
  // Pass 1 pos 0-84
  if (pass == 1){
    // Blue 255-0 Red 0-255
    NEO02.setPixelColor(2, int(pos*3), 0, int(255 - pos*3));
  }
  // Pass 2 pos 0-84
  if (pass == 2){
    // Red 255-0 Green 0-255
    NEO02.setPixelColor(2, int(255 - (pos*3)), int(pos*3), 0);
  }
  // Pass 3 pos 0-84
  if (pass == 3){
    // Green 255-0 Blue 0-255
    NEO02.setPixelColor(2, 0, int(255 - (pos*3)), int(pos*3));
  }
}
//
void threeks_neo_red() {
  NEO02.setPixelColor(2, 255, 0, 0);
}
//
void threeks_neo_green() {
  NEO02.setPixelColor(2, 0, 255, 0);
}
//
void threeks_neo_blue() {
  NEO02.setPixelColor(2, 0, 0, 255);
}
//

