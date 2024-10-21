#include "Arduino.h"
#include "SensorArray.h"
#include <DistanceSensor.h>

// SensorArray ::SensorArray() {
//   // int trigArr[] = {5, 7, 9, 11};
//   // int echoArr[] = {6, 8, 10, 12};

//   // for (int i = 0; i < 3; i ++) {
//   //   pinMode(trigArr[i], OUTPUT);
//   //   pinMode(echoArr[i], INPUT);

//   //   // DistanceSensor sensor(trigArr[i], echoArr[i]);

//   //   setSensors(trigArr[i], echoArr[i], i);
//   }
//}

SensorArray ::SensorArray() {
  for (int i = 0; i < 3; i ++) {
    spotStatus[i] = 0;
  }
}

void SensorArray ::setStatus(DistanceSensor sensor, int statusIndex) {
  // Serial.println("In setStatus");
  // Serial.println(sensor.getCM());
  int dist = sensor.getCM();
  Serial.print("Dist: ");
  Serial.println(dist);
  if (dist <= 30.0) {
    // Serial.print("Status from setStatus: ");
    // Serial.println(spotStatus[statusIndex]);
    spotStatus[statusIndex] = 1;  // Spot is occupied
    // Serial.print("Status from setStatus after setting: ");
    // Serial.println(spotStatus[statusIndex]);
  } else {
    spotStatus[statusIndex] = 0;  // Spot is open
  }
}

int SensorArray ::getStatus(int statusIndex) {
  return spotStatus[statusIndex];
}