#ifndef SensorArray_h
#define SensorArray_h

#include <Arduino.h>
#include <DistanceSensor.h>

// struct SensorArrayStruct {
//   SensorArrayStruct(int* trigArr, int* echoArr);

//   DistanceSensor sensor1;
//   DistanceSensor sensor2;
//   DistanceSensor sensor3;
//   DistanceSensor sensor4;
// };

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
    // const int trigArr[4] = {5, 7, 9, 11};

    // /*
    //  * An array of echo pins for the sensors
    //  */
    // const int echoArr[4] = {6, 8, 10, 12};

    // struct trigPinStruct {
    //   trigPinStruct();

    //   const int s1_pin = 5;
    //   const int s2_pin = 7;
    //   const int s3_pin = 9;
    //   const int s4_pin = 11;
    // };

    // trigPinStruct trigPins;

    // struct echoPinStruct {
    //   echoPinStruct();

    //   const int s1_pin = 6;
    //   const int s2_pin = 8;
    //   const int s3_pin = 10;
    //   const int s4_pin = 12;
    // };

    // echoPinStruct echoPins;

    //SensorArrayStruct sensorArray;
    
    /*
     * An array of ultrasonic distance sensors
     */
    DistanceSensor sensorArray[4];
};

#endif