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

//WiFi vars
char ssid[] = SECRET_SSID;
WifiConnection wifiConnection_HTTP(ssid);

int* is_reserved;
volatile bool timerFlag = false;

void setup() {
  Serial.begin(9600);
  delay(5000);
  // Sensor Pin mode
  sensorArray_LED.SensorSetup(S_Trig, S_Echo);
  //RGB LED Pin Mode
  sensorArray_LED.LEDsetup();

  // Take initial measurements
  for (int i = 0; i < 4; i++) {
    sensorArray_LED.setStatus(sensorArr[i], i);
  }

  // Wifi connection
  Serial.println("WiFi connection begin");
  wifiConnection_HTTP.begin();             //Set up WiFi connection
  int responseCode = 0;
  while (responseCode != 200){
      responseCode = wifiConnection_HTTP.serverGetSpotIds();  // GET request for spot ids.
  }
  wifiConnection_HTTP.idFlag = true;
}

void loop() {

  bool* is_occupied_arr = sensorArray_LED.getStatus();
  is_reserved = wifiConnection_HTTP.serverUpdateSpot(is_occupied_arr, wifiConnection_HTTP.spot_ids);  // post request posts the sensor data to a spot
  
  // Take measurements and print their values
  for (int i = 0; i < 4; i++) {
    char distPrint[100];
    sensorArray_LED.setStatus(sensorArr[i], i);
    delay(100);  //Eventually delete but for troubleshooting leave
  }

  is_occupied_arr = sensorArray_LED.getStatus();
  for (int i = 0; i < 4; i++) {
    if (is_reserved[i] == 1) {        // checks if the server has the spot reserved
      sensorArray_LED.setLED(i, 2);   // if the spot is reserved then turn yellow
    } else if (is_occupied_arr[i]) {  //checks if our system has the spot as occupied or open
      sensorArray_LED.setLED(i, 1);   //if the spot is occupied turn red
    } else {
      sensorArray_LED.setLED(i, 0);  //if the spot is open turn green
    }
    delay(500); //Eventually delete but for troubleshooting leave
  }
}
