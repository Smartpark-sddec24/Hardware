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
  previousMillisInfo = 0;
  //intervalInfo = 5000;
  interval = 0;
  connected = false;
}

void WifiConnection ::begin() {
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
    checkConnectionStatus();
  }
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
    // delay(5000); // This delay can be changed based on our real-time data needs
  }
}

// HTTP STUFF-----------------------------------------------
//HTTP Requests
WiFiClient wifi;
char host[] = "10.48.9.236:5000";
// char uuid[] = /*"get"/*UUID*/;
HttpClient https(wifi, host);

const int kNetworkDelay = 1000;
const int kNetworkTimeout = 30 * 1000;

// int WifiConnection ::serverGetStatus() {
//   // GET REQUEST--------------------------------------
//   Serial.println("making GET request");
//   int err = 0, intResponse;
//   err = https.get("/getStatus");
//   int statusCode = https.responseStatusCode();
//   String response = https.responseBody();

//   Serial.print("Status code: ");
//   Serial.println(statusCode);
//   Serial.print("Response: ");
//   Serial.println(response);
//   intResponse = response.toInt();
//   return intResponse;
// }

// int WifiConnection ::serverGetSpots(){
//   int err = 0, intResponse;
//   err = https.get("/getSpots");
//   int statusCode = https.responseStatusCode();
//   String response = https.responseBody();
//    intResponse = response.toInt();
//   return intResponse;
// }

int WifiConnection ::serverUpdateSpot(bool is_occupied, int spot_id) {
  int isReservedInt;
int WifiConnection ::serverGetStatus() {
  if(flag == false){
    flag = true;
  }
  // GET REQUEST--------------------------------------
  Serial.println("making GET request");
  int err = 0, intResponse;
  err = https.get("/getStatus");
  int statusCode = https.responseStatusCode();
  String response = https.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  intResponse = response.toInt();
  flag = false;
  return intResponse;
}

int WifiConnection ::serverGetSpots(){
  if(flag == false){
    flag = true;
  }
  int err = 0, intResponse;
  err = https.get("/getSpots");
  int statusCode = https.responseStatusCode();
  String response = https.responseBody();
   intResponse = response.toInt();
  flag = false; 
  return intResponse;
}

void WifiConnection ::serverUpdateSpot(int status, int id) {
  if(flag == false){
    flag = true;
  }
  String postData;
  String contentType = "text/plain";
  postData = "spot_id=%d&is_occupied=%b", spot_id, is_occupied;
  Serial.println("making POST request");
  https.post("/updateSpot?", contentType, postData);

  // read the status code and body of the response
  int statusCode = https.responseStatusCode();
  Serial.print("responseBody: ");
  Serial.println(https.responseBody());
  String isReserved = https.responseBody();
  Serial.print("Status code: ");
  Serial.println(statusCode);

  Serial.print("isReserved: ");
  Serial.println(isReserved);
  isReservedInt = isReserved.toInt();

  return isReservedInt;
  // delay(5000);
  flag = false;
}
