#include "WifiConnection.h"
#include "SensorArray.h"
#include "arduino_secrets.h"
#include <DistanceSensor.h> //Library by Segilmez06
//#include <HttpClient.h> //Library by Adrian McEwan

//Distance Sensors
//Sensor 4
const int S4_Trig = 5;
const int S4_Echo = 6;
DistanceSensor sensor4 = DistanceSensor(S4_Trig, S4_Echo);

//Sensor 3
const int S3_Trig = 7;
const int S3_Echo = 8;
DistanceSensor sensor3 = DistanceSensor(S3_Trig, S3_Echo);

//Sensor 2
const int S2_Trig = 9;
const int S2_Echo = 10;
DistanceSensor sensor2 = DistanceSensor(S2_Trig, S2_Echo);

//Sensor 1
const int S1_Trig = 11;
const int S1_Echo = 12;
DistanceSensor sensor1 = DistanceSensor(S1_Trig, S1_Echo);

SensorArray sensorArray = SensorArray();

int distance[4];

//LED Pin Assignments
int redPin= 13;
int greenPin = A6;
int bluePin = A7;
int lotnum = 0;

// //WiFi vars
// char ssid[] = SECRET_SSID;
// WifiConnection wifiConnection(ssid);

void setup() {
  Serial.begin(9600);
  delay(5000);
  // Serial.println("WiFi connection begin");

  // Sensor 1 Pin Mode
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

  //RGB LED Pin Mode
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // wifiConnection.begin();
}

void loop() {
  // wifiConnection.wifiInfo();
  takeMeasurements();

  //sensorArray.setStatus(sensor1, 0);
  // // Serial.print("Sensor 1 dist: ");
  // // Serial.println(/*sensor1.getCM()*/distance[0]);
  // Serial.print("Status: ");
  // Serial.println(sensorArray.getStatus(0));

  Serial.print("Sensor 1: ");
  Serial.println(distance[0]);

  //RGB Color Rotations
    for (lotnum == 0; lotnum <=3; lotnum++){
    if (lotnum == 1){
      setColor(0,255,0); //Green 
      delay(3000);
    }
    if (lotnum == 2){
      setColor(0,0,255); //White
      delay(3000);
    }
    if (lotnum == 3){
      setColor(255,0,0); //Red
      delay(3000);
    }
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

void setColor(int redValue, int greenValue, int blueValue) {
  //Writing to LED
  digitalWrite(redPin, redValue);
  digitalWrite(greenPin, greenValue);
  digitalWrite(bluePin, blueValue);
}