/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <ArduinoJson.h>
#include "certs.h"
#include <WiFiClientSecure.h>
#include <MQTT.h>
#include <WiFi.h>
#include <M5Core2.h>

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  30        /* Time ESP32 will go to sleep (in seconds) */


#define ESP_getChipId() ((uint32_t)ESP.getEfuseMac())

// The name of the device. This MUST match up with the name defined in the AWS console
#define DEVICE_NAME "M5Core"

#define AWS_IOT_TOPIC "/BlueSpace/ESP32"

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);
DynamicJsonDocument doc(2048);

int scanTime = 5; //In seconds
BLEScan* pBLEScan;

String getAddress(String AD);
float dist(int rssi);

unsigned long inter;

int devices = 0;
float minDist = 2;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      doc[getAddress(advertisedDevice.toString().c_str())][0] = advertisedDevice.getRSSI();
      doc[getAddress(advertisedDevice.toString().c_str())][1] = dist(advertisedDevice.getRSSI());
      if (minDist >= dist(advertisedDevice.getRSSI())) {
        minDist = dist(advertisedDevice.getRSSI());
      }
    }
};

void setup() {
  Serial.begin(115200);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  devices = doc.size();
  M5.begin();
  SD.begin();
  if (minDist < 1) {
    M5.Lcd.drawJpgFile(SD, "/high.jpg", 0, 0);
    doc["res"]="high";
  }
  else if (minDist >= 1 && minDist < 2) {
    M5.Lcd.drawJpgFile(SD, "/middle.jpg", 0, 0);
    doc["res"]="middle";
  }
  else {
    M5.Lcd.drawJpgFile(SD, "/low.jpg", 0, 0);
    doc["res"]="low";
  }
  M5.Lcd.setCursor(146, 140); //Move the cursor position to (x,y).  移动光标位置到 (x,y)处
  M5.Lcd.setTextColor(BLACK); //Set the font color to white.  设置字体颜色为白色
  M5.Lcd.setTextSize(5);  //Set the font size.  设置字体大小
  M5.Lcd.println(doc.size());  //Serial output format string.  输出格式化字符串
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("     Devices");
  M5.Lcd.println("     Detected");
  delay(1000);
  WiFi.begin(ssid, password);
  connect();
  String output1 = "";
  serializeJson(doc, output1);
  client.publish(AWS_IOT_TOPIC, string2char(output1));
  inter = millis();
}

void loop() {
  client.loop();
  if ((millis() - inter) > 5000) {
    esp_deep_sleep_start();
  }
  if (!client.connected()) {
    inter = millis();
    connect();
  }
}

float dist(int rssi) {
  float value = -69 - rssi;
  value /= (10 * 2);
  value = pow(10, value);
  return value;
}

String getAddress(String AD) {
  int place = AD.indexOf("Address");
  return AD.substring(place + 9, place + 26);
}

char* string2char(String command) {
  if (command.length() != 0) {
    char *p = const_cast<char*>(command.c_str());
    return p;
  }
}

void connectToWiFi() {
  int conCounter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    conCounter++;
    if (conCounter == 10) {
      ESP.restart();
    }
  }
}

void connectToAWS()
{
  // Configure WiFiClientSecure to use the AWS certificates we generated
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Try to connect to AWS and count how many times we retried.

  while (!client.connect(DEVICE_NAME)) {
    delay(100);
  }

  // Make sure that we did indeed successfully connect to the MQTT broker
  // If not we just end the function and wait for the next loop.
  if (!client.connected()) {
    connect();
  }

}

void connect() {
  connectToWiFi();
  Serial.println("WiFi OK");
  connectToAWS();
  Serial.println("AWS OK");
}
