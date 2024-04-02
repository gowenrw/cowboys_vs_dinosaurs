// blink_poc_02
//
// code to test the esp dev board
// blinks the onboard LED
// fade blink an external LED with PWM
// changes colors on an external Neopixel LED
//

// Include Libraries
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Pin Definitions
#define LED_BUILTIN 22
#define LED01 14
#define NEO01Pin 17

// PWM Properties
const int freq = 1000;
const int resolution = 8;
const int LED01pwm = 1;

// Define NeoPixel Strips - (Num pixels, pin to send signals, pixel type, signal rate)
Adafruit_NeoPixel NEO01 = Adafruit_NeoPixel(2, NEO01Pin, NEO_RGB + NEO_KHZ800);

// Debug Serial - If set greater than 0 it writes to serial for debugging
// 0 = no debug text
// 1 = basic debug info once per main loop
// 2 = extra debug info
int DebugSerial = 2;

// Main Loop LED Iteration Delay Time [in ms]
int LEDDelayTime = 50;

void ledAllOff() {
  digitalWrite(LED_BUILTIN, LOW);
  ledcWrite(LED01pwm, 0);
  NEO01.setPixelColor(0, 0, 0, 0);
  NEO01.show();
}

void setup() {
  // Add a delay to allow opening serial monitor
  delay(300);
  Serial.begin(115200);
  if (DebugSerial >= 1) {
    Serial.println("Starting Setup");
  }
  //
  // configure LED PWM functionalitites per channel
  ledcSetup(LED01pwm, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED01, LED01pwm);
  //
  //Normal LED output
  pinMode (LED_BUILTIN, OUTPUT);
  //
  // Initialize NeoPixels
  NEO01.begin();
  // Set Neopixel Brightness (0-255 scale)
  NEO01.setBrightness(150);
  //
  if (DebugSerial >= 1) {
    Serial.println(F("Setup Done!"));
  }
}

void loop(void) {
  if (DebugSerial >= 1) {
    Serial.println("Main Loop Start");
  }
  // Iterate 0 to 255
  for(int i=0; i<256; i++){
    // Set position value to iteration
    int pos = i;
    //
    // Group 1/4
    //
    if (pos < 64) {
      //
      // BUILTIN LED
      if (pos < 16) {
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
      }
      //
      // PWM LED
      // Start off and slowly get brighter to full on
      ledcWrite(LED01pwm, int(pos*4));
      //
      // NEOPIXEL LED
      // Blue then Green then Red
      if (pos < 22) {
        NEO01.setPixelColor(0, 0, 0, 255);
      } else if (pos < 44) {
        NEO01.setPixelColor(0, 0, 255, 0);
      } else {
        NEO01.setPixelColor(0, 255, 0, 0);
      }
    //
    // Group 2/4
    //
    } else if (pos < 128) {
      pos = pos - 64;
      //
      // BUILTIN LED
      if (pos < 16) {
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
      }
      //
      // PWM LED
      // Start on and slowly get dimmer to full off
      ledcWrite(LED01pwm, int(255 - (pos*4)));
      //
      // NEOPIXEL LED
      // Red 255-0 Green 0-255
      NEO01.setPixelColor(0, int(255 - (pos*4)), int(pos*4), 0);
    //
    // Group 3/4
    //
    } else if (pos < 192) {
      pos = pos - 128;
      //
      // BUILTIN LED
      if (pos < 16) {
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
      }
      //
      // PWM LED
      // Start off and slowly get brighter to full on
      ledcWrite(LED01pwm, int(pos*4));
      //
      // NEOPIXEL LED
      // Green 255-0 Blue 0-255
      NEO01.setPixelColor(0, 0, int(255 - (pos*4)), int(pos*4));
    //
    // Group 4/4
    //
    } else {
      pos = pos -192;
      //
      // BUILTIN LED
      if (pos < 16) {
        digitalWrite(LED_BUILTIN, HIGH);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
      }
      //
      // PWM LED
      // Start on and slowly get dimmer to full off
      ledcWrite(LED01pwm, int(255 - (pos*4)));
      //
      // NEOPIXEL LED
      // Blue 255-0 Red 0-255
      NEO01.setPixelColor(0, int(pos*4), 0, int(255 - pos*4));
    }
    // Set Neopixel to Show Value Set Above
    NEO01.show();
    // DEBUG - Print current Iteration value to serial console for troubleshooting
    if (DebugSerial == 2) {
      Serial.print("  Iteration="); Serial.print(i);
      Serial.print("  Position="); Serial.print(pos);
      Serial.print("  PosX4="); Serial.print(pos*4);
      Serial.println();
    }
    // Pause the loop to display LEDS
    delay(LEDDelayTime);
  }
  // Turn off all LEDs at end of loop
  ledAllOff();
  if (DebugSerial >= 1) {
    Serial.println(F("Main Loop End"));
  }

}