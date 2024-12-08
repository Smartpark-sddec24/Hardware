/**
 * This class creates and maintains a WiFi connection between an
 *    Arduino Nano 33 IoT and some WiFi network
 */

#ifndef WifiConnection_h
#define WifiConnection_h

#include <Arduino.h>
#include <WiFiNINA.h>  //Library by Arduino
#include "arduino_secrets.h"

class WifiConnection {
public:
  int spot_ids[4];

  /*
   * Flag to indicate that the spot ids have been retrieved from the server on a system start up
   */
  bool idFlag = false;

  /**
   * The MAC address of this board
   */ 
  byte mac[6];
 
  /*
   * Constructs a WifiConnection which manages the WiFi connection
   *    of an Arduino Nano 33 IoT
   *
   * @param ssid - the ssid of the WiFi network the board is connecting to
   */
  WifiConnection(const char* ssid);

  /*
   * Establishes an initial connection to the network
   */
  void begin();

  /*
   * Displays the following connection information:
   *    Board IP Address
   *    Network SSID
   *    Received Signal Strength
   */
  void wifiInfo();

  /*
   * Checks the connection status and reconnects upon a disconnect
   *    Status codes:
   *      0: System idle
   *      1: No SSID available
   *      2: Scan for networks completed
   *      3: Connected to the network with SSID "_ssid"
   *      4: Connection failed
   *      5: Connection lost
   *          In this case, see reconnect() below
   *      6: Disconnected
   *      255: No WiFi shield detected
   *      Other: Unknown code
   */
  void checkConnectionStatus();

  /*
   * Disconnects the board from the network
   */
  void disconnect();

  /*
   * A value storing the status of the connection
   */
  int status;

  // NOTE: Removed both GET requests as they are unnecessary

  /*
   * Posts an updated status for a spot with id 'id' to the server.
   * The response of this request will carry an 'is_reserved' status and this will
   *   be used to overwrite our LED color to indicate a reservation for that spot.
   * 
   * TODO: Update parameters to take in an array of statuses and ids to post in
   *    a request body then parse an array of responses
   */
  int* serverUpdateSpot(bool* is_occupied, int* spot_ids);

  /*
   * Used to get the ids of the spots which correspond to the sensors on system start up.
   * Returns - an array of spot ids
   */
  int serverGetSpotIds();

private:
  /*
   * This function reconnects the board to the network
   * In the case of up to three faild reconnects, this function restarts the system
   */
  void reconnect();
  /*
   * The SSID of the network
   */
  char _ssid[30];

  /*
   * A flag to signal when the system is intentionally disconnected from the network so that
   *    reconnect() is not called if a call is made to checkConnectionStatus() after a
   *    disconnect() call is made.
   */
  bool connected;
};

#endif