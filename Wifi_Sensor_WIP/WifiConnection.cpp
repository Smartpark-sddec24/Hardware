#include "api/Print.h"
#include <stdio.h>
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
#include <ArduinoHttpClient.h>


WifiConnection ::WifiConnection(const char* ssid) {
  bcopy(ssid, _ssid, strlen(ssid));
  status = WL_IDLE_STATUS;
  connected = false;
  spot_ids;
}

void WifiConnection ::begin() {
  while (status != WL_CONNECTED) {  // While the connection is not successful
    Serial.print("Attempting to connect to network: ");
    Serial.println(_ssid);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(_ssid);
    checkConnectionStatus();
    // wait 5 seconds for connection:
    delay(5000);
  }

  WiFi.macAddress(mac);

  connected = true;
  // Connection successful
  Serial.println("You're connected to the network");
  Serial.println("---------------------------------------");
}

void WifiConnection ::wifiInfo() {

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(rssi);

  // Get the connection status
  checkConnectionStatus();
}

void WifiConnection ::checkConnectionStatus() {
  status = WiFi.status();

  Serial.print("Status: ");
  Serial.print(status);
  Serial.print(" ");

  switch (status) {
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
  int attempts = 0;
  while (status != WL_CONNECTED) {
    if (attempts > 2) {
      NVIC_SystemReset();
    }
    status = WiFi.begin(_ssid);
    attempts++;
  }
}

// HTTP STUFF-----------------------------------------------
//HTTP Requests
WiFiClient wifi;
char host[] = "10.48.8.116";

HttpClient http(wifi, host, 5000);

int* WifiConnection ::serverUpdateSpot(bool* is_occupied, int* spot_ids) {

  int* isReservedInt;
  char isReserved[25];
  String contentType = "application/json";

  char postInfo[300] = {'[', '\0'};
  char spotInfoBuff[300];

  for (int i = 0; i < 4; i++) {
    if (i < 3) {
      sprintf(spotInfoBuff, "{\"spot_id\":%d,\"is_occupied\":%d},", spot_ids[i], is_occupied[i]);
    } else {
      sprintf(spotInfoBuff, "{\"spot_id\":%d,\"is_occupied\":%d}]", spot_ids[i], is_occupied[i]);
    }
    strcat(postInfo, spotInfoBuff);
  }

  Serial.print("POST INFO: ");
  Serial.println(postInfo);

  // Serial.println("making POST request");
  http.post("/updateSpot", contentType, postInfo);
  Serial.println("POST complete");

  // read the status code and body of the response
  int statusCode = http.responseStatusCode();
  Serial.print("responseBody: ");

  http.responseBody().toCharArray(isReserved, 25);;
  Serial.print("Status code: ");
  Serial.println(statusCode);

  Serial.print("isReserved: ");
  Serial.println(isReserved);
  sscanf(isReserved, "[%d,%d,%d,%d]", &isReservedInt[0], &isReservedInt[1], &isReservedInt[2], &isReservedInt[3]);
  return isReservedInt;
}

int WifiConnection ::serverGetSpotIds() {
  Serial.println("Making GET Request");
  String contentType = "text/plain";

  char mac_address[(sizeof mac) + 1];
  mac_address[sizeof mac] = 0;
  // sprintf(mac_address, "%x:%x:%x:%x:%x:%x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  snprintf(mac_address, sizeof(mac_address), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  Serial.println("Mac address");

  char getData[100];
  sprintf(getData, "/initialize?mac_address=%s", mac_address);
  http.get(getData);
  Serial.println("Get Data");

  int statusCode = http.responseStatusCode();
  char response[100];
  http.responseBody().toCharArray(response, 100);
  sscanf(response, "[%d,%d,%d,%d]", &spot_ids[0], &spot_ids[1], &spot_ids[2], &spot_ids[3]);
  Serial.println("response");
  return statusCode;
}
