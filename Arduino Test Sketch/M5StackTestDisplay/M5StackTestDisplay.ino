#include <M5Core2.h>
#include "SD.h"

void setup() {
  M5.begin();
  SD.begin();
  M5.Lcd.fillScreen(WHITE);
  delay(1000);
  M5.Lcd.drawJpgFile(SD, "/middle.jpg", 0, 0);
  delay(2000);
  M5.Lcd.fillScreen(WHITE);
  delay(1000);
  M5.Lcd.drawJpgFile(SD, "/high.jpg", 0, 0);
  delay(2000);
  M5.Lcd.fillScreen(WHITE);
  delay(1000);
  M5.Lcd.drawJpgFile(SD, "/low.jpg", 0, 0);
  delay(2000);
  M5.Lcd.fillScreen(WHITE);
  delay(1000);
}

void loop() {
  M5.update();
}
