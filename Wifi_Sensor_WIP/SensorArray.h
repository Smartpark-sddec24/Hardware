#ifndef SensorArray_h
#define SensorArray_h

#include <Arduino.h>
#include <DistanceSensor.h>

/**
 * This class represents a sensor array used to measure distances and translate it
 *    into a parking spot's current status:
 *      0: Open
 *      1: Occupied
 *      2: Reserved
 */
class SensorArray {
public:
  /**
     * Currently constructs a SensorArray object which initializes all spotStatus elements to open.
     */
  SensorArray();

  /**
   * This holds the status of the four spots that a single array is responsible for.
   *    0: Open spot
   *    1: Occupied spot
   *    2: Reserved spot
   *
   * It should be noted that the POST request header for an updated status is a boolean "is_occupied" field
   *    indicating that we should send a false value on an open spot and a true value on an occupied spot.
   */
  bool spotStatus[4];

  /**
   * This method currently takes in a single sensor and its corresponding status index in spotStatus, makes a
   *  measurement with the sensor and translates it into an updated status stored at statusIndex.
   */
  void setStatus(DistanceSensor sensor, int statusIndex);

  /**
   * Returns the status of a sensor at some statusIndex.
   */
  bool* getStatus() ;

  /**
  * Sets the pin modes for each of the sensors
  */
  void SensorSetup(int trigPins[], int echoPins[]);

  /****************************************
  LED FUNCTIONS
  *****************************************/

  /*
   * Defines each LED pin array as an output pin
   */
  void LEDsetup ();

  /*
   * Takes in the current status of a sensor at some index and sets the corresponding led to either
   *    of the following colors:
   *        Green = Open
   *        Red   = Occupied
   */
  void setLED(int index, int status);

  /*
   * Sets the analog value of each 
   */
  void setColor(int redValue, int greenValue, int blueValue, int index);
};

#endif