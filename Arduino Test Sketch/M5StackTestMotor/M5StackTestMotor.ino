#include <M5Core2.h>

void setup() {
  M5.begin();
  // put your setup code here, to run once:

}

void loop() {
  M5.Axp.SetLDOEnable(3,1);
  delay(1000);
  M5.Axp.SetLDOEnable(3,0);
  delay(5000);
  // put your main code here, to run repeatedly:
}
