#include "Arduino.h"
#include "SensorArray.h"
#include <DistanceSensor.h>

SensorArray ::SensorArray() {
  for (int i = 0; i < 3; i ++) {
    spotStatus[i] = 0;
  }
}

void SensorArray ::setStatus(DistanceSensor sensor, int statusIndex) {
  int dist = sensor.getCM();

  if (dist <= 30.0) {
    spotStatus[statusIndex] = 1;  // Spot is occupied
  } else {
    spotStatus[statusIndex] = 0;  // Spot is open
  }
}

int SensorArray ::getStatus(int statusIndex) {
  return spotStatus[statusIndex];
}