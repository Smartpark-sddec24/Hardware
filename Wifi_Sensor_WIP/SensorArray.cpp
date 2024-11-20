#include "Arduino.h"
#include "SensorArray.h"
#include <DistanceSensor.h>

//LED Pin Assignments
//          R, G, B
// LED1 = [A0,A1,A2]
// LED2 = [A3,A4,A5]
// LED3 = [A6,A7,D13]
// LED1 = [D4,D3,D2]
int redPin[] = { 14, 17, 20, 4 };    //[A0,A3,A6,D4]
int greenPin[] = { 15, 18, 21, 3 };  //[A1,A4,A7,D3]
int bluePin[] = { 16, 19, 13, 2 };   //[A2,A5,D13,D2]


SensorArray ::SensorArray() {
  for (int i = 0; i < 3; i++) {
    spotStatus[i] = false;
  }
}

double SensorArray ::averageMeasurement(DistanceSensor sensor) {
  double average;

  unsigned long startTime = millis();
  
}

void SensorArray ::setStatus(DistanceSensor sensor, int statusIndex) {
  int dist = sensor.getCM();
  char printSentence[50];
  sprintf(printSentence, "Sensor %d dist: ", statusIndex + 1);
  Serial.print(printSentence);
  Serial.println(dist);  //gets the distance in cm
  if (dist <= 30.0) {
    spotStatus[statusIndex] = 1;  // Spot is occupied
  } else {
    spotStatus[statusIndex] = 0;  // Spot is open
  }
}

bool SensorArray ::getStatus(int statusIndex) {
  return spotStatus[statusIndex];
}

void SensorArray ::SensorSetup(int trigPins[], int echoPins[]) {
  //RGB LED Pin Mode
  for (int i = 0; i < 4; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
}

// LED ---------------------------
void SensorArray ::LEDsetup() {
  //RGB LED Pin Mode
  for (int i = 0; i < 4; i++) {
    pinMode(redPin[i], OUTPUT);
    pinMode(greenPin[i], OUTPUT);
    pinMode(bluePin[i], OUTPUT);
  }
}
void SensorArray ::setLED(int index, int status) {
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
    Serial.println("yellow");
    setColor(255, 255, 0, index);  //yellow
  }
}
void SensorArray ::setColor(int redValue, int greenValue, int blueValue, int index) {
  //Writing to LED
  digitalWrite(redPin[index], redValue);
  digitalWrite(greenPin[index], greenValue);
  digitalWrite(bluePin[index], blueValue);
}
