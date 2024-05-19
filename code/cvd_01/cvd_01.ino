// cowbooys vs dinosaurs badge code rev01

// Include Libraries
#include <Arduino.h>
#include <WiFi.h>
#include "Adafruit_NeoPixel.h"
#include "SPI.h"
#include <driver/adc.h>

// Pin Definitions
//
// NeoPixel Data Pins
#define NEO01_DATA 17
#define NEO02_DATA 16
//
// One color LED Pins
#define LED_D1 33  // White - Left Dino no hat
#define LED_D2 32  // White - Right Dino hat
#define LED_D3 14  // Blue - Clubs 10
#define LED_D4 27  // Red - Hearts J
#define LED_D5 26  // Blue - Spades Q
#define LED_D6 25  // Red - Diamonds K
//
// Built-in LED
#define LED_BI 22

//
// Capacitive Touch Pins
#define TCH01_PIN 4  // Dinosaurs
#define TCH02_PIN 2  // Logo
#define TCH03_PIN 15 // 3000
#define TCH04_PIN 13 // Society
#define TCH05_PIN 12 // Cowboys

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
int LEDDelayTime = 15;
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
  pinMode(LED_BI, OUTPUT);

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

  // //////////////////////////////////
  //     START OF ITERATION LOOP
  // //////////////////////////////////
  //
  // Iterate 0 to 254
  for(int i=0; i<255; i++){
    // Set position value to iteration value
    int pos = i;

    // DEBUG - Print current Iteration value to serial console for troubleshooting
    if (DebugSerial >= 2) {
      Serial.print(" Iteration="); Serial.print(i);
      Serial.print(" Pos="); Serial.print(pos);
    }

    //
    // TOUCH
    //
    // Read Touch Values
    Touch01_Value = touchRead(TCH01_PIN); // Dinosaurs
    Touch02_Value = touchRead(TCH02_PIN); // Logo
    Touch03_Value = touchRead(TCH03_PIN); // 3000
    Touch04_Value = touchRead(TCH04_PIN); // Society
    Touch05_Value = touchRead(TCH05_PIN); // Cowboys
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
      touchedDinosaurs();
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
      touchedCowboys();
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

    //
    // DEFAULT MODE
    //
    // First of three position groups i 0-84
    if (pos < 85) {
      //
      // LED FUNCTIONS
      table_neo_colorshift(pos, 1);
      threeks_neo_colorshift(pos, 1);
      ledPwmAlternate(pos, 1);
      BI_blink_two(pos);
    // Second of three position groups i 85-169 (pos-85 = 0-84)
    } else if (pos < 170) {
      pos = pos - 85;
      //
      // LED FUNCTIONS
      table_neo_colorshift(pos, 2);
      threeks_neo_colorshift(pos, 2);
      ledPwmAlternate(pos, 2);
      BI_blink_two(pos);
    // Third of three position groups i 170-254 (pos-170 = 0-84)
    } else {
      pos = pos -170;
      //
      // LED FUNCTIONS
      table_neo_colorshift(pos, 3);
      threeks_neo_colorshift(pos, 3);
      BI_blink_two(pos);
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

    // DEBUG - Print status neopixel mode
    if (DebugSerial >= 2) {
      // Status NeoPixel LED color mode default=0 green=1 blue=2 red=3
      Serial.print(" Smode="); Serial.print(status_neo_mode);
    }

    // DEBUG - Print Carriage Return for iteration level debug output
    if (DebugSerial >= 2) {
      Serial.println();
    }

    // Display Neopixel values
    neo_show();

    // Pause the loop to display everything
    delay(LEDDelayTime);

    // END OF FOR ITERATION LOOP
  }
  // //////////////////////////////////
  //     END OF ITERATION LOOP
  // //////////////////////////////////

  // Touch Loop Counters - USE TBD
  if (Touch01_IntCount == 1) { Touch01_LoopCount++; Touch01_IntCount = 0; } else { Touch01_LoopCount = 0; }
  if (Touch02_IntCount == 1) { Touch02_LoopCount++; Touch02_IntCount = 0; } else { Touch02_LoopCount = 0; }
  if (Touch03_IntCount == 1) { Touch03_LoopCount++; Touch03_IntCount = 0; } else { Touch03_LoopCount = 0; }
  if (Touch04_IntCount == 1) { Touch04_LoopCount++; Touch04_IntCount = 0; } else { Touch04_LoopCount = 0; }
  if (Touch05_IntCount == 1) { Touch05_LoopCount++; Touch05_IntCount = 0; } else { Touch05_LoopCount = 0; }

  // Turn off all LEDs at end of loop (Optional)
  // ledAllOff();

  // //////////////////////////////////////////////////
  //
  // Launch REACTION TIME GAME Alternate Mainline Code When
  // Touch01_LoopCount exceeds Touch01_Loop_Threshold
  //
  // //////////////////////////////////////////////////
  if (Touch01_LoopCount > Touch01_Loop_Threshold) {
    //
    Serial.println("LONG TOUCH DETECTED on TCH01 - JUMP TO ALTERNATE CODE");
    //
    ledAllOff();
    //
    Touch01_LoopCount = 0;
    //
    // Alternate code loop
    reaction_time_game();
    //
    // END ALTERNATE MAIN LOOP
    Serial.println("****************************************");
    Serial.println("****** EXITING REACTION TIME GAME ******");
    Serial.println("****************************************");
    //
    ledAllOff();
    //
    Touch01_LoopCount = 0;
    //
    status_neo_mode = 0;
    // Pause before exiting
    delay(100);
  }

  // //////////////////////////////////////////////////
  //
  // Launch BATT_CHRG_NOLED Alternate Mainline Code When
  // Touch02_LoopCount exceeds Touch02_Loop_Threshold
  //
  // //////////////////////////////////////////////////
  if (Touch02_LoopCount > Touch02_Loop_Threshold) {
    //
    Serial.println("LONG TOUCH DETECTED on TCH02 - JUMP TO ALTERNATE CODE");
    //
    ledAllOff();
    //
    Touch02_LoopCount = 0;
    //
    // Alternate code loop
    batt_chrg_noled();
    //
    // END ALTERNATE MAIN LOOP
    Serial.println("****************************************");
    Serial.println("***** EXITING BATT_CHRG_NOLED MODE *****");
    Serial.println("****************************************");
    //
    ledAllOff();
    //
    Touch02_LoopCount = 0;
    //
    status_neo_mode = 0;
    // Pause before exiting
    delay(100);
  }

  // //////////////////////////////////////////////////
  //
  // Launch FLUSH CARD GAME Alternate Mainline Code When
  // Touch05_LoopCount exceeds Touch05_Loop_Threshold
  //
  // //////////////////////////////////////////////////
  if (Touch05_LoopCount > Touch05_Loop_Threshold) {
    //
    Serial.println("LONG TOUCH DETECTED on TCH05 - JUMP TO ALTERNATE CODE");
    //
    ledAllOff();
    //
    Touch05_LoopCount = 0;
    //
    // Alternate code loop
    flush_card_game();
    //
    // END ALTERNATE MAIN LOOP
    Serial.println("****************************************");
    Serial.println("***** EXITING FLUSH CARD GAME MODE *****");
    Serial.println("****************************************");
    //
    ledAllOff();
    //
    Touch05_LoopCount = 0;
    //
    status_neo_mode = 0;
    // Pause before exiting
    delay(100);
  }

}
// //////////////////////////////////
//        END OF MAIN LOOP
// //////////////////////////////////


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
  digitalWrite(LED_BI, HIGH); // HIGH = OFF?
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
void ledPwmAllOn() {
    ledcWrite(LED_D1_pwm, 255);
    ledcWrite(LED_D3_pwm, 255);
    ledcWrite(LED_D5_pwm, 255);
    ledcWrite(LED_D2_pwm, 255);
    ledcWrite(LED_D4_pwm, 255);
    ledcWrite(LED_D6_pwm, 255);
}
//
void ledPwmAllOff() {
    ledcWrite(LED_D1_pwm, 0);
    ledcWrite(LED_D3_pwm, 0);
    ledcWrite(LED_D5_pwm, 0);
    ledcWrite(LED_D2_pwm, 0);
    ledcWrite(LED_D4_pwm, 0);
    ledcWrite(LED_D6_pwm, 0);
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
  // If T1 or T5 were pressed dont do anything here
  if (Touch01_IntCount > 0 || Touch05_IntCount > 0) { pass = 0; }
  //
  // lightlevel var used to set the pwm value
  uint8_t lightlevel = 0;
  //
  // Pass 1 pos 0-84
  // D2/3/5 ON->OFF
  // D1/4/6 OFF->ON
  if (pass == 1){
    if (pos <= 16) { lightlevel = 0; }
    else if (pos > 16 and pos <= 32) { lightlevel = 64; }
    else if (pos > 32 and pos <= 48) { lightlevel = 128; }
    else if (pos > 48 and pos <= 64) { lightlevel = 192; }
    else { lightlevel = 255; }
    ledcWrite(LED_D2_pwm, int(255 - lightlevel));
    ledcWrite(LED_D3_pwm, int(255 - lightlevel));
    ledcWrite(LED_D5_pwm, int(255 - lightlevel));
    ledcWrite(LED_D1_pwm, int(lightlevel));
    ledcWrite(LED_D4_pwm, int(lightlevel));
    ledcWrite(LED_D6_pwm, int(lightlevel));
  }
  // Pass 2 pos 0-84
  // D2/3/5 OFF->ON
  // D1/4/6 ON->OFF
  if (pass == 2){
    if (pos <= 16) { lightlevel = 0; }
    else if (pos > 16 and pos <= 32) { lightlevel = 64; }
    else if (pos > 32 and pos <= 48) { lightlevel = 128; }
    else if (pos > 48 and pos <= 64) { lightlevel = 192; }
    else { lightlevel = 255; }
    ledcWrite(LED_D2_pwm, int(lightlevel));
    ledcWrite(LED_D3_pwm, int(lightlevel));
    ledcWrite(LED_D5_pwm, int(lightlevel));
    ledcWrite(LED_D1_pwm, int(255 - lightlevel));
    ledcWrite(LED_D4_pwm, int(255 - lightlevel));
    ledcWrite(LED_D6_pwm, int(255 - lightlevel));
  }
  // Pass 3 pos 0-42
  // D3/5 ON->OFF
  // D4/6 OFF->ON
  // D1/2 ON
  if (pass == 3){
    if (pos <= 8) { lightlevel = 0; }
    else if (pos > 8 and pos <= 16) { lightlevel = 64; }
    else if (pos > 16 and pos <= 24) { lightlevel = 128; }
    else if (pos > 24 and pos <= 32) { lightlevel = 192; }
    else { lightlevel = 255; }
    ledcWrite(LED_D3_pwm, int(255 - lightlevel));
    ledcWrite(LED_D5_pwm, int(255 - lightlevel));
    ledcWrite(LED_D4_pwm, int(lightlevel));
    ledcWrite(LED_D6_pwm, int(lightlevel));
    ledcWrite(LED_D1_pwm, 255);
    ledcWrite(LED_D2_pwm, 255);
  }
  // Pass 4 pos 43-84
  // D3/5 OFF->ON
  // D4/6 ON->OFF
  // D1/2 ON
  if (pass == 4){
    if (pos <= 51) { lightlevel = 0; }
    else if (pos > 51 and pos <= 59) { lightlevel = 64; }
    else if (pos > 59 and pos <= 67) { lightlevel = 128; }
    else if (pos > 67 and pos <= 75) { lightlevel = 192; }
    else { lightlevel = 255; }
    ledcWrite(LED_D3_pwm, int(lightlevel));
    ledcWrite(LED_D5_pwm, int(lightlevel));
    ledcWrite(LED_D4_pwm, int(255 - lightlevel));
    ledcWrite(LED_D6_pwm, int(255 - lightlevel));
    ledcWrite(LED_D1_pwm, 255);
    ledcWrite(LED_D2_pwm, 255);
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
  // If T1 or T5 were pressed dont do anything here
  if (Touch01_IntCount > 0 || Touch05_IntCount > 0) { pass = 0; }
  //
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
void status_indicator(uint8_t status) {
  // Status NeoPixel LED color mode default=0 green=1 blue=2 red=3
  if (status == 1){
    NEO02.setPixelColor(2, 0, 255, 0);
  }
  if (status == 2){
    NEO02.setPixelColor(2, 0, 0, 255);
  }
  if (status == 3){
    NEO02.setPixelColor(2, 255, 0, 0);
  }
}
//
void touchedCowboys() {
    // Light Cowboys and 3KS logo but nothing else
    ledcWrite(LED_D1_pwm, 0);
    ledcWrite(LED_D2_pwm, 0);
    ledcWrite(LED_D3_pwm, 0);
    ledcWrite(LED_D4_pwm, 0);
    ledcWrite(LED_D5_pwm, 0);
    ledcWrite(LED_D6_pwm, 0);
    NEO01.setPixelColor(0, 0, 0, 255);
    NEO01.setPixelColor(1, 0, 0, 0);
    NEO01.setPixelColor(2, 0, 0, 255);
    NEO02.setPixelColor(0, 0, 0, 0);
    NEO02.setPixelColor(1, 0, 0, 0);
    NEO02.setPixelColor(2, 255, 255, 255);
}
//
void touchedDinosaurs() {
    // Light Dinos and 3KS logo but nothing else
    ledcWrite(LED_D1_pwm, 255);
    ledcWrite(LED_D2_pwm, 255);
    ledcWrite(LED_D3_pwm, 0);
    ledcWrite(LED_D4_pwm, 0);
    ledcWrite(LED_D5_pwm, 0);
    ledcWrite(LED_D6_pwm, 0);
    NEO01.setPixelColor(0, 0, 0, 0);
    NEO01.setPixelColor(1, 0, 0, 0);
    NEO01.setPixelColor(2, 0, 0, 0);
    NEO02.setPixelColor(0, 0, 0, 0);
    NEO02.setPixelColor(1, 0, 0, 0);
    NEO02.setPixelColor(2, 255, 255, 255);
}
//
void BI_on() {
  digitalWrite(LED_BI, LOW); // LOW = ON?
}
//
void BI_off() {
  digitalWrite(LED_BI, HIGH); // HIGH = OFF?
}
//
void BI_blink_one(uint8_t pos) {
  if (pos <= 21) {
    digitalWrite(LED_BI, LOW); // LOW = ON?
  } else {
    digitalWrite(LED_BI, HIGH); // HIGH = OFF?
  }
}
//
void BI_blink_two(uint8_t pos) {
  if (pos <= 11) {
    digitalWrite(LED_BI, LOW); // LOW = ON?
  } else if (pos > 11 and pos <= 22) {
    digitalWrite(LED_BI, HIGH); // HIGH = OFF?
  } else if (pos > 22 and pos <= 33) {
    digitalWrite(LED_BI, LOW); // LOW = ON?
  } else {
    digitalWrite(LED_BI, HIGH); // HIGH = OFF?
  }
}
//
void reaction_time_game() {
  // Set status to 1/green
  status_neo_mode = 1;
  status_indicator(status_neo_mode);
  neo_show();
  //
  // Set an exit var
  bool reaction_time_active = true;
  //
  // Set delay values
  int delaybase = 100;
  int delaytime = delaybase + 0;
  //
  while (reaction_time_active) {
    // Print Serial Message About Mode
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("******* REACTION TIME GAME MODE ********");
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("*** ACTIVATED BY LONG TOUCH ON TCH01 ***");
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("** LONG PRESS AGAIN TO EXIT THIS MODE **");
    Serial.println("****************************************");
    Serial.println("****************************************");
    // All OFF
    ledcWrite(LED_D3_pwm, 0);
    ledcWrite(LED_D4_pwm, 0);
    ledcWrite(LED_D5_pwm, 0);
    ledcWrite(LED_D6_pwm, 0);
    // Pause
    delay(10);
    // Loop 0-8 - none/1/2/3/4/3/2/1/none
    for(int r=0; r<9; r++){
      if (r == 1) { ledcWrite(LED_D3_pwm, 255); delaytime = delaybase + 50;}
      if (r == 2) { ledcWrite(LED_D4_pwm, 255); delaytime = delaybase + 25;}
      if (r == 3) { ledcWrite(LED_D5_pwm, 255); delaytime = delaybase;}
      if (r == 4) { ledcWrite(LED_D6_pwm, 255); delaytime = delaybase - 50;}
      if (r == 5) { ledcWrite(LED_D6_pwm, 0); delaytime = delaybase;}
      if (r == 6) { ledcWrite(LED_D5_pwm, 0); delaytime = delaybase + 25;}
      if (r == 7) { ledcWrite(LED_D4_pwm, 0); delaytime = delaybase + 50;}
      if (r == 8) { ledcWrite(LED_D3_pwm, 0); delaytime = delaybase + 75;}
      // DEBUG - Print current iteration and delaytime to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print("R="); Serial.print(r);
        Serial.print(" Delaytime="); Serial.println(delaytime);
      }
      //
      // Touch
      //
      Touch01_Value = touchRead(TCH01_PIN);
      // Do Stuff If We Detect a Touch on TCH01_PIN
      if (Touch01_Value < Touch01_Threshold) {
        // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
        if (DebugSerial >= 2) {
          Serial.print("TCH01_TOUCHED="); Serial.print(Touch01_Value);
          Serial.print("/"); Serial.print(Touch01_Threshold);
          Serial.print("-"); Serial.println(Touch01_LoopCount);
        }
        // STUFF - TCH01_PIN TOUCHED
        Touch01_LoopCount++;
        delay(1000);
        break;
      //
      // Do Stuff If We DONT Detect a Touch on TCH01_PIN
      } else {
        // STUFF - TCH01_PIN NOT TOUCHED
        Touch01_LoopCount = 0;
      }
      // Delay
      delay(delaytime);
    }
    // break out if touch loop threshold met
    if (Touch01_LoopCount > Touch01_Loop_Threshold) {
      reaction_time_active = false;
    }
  }
}
//
void batt_chrg_noled() {
  // Set an exit var
  bool batt_chrg_noled_active = true;
  //
  while (batt_chrg_noled_active) {
    BI_off();
    // Print Serial Message About Mode
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("********* BATT_CHRG_NOLED MODE *********");
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("*** ACTIVATED BY LONG TOUCH ON TCH02 ***");
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("** LONG PRESS AGAIN TO EXIT THIS MODE **");
    Serial.println("****************************************");
    Serial.println("****************************************");
    // Pause
    delay(3500);
    // Turn on-board LED on briefly to show badge is still on
    BI_on();
    // Pause
    delay(500);
    //
    // Touch for exit mode settings
    //
    Touch02_Value = touchRead(TCH02_PIN);
    // Do Stuff If We Detect a Touch on TCH02_PIN
    if (Touch02_Value < Touch02_Threshold) {
      // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print("TCH02_TOUCHED="); Serial.print(Touch02_Value);
        Serial.print("/"); Serial.print(Touch02_Threshold);
        Serial.print("-"); Serial.println(Touch02_LoopCount);
      }
      // STUFF - TCH02_PIN TOUCHED
      Touch02_LoopCount++;
    //
    // Do Stuff If We DONT Detect a Touch on TCH02_PIN
    } else {
      // STUFF - TCH02_PIN NOT TOUCHED
      Touch02_LoopCount = 0;
    }
    if (Touch02_LoopCount > Touch02_Loop_Threshold) {
      batt_chrg_noled_active = false;
    }
  }
}
//
void flush_card_game() {
  // Set status to 2/blue
  status_neo_mode = 2;
  status_indicator(status_neo_mode);
  neo_show();
  //
  // Set an exit var
  bool flush_card_active = true;
  //
  // Set delay value
  int delaytime = 250;
  //
  // Set Card Random variables
  int card_rand_1 = 0;
  int card_rand_2 = 0;
  int card_rand_3 = 0;
  int card_rand_4 = 0;
  int card_rand_5 = 0;
  //
  // Set Card Color Values
  int card_red[] = { 255, 0, 0, 255, 255, 0, 0, 255 };
  int card_green[] = { 0, 255, 0, 0, 0, 255, 0, 0 };
  int card_blue[] = { 0, 0, 255, 255, 0, 0, 255, 255 };
  //
  // Analog Read Settings for Random Source
  //adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_0);
  adc1_config_channel_atten(ADC1_CHANNEL_3,ADC_ATTEN_DB_0);
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_0);
  adc1_config_channel_atten(ADC1_CHANNEL_7,ADC_ATTEN_DB_0);
  int cardseed = 0;
  //
  // Set Flush Detector
  bool flush_win = false;
  //
  while (flush_card_active) {
    // Print Serial Message About Mode
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("******** FLUSH CARD GAME MODE **********");
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("*** ACTIVATED BY LONG TOUCH ON TCH05 ***");
    Serial.println("****************************************");
    Serial.println("****************************************");
    Serial.println("** LONG PRESS AGAIN TO EXIT THIS MODE **");
    Serial.println("****************************************");
    Serial.println("****************************************");
    //
    // Set a color to circle with based on a previous random color
    int circle_rand = card_rand_1;
    for(int f=1; f<6; f++){
      if (f == 1) {
        //
        NEO01.setPixelColor(0, card_red[circle_rand], card_green[circle_rand], card_blue[circle_rand]);
        NEO01.setPixelColor(1, 0, 0, 0);
        NEO01.setPixelColor(2, 0, 0, 0);
        NEO02.setPixelColor(1, 0, 0, 0);
        NEO02.setPixelColor(0, 0, 0, 0);
      } else if (f == 2) {
        NEO01.setPixelColor(0, 0, 0, 0);
        NEO01.setPixelColor(1, card_red[circle_rand], card_green[circle_rand], card_blue[circle_rand]);
        NEO01.setPixelColor(2, 0, 0, 0);
        NEO02.setPixelColor(1, 0, 0, 0);
        NEO02.setPixelColor(0, 0, 0, 0);
      } else if (f == 3) {
        NEO01.setPixelColor(0, 0, 0, 0);
        NEO01.setPixelColor(1, 0, 0, 0);
        NEO01.setPixelColor(2, card_red[circle_rand], card_green[circle_rand], card_blue[circle_rand]);
        NEO02.setPixelColor(1, 0, 0, 0);
        NEO02.setPixelColor(0, 0, 0, 0);
      } else if (f == 4) {
        NEO01.setPixelColor(0, 0, 0, 0);
        NEO01.setPixelColor(1, 0, 0, 0);
        NEO01.setPixelColor(2, 0, 0, 0);
        NEO02.setPixelColor(1, card_red[circle_rand], card_green[circle_rand], card_blue[circle_rand]);
        NEO02.setPixelColor(0, 0, 0, 0);
      } else if (f == 5) {
        NEO01.setPixelColor(0, 0, 0, 0);
        NEO01.setPixelColor(1, 0, 0, 0);
        NEO01.setPixelColor(2, 0, 0, 0);
        NEO02.setPixelColor(1, 0, 0, 0);
        NEO02.setPixelColor(0, card_red[circle_rand], card_green[circle_rand], card_blue[circle_rand]);
      }
      //
      // Show Neopixels
      neo_show();
      //
      // Get Random Card Values
      if (DebugSerial >= 2) { Serial.print("F="); Serial.print(f); }
      int seedsrc1 = adc1_get_raw(ADC1_CHANNEL_0);
      int seedsrc2 = analogRead(0);
      int seedsrc3 = touchRead(TCH03_PIN);
      int seedsrc4 = touchRead(TCH04_PIN);
      int seedsrc5 = adc1_get_raw(ADC1_CHANNEL_7);
      int seedsrc6 = adc1_get_raw(ADC1_CHANNEL_3);
      int seedsrc7 = adc1_get_raw(ADC1_CHANNEL_6);
      if (DebugSerial >= 2) {
        Serial.print(" source="); Serial.print(seedsrc1);
        Serial.print(" "); Serial.print(seedsrc2);
        Serial.print(" "); Serial.print(seedsrc3);
        Serial.print(" "); Serial.print(seedsrc4);
        Serial.print(" "); Serial.print(seedsrc5);
        Serial.print(" "); Serial.print(seedsrc6);
        Serial.print(" "); Serial.print(seedsrc7);
      }
      if (card_rand_1 < 3) {
        cardseed = (seedsrc1 + seedsrc2 + seedsrc3 + seedsrc4 + seedsrc5 + seedsrc6 + seedsrc7);
        randomSeed(cardseed);
      }
      card_rand_1 = random(0, 7);
      if (DebugSerial >= 2) { Serial.print(" card1="); Serial.print(card_rand_1); Serial.print("/"); Serial.print(cardseed); }
      if (card_rand_2 < 3) {
        cardseed = (seedsrc1 + seedsrc2 + seedsrc3 + seedsrc4 + seedsrc5 + seedsrc6 + seedsrc7);
        randomSeed(cardseed);
      }
      card_rand_2 = random(0, 7);
      if (DebugSerial >= 2) { Serial.print(" card2="); Serial.print(card_rand_2); Serial.print("/"); Serial.print(cardseed); }
      if (card_rand_3 < 3) {
        cardseed = (seedsrc1 + seedsrc2 + seedsrc3 + seedsrc4 + seedsrc5 + seedsrc6 + seedsrc7);
        randomSeed(cardseed);
      }
      card_rand_3 = random(0, 7);
      if (DebugSerial >= 2) { Serial.print(" card3="); Serial.print(card_rand_3); Serial.print("/"); Serial.print(cardseed); }
      if (card_rand_4 < 3) {
        cardseed = (seedsrc1 + seedsrc2 + seedsrc3 + seedsrc4 + seedsrc5 + seedsrc6 + seedsrc7);
        randomSeed(cardseed);
      }
      card_rand_4 = random(0, 7);
      if (DebugSerial >= 2) { Serial.print(" card4="); Serial.print(card_rand_4); Serial.print("/"); Serial.print(cardseed); }
      if (card_rand_5 < 3) {
        cardseed = (seedsrc1 + seedsrc2 + seedsrc3 + seedsrc4 + seedsrc5 + seedsrc6 + seedsrc7);
        randomSeed(cardseed);
      }
      card_rand_5 = random(0, 7);
      if (DebugSerial >= 2) { Serial.print(" card5="); Serial.print(card_rand_5); Serial.print("/"); Serial.println(cardseed); }
      //
      // Touch
      //
      Touch05_Value = touchRead(TCH05_PIN);
      // Do Stuff If We Detect a Touch on TCH05_PIN
      if (Touch05_Value < Touch05_Threshold) {
        // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
        if (DebugSerial >= 2) {
          Serial.print("TCH05_TOUCHED="); Serial.print(Touch05_Value);
          Serial.print("/"); Serial.print(Touch05_Threshold);
          Serial.print("-"); Serial.print(Touch05_LoopCount);
          String comma=",";
          Serial.print(" C1 "); Serial.print(card_rand_1 + comma + card_red[card_rand_1] + comma + card_green[card_rand_1] + comma + card_blue[card_rand_1]);
          Serial.print(" C2 "); Serial.print(card_rand_2 + comma + card_red[card_rand_2] + comma + card_green[card_rand_2] + comma + card_blue[card_rand_2]);
          Serial.print(" C3 "); Serial.print(card_rand_3 + comma + card_red[card_rand_3] + comma + card_green[card_rand_3] + comma + card_blue[card_rand_3]);
          Serial.print(" C4 "); Serial.print(card_rand_4 + comma + card_red[card_rand_4] + comma + card_green[card_rand_4] + comma + card_blue[card_rand_4]);
          Serial.print(" C5 "); Serial.print(card_rand_5 + comma + card_red[card_rand_5] + comma + card_green[card_rand_5] + comma + card_blue[card_rand_5]);
          Serial.println();
        }
        // STUFF - TCH05_PIN TOUCHED
        Touch05_LoopCount++;
        //
        // Set Flush Card Colors based on randoms
        NEO01.setPixelColor(0, card_red[card_rand_1], card_green[card_rand_1], card_blue[card_rand_1]);
        NEO01.setPixelColor(1, card_red[card_rand_2], card_green[card_rand_2], card_blue[card_rand_2]);
        NEO01.setPixelColor(2, card_red[card_rand_3], card_green[card_rand_3], card_blue[card_rand_3]);
        NEO02.setPixelColor(0, card_red[card_rand_4], card_green[card_rand_4], card_blue[card_rand_4]);
        NEO02.setPixelColor(1, card_red[card_rand_5], card_green[card_rand_5], card_blue[card_rand_5]);
        //
        // Show Neopixels
        neo_show();
        //
        // Check if we have a Flush
        if (card_rand_1 >= 4) { card_rand_1 = card_rand_1 - 4; }
        if (card_rand_2 >= 4) { card_rand_2 = card_rand_2 - 4; }
        if (card_rand_3 >= 4) { card_rand_3 = card_rand_3 - 4; }
        if (card_rand_4 >= 4) { card_rand_4 = card_rand_4 - 4; }
        if (card_rand_5 >= 4) { card_rand_5 = card_rand_5 - 4; }
        if (card_rand_1 == card_rand_2 && card_rand_2 == card_rand_3 && card_rand_3 == card_rand_4 && card_rand_4 == card_rand_5) {
          flush_win = true;
        }
        //
        delay(2000);
        break;
      //
      // Do Stuff If We DONT Detect a Touch on TCH05_PIN
      } else {
        // STUFF - TCH05_PIN NOT TOUCHED
        Touch05_LoopCount = 0;
      }
      // Delay
      delay(delaytime);
    }
    // break out if touch loop threshold met
    if (Touch05_LoopCount > Touch05_Loop_Threshold) {
      flush_card_active = false;
    }
    // Winner!
    while (flush_win) {
      // Don't update the lights any more, leave flush displayed but still check for touch
      //
      // DEBUG - Print card randoms to serial console for troubleshooting
      if (DebugSerial >= 2) {
        Serial.print("WINNER!!!");
        Serial.print(" card1="); Serial.print(card_rand_1);
        Serial.print(" card2="); Serial.print(card_rand_2);
        Serial.print(" card3="); Serial.print(card_rand_3);
        Serial.print(" card4="); Serial.print(card_rand_4);
        Serial.print(" card5="); Serial.println(card_rand_5);
      }
      Touch05_Value = touchRead(TCH05_PIN);
      if (Touch05_Value < Touch05_Threshold) {
        // DEBUG - Print current Touch value/threshold to serial console for troubleshooting
        if (DebugSerial >= 2) {
          Serial.print("TCH05_TOUCHED="); Serial.print(Touch05_Value);
          Serial.print("/"); Serial.print(Touch05_Threshold);
          Serial.print("-"); Serial.println(Touch05_LoopCount);
        }
        // STUFF - TCH05_PIN TOUCHED
        Touch05_LoopCount++;
      } else {
        // STUFF - TCH05_PIN NOT TOUCHED
        Touch05_LoopCount = 0;
      }
      // Delay
      delay(delaytime);
      // break out if touch loop threshold met
      if (Touch05_LoopCount > Touch05_Loop_Threshold) {
        flush_win = false;
      }
    }
  }
}
