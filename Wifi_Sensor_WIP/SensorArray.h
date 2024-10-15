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
    SensorArray();
    
    /*
     * Iterates through the array of sensors and measures the distances
     *    each sensor sees.
     */
    void measureDistances();
  private:
    /*
     * An array to store measured distance measurements
     */
    double distances[4];

    /*
     * An array of trigger pins for the sensors
     */
    int trigArr[4] = {5, 7, 9, 11};

    /*
     * An array of echo pins for the sensors
     */
    int echoArr[4] = {6, 8, 10, 12};
    
    /*
     * An array of ultrasonic distance sensors
     */
    DistanceSensor sensorArray[4] = {DistanceSensor(trigArr[0], echoArr[0]),
                                     DistanceSensor(trigArr[1], echoArr[1]),
                                     DistanceSensor(trigArr[2], echoArr[2]),
                                     DistanceSensor(trigArr[3], echoArr[3])};
};

#endif