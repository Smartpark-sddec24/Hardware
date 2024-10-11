/**
 * Cut out serial monitor calls
 * Create a function to update the main code file
 *    about connection status
 * Upon a disconnect, flag and update main code
 * Reset flag and update main code upon reconnection
 */

#include "Arduino.h"
#include "WifiConnection.h"
#include "arduino_secrets.h"

WifiConnection ::WifiConnection(const char* ssid) {
  bcopy(ssid, _ssid, strlen(ssid));
  status = WL_IDLE_STATUS;
  previousMillisInfo = 0;
  //intervalInfo = 5000;
  interval = 0;
  connected = false;
}

void WifiConnection ::begin() {
  // Serial.print(_ssid);
  while (status != WL_CONNECTED) {  // While the connection is not successful
    Serial.print("Attempting to connect to network: ");
    Serial.println(_ssid);
  
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(_ssid);
    checkConnectionStatus();
    
    // wait 10 seconds for connection:
    delay(10000);
  }

  connected = true;
  // Connection successful
  Serial.println("You're connected to the network");
  Serial.println("---------------------------------------");
}

void WifiConnection ::wifiInfo() {

  unsigned long currentMillisInfo = millis();

  // if (interval < 1) {
    // check if the time after the last update is bigger the interval
    if (currentMillisInfo - previousMillisInfo >= intervalInfo) {
      previousMillisInfo = currentMillisInfo;

      // print your board's IP address:
      IPAddress ip = WiFi.localIP();
      Serial.print("IP Address: ");
      Serial.println(ip);

      // print the received signal strength:
      long rssi = WiFi.RSSI();
      Serial.print("RSSI: ");
      Serial.println(rssi);

      // Get the connection status
      status = WiFi.status();
      Serial.print("Status: ");
      checkConnectionStatus();
    }
  //}
  // interval++;
  // if (status != WL_CONNECTED) {
  //   interval = 0;
  // }
}

void WifiConnection ::checkConnectionStatus() {
  status = WiFi.status();

  Serial.print("Status: ");
  Serial.print(status);
  
  switch(status) {
    case 0:
      Serial.println("System idle");
      break;
    case 1:
      Serial.println("No SSID available");
      break;
    case 2:
      Serial.println("Scan for networks completed");
      break;
    case 3:
      Serial.println("Connected to network");
      break;
    case 4:
      Serial.println("Connection failed");
      break;
    case 5:
      Serial.println("Connection lost");
      if (connected) { reconnect(); }
      break;
    case 6:
      Serial.println("Disconnected");
      break;
    case 255:
      Serial.println("No WiFi shield detected");
      break;
    default:
      Serial.println("Unknown status code");
  }
}

void WifiConnection ::disconnect() {
  status = WiFi.disconnect();
  connected = false;
}

void WifiConnection ::reconnect() {
  while (status != WL_CONNECTED) {
    status = WiFi.begin(_ssid);
    delay(5000); // This delay can be changed based on our real-time data needs
  }
}