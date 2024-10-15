#include "Arduino.h"
#include "SensorArray.h"
#include <DistanceSensor.h>

SensorArray ::SensorArray() {
  DistanceSensor sensor1 = DistanceSensor(trigArr[0], echoArr[0]);
  DistanceSensor sensor2 = DistanceSensor(trigArr[1], echoArr[1]);
  DistanceSensor sensor3 = DistanceSensor(trigArr[2], echoArr[2]);
  DistanceSensor sensor4 = DistanceSensor(trigArr[3], echoArr[3]);

  sensorArray[0] = sensor1;
  sensorArray[1] = sensor2;
  sensorArray[2] = sensor3;
  sensorArray[3] = sensor4;
}