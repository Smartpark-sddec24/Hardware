#ifndef SensorArray_h
#define SensorArray_h

#include <Arduino.h>
#include <DistanceSensor.h>

class SensorArray {
  public:
    SensorArray();

    int spotStatus[4];

    void setStatus(DistanceSensor sensor, int statusIndex);

    int getStatus(int statusindex);
};

#endif