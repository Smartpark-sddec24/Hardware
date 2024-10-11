#include "WifiConnection.h"
#include "arduino_secrets.h"
#include <DistanceSensor.h>

// Will uses HTTPClient to 

//Distance Sensors
//Sensor 1
const int S1_Trig = 5;
const int S1_Echo = 6;
DistanceSensor sensor1 = DistanceSensor(S1_Trig, S1_Echo);

//Sensor 2
const int S2_Trig = 7;
const int S2_Echo = 8;
DistanceSensor sensor2 = DistanceSensor(S2_Trig, S2_Echo);

//Sensor 3
const int S3_Trig = 9;
const int S3_Echo = 10;
DistanceSensor sensor3 = DistanceSensor(S3_Trig, S3_Echo);

//Sensor 4
const int S4_Trig = 11;
const int S4_Echo = 12;
DistanceSensor sensor4 = DistanceSensor(S4_Trig, S4_Echo);

int distance[4];

const long measurementTiming = 50000;
long mTime = 0;

const long wifiInfoTiming = 25000;
long wTime = 0;

//WiFi vars
char ssid[] = SECRET_SSID;
WifiConnection wifiConnection(ssid);

void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("WiFi connection begin");

  //Sensor 1 Pin Mode
  pinMode(S1_Trig, OUTPUT);
  pinMode(S1_Echo, INPUT);

  //Sensor 2 Pin Mode
  pinMode(S2_Trig, OUTPUT);
  pinMode(S2_Echo, INPUT);
  
  //Sensor 3 Pin Mode
  pinMode(S3_Trig, OUTPUT);
  pinMode(S3_Echo, INPUT);

  //Sensor 4 Pin Mode
  pinMode(S4_Trig, OUTPUT);
  pinMode(S4_Echo, INPUT);

  mTime = millis();
  wTime = millis();

  wifiConnection.begin();
}

void loop() {
  if (wTime - millis() >= wifiInfoTiming) {
      wifiConnection.wifiInfo();
      wTime = millis();
  }
  
  if (mTime - millis() >= measurementTiming) {
    takeMeasurements();
    printMeasurements();
    mTime = millis();
  }
}

void takeMeasurements() {
    //Taking measurement.
  distance[0] = sensor1.getCM();
  delay(100);

  distance[1] = sensor2.getCM();
  delay(100);

  distance[2] = sensor3.getCM();
  delay(100);

  distance[3] = sensor4.getCM();
  delay(100);
}

void printMeasurements() {
  //Sensor 1 print
  Serial.print("Sensor 1: ");
  Serial.println(distance[0]);
  
  //Sensor 2 print
  Serial.print("Sensor 2: ");
  Serial.println(distance[1]);
  
  //Sensor 3 print
  Serial.print("Sensor 3: ");
  Serial.println(distance[2]);

  //Sensor 4 print
  Serial.print("Sensor 4: ");
  Serial.println(distance[3]);
}