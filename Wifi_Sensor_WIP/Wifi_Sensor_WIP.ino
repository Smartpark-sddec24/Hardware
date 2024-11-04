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

// DistanceSensor sensor4 = DistanceSensor(S4_Trig, S4_Echo);

//Sensor 3
// const int S3_Trig = 7;
// const int S3_Echo = 8;
// DistanceSensor sensor3 = DistanceSensor(S3_Trig, S3_Echo);

// //Sensor 2
// const int S2_Trig = 9;
// const int S2_Echo = 10;
// DistanceSensor sensor2 = DistanceSensor(S2_Trig, S2_Echo);

// //Sensor 1
// const int S1_Trig = 11;
// const int S1_Echo = 12;
// DistanceSensor sensor1 = DistanceSensor(S1_Trig, S1_Echo);

SensorArray sensorArrayLIB = SensorArray();

// DistanceSensor arrTest[] = { sensor1, sensor2, sensor3, sensor4 };
int distance[4];

//LED Pin Assignments
int redPin[] = { 16, 19 };
int greenPin[] = { 17, 20 };
int bluePin[] = { 18, 21 };


// //WiFi vars
char ssid[] = SECRET_SSID;
WifiConnection wifiConnection(ssid);

//HTTP Requests
WiFiClient wifi;
char host[] = "f2cfd6bf-13e6-4e69-b465-99e6732e63bc.mock.pstmn.io";
// char uuid[] = /*"get"/*UUID*/;
HttpClient https(wifi, host);

const int kNetworkDelay = 1000;
const int kNetworkTimeout = 30 * 1000;

void setup() {
  Serial.begin(9600);
  delay(5000);
  // Sensor Pin mode
  sensorArrayLIB.SensorSetup(S_Trig, S_Echo);
  //RGB LED Pin Mode
  LEDsetup();
  // Wifi connection
  Serial.println("WiFi connection begin");
  wifiConnection.begin();
}


void loop() {
  // wifiConnection.wifiInfo();

for (int i=0;i<2;i++){
  sensorArrayLIB.setStatus(sensorArr[i], i);
  String printSentence;
  printSentence= "Sensor %d dist: ",i;
  Serial.print(printSentence);
  Serial.println(sensorArr[i].getCM());//gets the distance in cm
  Serial.print("Status: ");
  
  Serial.println(sensorArrayLIB.getStatus(i));// gets the status of a spot (open, occupied, reserved)
  setLED(i, sensorArrayLIB.getStatus(i)); //sets the LED to the correct color. Eventually will use get request instead of get status

}

  
  // getRequest(); //get request returns a number value to use in setLED()

  // postRequest(sensorArrayLIB.getStatus(i), i); // post request posts the sensor data to a spot


  // And just stop, now that we've tried a download
  while (1)
    ;
  
}



int getRequest() {
  // GET REQUEST--------------------------------------
  Serial.println("making GET request");
  int err = 0, intResponse;
  err = https.get("/getStatus");
  int statusCode = https.responseStatusCode();
  String response = https.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  intResponse = response.toInt();
  return intResponse;
}

void postRequest(int status, int id) {
  String postData;
  String contentType = "text/plain";
  postData = "status=%d&id=%d", status, id;
  Serial.println("making POST request");
  https.post("/setState?", contentType, postData);

  // read the status code and body of the response
  int statusCode = https.responseStatusCode();
  String response = https.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  delay(5000);
}

// The server does not accommodate a PUT request for hardware, so this request is unnecessary
void putRequest(int status, int id) {
  String putData;
  String contentType = "text/plain";
  putData = "status=%d&id=%d", status, id;
  Serial.println("making PUT request");
  https.put("/setState?", contentType, putData);

  // read the status code and body of the response
  int statusCode = https.responseStatusCode();
  String response = https.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  delay(5000);
  // distance[3] = sensor4.getCM();
  delay(100);
}
// LED ---------------------------
void LEDsetup() {
  //RGB LED Pin Mode
  for (int i = 0; i < 2; i++) {
    pinMode(redPin[i], OUTPUT);
    pinMode(greenPin[i], OUTPUT);
    pinMode(bluePin[i], OUTPUT);
  }
}
void setLED(int index, int status) {
  // int status = getRequest();
  Serial.print("setLED status:");
  Serial.println(status);
  if (status == 0) {
    Serial.println("green");
    setColor(0, 255, 0, index);  //Green
  } else if (status == 1) {
    Serial.println("red");
    setColor(255, 0, 0, index);  //Red
  } else {
    Serial.println("white");
    setColor(255, 0, 255, index);  //White
  }
}
void setColor(int redValue, int greenValue, int blueValue, int index) {
  //Writing to LED
  digitalWrite(redPin[index], redValue);
  digitalWrite(greenPin[index], greenValue);
  digitalWrite(bluePin[index], blueValue);
}