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
     *
     * @param trigArr - an array of trigger pin values
     * @param echoArr - an array of echo pin values
     */
    SensorArray(const int* trigArr, const int* echoArr);
    
    /*
     * Iterates through the array of sensors and measures the distances
     *    each sensor sees.
     */
    void measureDistances();
  private:
    /*
     * An array to store measured distance measurements
     */
    double[4] distances;
    /*
     * An array of ultrasonic distance sensors
     */
    DistanceSensor[4] array;
}