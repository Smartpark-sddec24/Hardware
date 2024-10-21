#ifndef SensorArray_h
#define SensorArray_h

#include <Arduino.h>
#include <DistanceSensor.h>

/**
 * The sensor array 
 */
class SensorArray {
  // public:
  //   /*
  //    * A constructor for a sensor array of up to four ultrasonic sensors
  //    * Takes in two arrays: trigArr and echoArr. The elements of these arrays
  //    *    are meant to be assigned in pairs, i.e. trigArr[0] will be mapped
  //    *    to the same sensor as echoArr[0]
  //    */
  //   SensorArray() {
  //     int trigArr[] = {5, 7, 9, 11};
  //     int echoArr[] = {6, 8, 10, 12};

  //     for (int i = 0; i < 3; i ++) {
  //       pinMode(trigArr[i], OUTPUT);
  //       pinMode(echoArr[i], INPUT);

  //   // DistanceSensor sensor(trigArr[i], echoArr[i]);

  //       setSensors(trigArr[i], echoArr[i], i);
  //     }
  //   }

  //   /*
  //    * This method intializes
  //    */
  //   // void setSensors(DistanceSensor sensor, int sensorArrayIndex) {
  //   //   this->sensorArray[sensorArrayIndex] = sensor;
  //   // }

  //   void setSensors(int trigPin, int echoPin, int sensorArrayIndex) {
  //     // if (sensorArrayIndex >= 0) {
  //       this->sensorArray[sensorArrayIndex] = DistanceSensor(trigPin, echoPin);
  //     }

  //   /*
  //    * Iterates through the array of sensors and measures the distances
  //    *    each sensor sees.
  //    */
  //   void measureDistances() {
  //     for(int i = 0; i < 3; i ++) {
  //       distances[i] = sensorArray[i].getCM();
  //     }
  //   }

  //   double* getDistances() {
  //     return distances;
  //   }
  // private:
  //   /*
  //    * An array to store measured distance measurements
  //    */
  //   double distances[4];

  //   /*
  //    * An array of ultrasonic distance sensors
  //    */
  //   DistanceSensor sensorArray[4];

  public:
    SensorArray();

    int spotStatus[4];

    void setStatus(DistanceSensor sensor, int statusIndex);

    int getStatus(int statusindex);
};

#endif