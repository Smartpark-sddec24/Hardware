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
    // wait 10 seconds for connection:
    // delay(5000);
  }

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
char host[] = "10.48.9.221";
// char host[] ="f2cfd6bf-13e6-4e69-b465-99e6732e63bc.mock.pstmn.io"; //Hardware url

HttpClient http(wifi, host, 5000);

int WifiConnection ::serverUpdateSpot(bool is_occupied, int spot_id) {
  int isReservedInt = 4;
  String isReserved;
  String contentType = "text/plain";

  char postData[100];
  sprintf(postData, "/updateSpot?spot_id=%d&is_occupied=%d", spot_id, is_occupied);
  // Serial.print("POST DATA: ");
  // Serial.println(postData);

  // Serial.println("making POST request");
  http.post(postData);

  // read the status code and body of the response
  int statusCode = http.responseStatusCode();
  // Serial.print("responseBody: ");

  isReserved = http.responseBody();
  // Serial.print("Status code: ");
  // Serial.println(statusCode);

  // Serial.print("isReserved: ");
  // Serial.println(isReserved);
  isReservedInt = isReserved.toInt();
  return isReservedInt;
}

void WifiConnection ::serverGetSpotIds() {
  Serial.println("Making GET Request");
  String contentType = "text/plain";

  char getData[100];
  // Serial.println(MAC_ADDRESS);
  sprintf(getData, "/initialize?mac_address=%s", MAC_ADDRESS);
  http.get(getData);
  // Serial.println(getData);

  int statusCode = http.responseStatusCode();
  Serial.print("Status Code: ");
  Serial.println(statusCode);
  String response = http.responseBody();
  Serial.print("Response: ");
  Serial.println(response);

  *(spot_ids) << static_cast<int>(response[1]);
  *(spot_ids+1) << static_cast<int>(response[3]);
  *(spot_ids+2) << static_cast<int>(response[4]);
  *(spot_ids+3) << static_cast<int>(response[5]);

  Serial.print("id 1: ");
  Serial.println(*(spot_ids));
  Serial.print("id 2: ");
  Serial.println(*(spot_ids + 1));
  Serial.print("id 3: ");
  Serial.println(*(spot_ids + 2));
  Serial.print("id 4: ");
  Serial.println(*(spot_ids + 3));

  idFlag = true;
}


