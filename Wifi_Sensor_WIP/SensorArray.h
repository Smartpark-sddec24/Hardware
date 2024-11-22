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
 *
 * TODO: This class will be reweritten to incorporate an actual sensor array
 *    This is make our main file cleaner and easier to read.
 * 
 * This class should also have an array of spot ids for server communication.
 * 
 * TODO: The spot status systems is indicating we should only store an open or occupied status in this
 *  file. Holding spots open on a reserved spot up until the driver gets to their reserved space. However,
 *  the LED will take a signal from a main file value overriding this file's current spot status for reserved spots.
 *      Easier said than done.
 * 
 * TODO: A major rewrite that will make a few things easier and a couple of things possibly more difficult is 
 *  changing the data type of spotStatus from int to bool. This would make POST request translation of a spot's
 *  integer status into a boolean for the server unnecessary.
 */
class SensorArray {
public:
  /**
     * Currently constructs a SensorArray object which initializes all spotStatus elements to open.
     * 
     * TODO: This will need to incorporate parameters for main file constructed sensors to assign to 
     *  an array in this file. However, getting around the no DistanceSensor constructor error I was encountering
     *  previously may still be an issue.
     * 
     * I had written a whole TODO about how this constructor should pull data from the server, but this is
     *  unnecessary due to the nature of real time systems. So instead, we should use this constructor with the
     *  TODO above, and immediately take measurements just after its construction.
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
   *
   * TODO: Alternatively, this could be changed to a boolean array to match the server data. This would cut out all
   *  of the post and/or preprocessing necessary for making a POST request, currently having to translate it into a bool
   *  from an int.
   */
  bool spotStatus[4];

  /**
   * This method currently takes in a single sensor and its corresponding status index in spotStatus, makes a
   *  measurement with the sensor and translates it into an updated status stored at statusIndex.
   * 
   * TODO: Rewrite to incorporate a sensor array and iterate through the array, taking measurements and updating the
   *  spotStatus array as needed.
   *
   * TODO: As stated in the TODO for spotStatus above, if the spotStatus is rewritten to store boolean values, all of 
   *  the translation from an int to a bool will be handled in this method and it will simply store whether a spot is taken
   *  or not.
   */
  void setStatus(DistanceSensor sensor, int statusIndex);

  /**
   * Returns the status of a sensor at some statusIndex.
   *
   * TODO: A possible rewrite for this method could be to return a bool insteado of the raw status.
   *  this would make POST requests a bit easier to write, as it would not have any post processing to do after calling
   *  this method. This change would be evidence for keeping the spotStatus array in this file.
   * 
   * Also, if the spotStatus array is a public variable, this method may not be necessary since we should be able to 
   *  make references directly to the array. However, it's possible that we should make the array private since we don't
   *  anyone else in terms of other classes to be able to change its data.
   */
  bool getStatus(int statusindex);

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