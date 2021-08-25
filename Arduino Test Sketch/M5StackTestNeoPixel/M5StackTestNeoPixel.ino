#include <Adafruit_NeoPixel.h>
#include <M5Core2.h>

#define PIN       25 // M5Stack NeoPixel Pin
#define NUMPIXELS 10 // M5 Neopixel Number

Adafruit_NeoPixel M5pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
  M5pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  M5.begin();
}

void loop() {
  M5pixels.clear(); // Set all pixel colors to 'off'
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
    // M5pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    M5pixels.setPixelColor(i, M5pixels.Color(0, 150, 0));
    M5pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
  }
}
