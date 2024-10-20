#include "Arduino.h"
#include "SensorArray.h"
#include <DistanceSensor.h>

SensorArray ::SensorArray() {
  int trigArr[] = {5, 7, 9, 11};
  int echoArr[] = {6, 8, 10, 12};

  for (int i = 0; i < 3; i ++) {
    pinMode(trigArr[i], OUTPUT);
    pinMode(echoArr[i], INPUT);

    DistanceSensor sensor(trigArr[i], echoArr[i]);

    setSensors(sensor, i);
  }
}