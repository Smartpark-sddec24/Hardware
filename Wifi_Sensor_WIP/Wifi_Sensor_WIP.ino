#include "WifiConnection.h"
#include "arduino_secrets.h"

// Will uses HTTPClient to 

char ssid[] = SECRET_SSID;
WifiConnection wifiConnection(ssid);

void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("WiFi connection begin");

  wifiConnection.begin();
}

void loop() {
  wifiConnection.wifiInfo();
}