#ifndef SensorArray_h
#define SensorArray_h

#include <Arduino.h>
#include <DistanceSensor.h>

class SensorArray {
  public:
    /*
     * A constructor for a sensor array of up to four ultrasonic sensors
     * Takes in two arrays: trigArr and echoArr. The elements of these arrays
     *    are meant to be assigned in pairs, i.e. trigArr[0] will be mapped
     *    to the same sensor as echoArr[0]
     */
    SensorArray();
    
    /*
     * This method intializes 
     */
    void setSensors(DistanceSensor sensor, int sensorArrayIndex) {
      this->sensorArray[sensorArrayIndex] = sensor;
    }

    /*
     * Iterates through the array of sensors and measures the distances
     *    each sensor sees.
     */
    void measureDistances() {
      for(int i = 0; i < 3; i ++) {
        distances[i] = sensorArray[i].getCM();
      }
    }

    double* getDistances() {
      return distances;
    }
  private:
    /*
     * An array to store measured distance measurements
     */
    double distances[4];
    
    /*
     * An array of ultrasonic distance sensors
     */
    DistanceSensor sensorArray[4];
};

#endif