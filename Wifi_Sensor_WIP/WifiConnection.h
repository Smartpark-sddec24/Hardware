/**
 * This class creates and maintains a WiFi connection between an
 *    Arduino Nano 33 IoT and some WiFi network
 */

#ifndef WifiConnection_h
#define WifiConnection_h

#include <Arduino.h>
#include <WiFiNINA.h> //Library by Arduino
#include "arduino_secrets.h"

class WifiConnection {
public:
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
   * This function detects a flag that 
   */

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
   * Returns the IP Address of the board
   */
  // IPAddress getIPAddess();

  /*
   * The last time the connection information was displayed
   * ------ MAY NOT BE NECESSARY ------
   */
  unsigned long previousMillisInfo;

  /*
   * A five second interval between connection information displays
   * ------ MAY NOT BE NECESSARY ------
   */
  const long intervalInfo = 5000;

  /*
   * A flag to display connection information
   * 0  -> Display connection information
   * >0 -> Do not display connection information
   */
  int interval;

  /*
   * A value storing the status of the connection
   */
  int status;

  /**
   * This is a flag for a system reset on an initial connection attempt when
   *    the system reads a Disconnected status on start up. If this status is
   *    returned for three connetion attempts, the system will do a hard reset
   */
  int connectionAttempts;
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