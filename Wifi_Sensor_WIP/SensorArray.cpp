#include "Arduino.h"
#include "SensorArray.h"
#include <DistanceSensor.h>

SensorArray ::SensorArray() {
  trigArr = {5, 7, 9, 11};
  echoArr = {6, 8, 10, 12};

  

  // sensor1 = DistanceSensor(trigArr[0], echoArr[0]);
  // sensor2 = DistanceSensor(trigArr[1], echoArr[1]);
  // sensor3 = DistanceSensor(trigArr[2], echoArr[2]);
  // sensor4 = DistanceSensor(trigArr[3], echoArr[3]);
}