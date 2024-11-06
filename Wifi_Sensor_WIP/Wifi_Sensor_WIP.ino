#include "WifiConnection.h"
#include "SensorArray.h"
#include "arduino_secrets.h"
#include <DistanceSensor.h>  //Library by Segilmez06
#include <ArduinoHttpClient.h>
#include <string.h>

//Distance Sensors
int S_Trig[] = { 5, 7, 9, 11 };
int S_Echo[] = { 6, 8, 10, 12 };
DistanceSensor sensorArr[] = {
  DistanceSensor(S_Trig[0], S_Echo[0]),
  DistanceSensor(S_Trig[1], S_Echo[1]),
  DistanceSensor(S_Trig[2], S_Echo[2]),
  DistanceSensor(S_Trig[3], S_Echo[3])
};

SensorArray sensorArray_LED = SensorArray();

// //WiFi vars
char ssid[] = SECRET_SSID;
WifiConnection wifiConnection_HTTP(ssid);

void setup() {
  Serial.begin(9600);
  delay(5000);
  // Sensor Pin mode
  sensorArray_LED.SensorSetup(S_Trig, S_Echo);
  //RGB LED Pin Mode
  sensorArray_LED.LEDsetup();
  // Wifi connection
  Serial.println("WiFi connection begin");
  // wifiConnection_HTTP.begin();
}


void loop() {
  // wifiConnection.wifiInfo();

  for (int i = 0; i < 4; i++) {
    sensorArray_LED.setStatus(sensorArr[i], i);
    delay(5000);

    Serial.print("Status: ");

    Serial.println(sensorArray_LED.getStatus(i));            // gets the status of a spot (open, occupied)
    sensorArray_LED.setLED(i, sensorArray_LED.getStatus(i));  //sets the LED to the correct color. Eventually will use serverGetStatus instead of getStatus
    delay(5000);
  }


  // wifiConnection_HTTP.serverGetStatus(); //serverGetStatus returns a number value to use in setLED()

  // wifiConnection_HTTP.serverUpdateSpot(sensorArrayLIB.getStatus(i), i); // post request posts the sensor data to a spot


  // And just stop, now that we've tried a download
  while (1)
    ;
}
