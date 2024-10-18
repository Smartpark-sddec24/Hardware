#include "WifiConnection.h"
#include "arduino_secrets.h"
#include <DistanceSensor.h> //Library by Segilmez06
#include <ArduinoHttpClient.h>

//Distance Sensors
//Sensor 4
const int S4_Trig = 5;
const int S4_Echo = 6;
DistanceSensor sensor4 = DistanceSensor(S4_Trig, S4_Echo);

//Sensor 3
const int S3_Trig = 7;
const int S3_Echo = 8;
DistanceSensor sensor3 = DistanceSensor(S3_Trig, S3_Echo);

//Sensor 2
const int S2_Trig = 9;
const int S2_Echo = 10;
DistanceSensor sensor2 = DistanceSensor(S2_Trig, S2_Echo);

//Sensor 1
const int S1_Trig = 11;
const int S1_Echo = 12;
DistanceSensor sensor1 = DistanceSensor(S1_Trig, S1_Echo);

int distance[4];

//WiFi vars
char ssid[] = SECRET_SSID;
WifiConnection wifiConnection(ssid);

//HTTP Requests
WiFiClient wifi;
char host[] = "f2cfd6bf-13e6-4e69-b465-99e6732e63bc.mock.pstmn.io";
// char uuid[] = /*"get"/*UUID*/;
HttpClient https(wifi, host);

void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("WiFi connection begin");

  //Sensor 1 Pin Mode
  pinMode(S1_Trig, OUTPUT);
  pinMode(S1_Echo, INPUT);

  //Sensor 2 Pin Mode
  pinMode(S2_Trig, OUTPUT);
  pinMode(S2_Echo, INPUT);
  
  //Sensor 3 Pin Mode
  pinMode(S3_Trig, OUTPUT);
  pinMode(S3_Echo, INPUT);

  //Sensor 4 Pin Mode
  pinMode(S4_Trig, OUTPUT);
  pinMode(S4_Echo, INPUT);

  wifiConnection.begin();
}

const int kNetworkDelay = 1000;
const int kNetworkTimeout = 30*1000;

void loop()
{
  int err =0;
  
  err = https.get("/getStatus");
  if (err == 0)
  {
    Serial.println("startedRequest ok");

    err = https.responseStatusCode();
    if (err >= 0)
    {
      Serial.print("Got status code: ");
      Serial.println(err);

      // Usually you'd check that the response code is 200 or a
      // similar "success" code (200-299) before carrying on,
      // but we'll print out whatever response we get

      // If you are interesting in the response headers, you
      // can read them here:
      //while(http.headerAvailable())
      //{
      //  String headerName = http.readHeaderName();
      //  String headerValue = http.readHeaderValue();
      //}

      int bodyLen = https.contentLength();
      Serial.print("Content length is: ");
      Serial.println(bodyLen);
      Serial.println();
      Serial.println("Body returned follows:");
    
      // Now we've got to the body, so we can print it out
      unsigned long timeoutStart = millis();
      char c;
      // Whilst we haven't timed out & haven't reached the end of the body
      while ( (https.connected() || https.available()) &&
             (!https.endOfBodyReached()) &&
             ((millis() - timeoutStart) < kNetworkTimeout) )
      {
          if (https.available())
          {
              c = https.read();
              // Print out this character
              Serial.print(c);
             
              // We read something, reset the timeout counter
              timeoutStart = millis();
          }
          else
          {
              // We haven't got any data, so let's pause to allow some to
              // arrive
              delay(kNetworkDelay);
          }
      }
    }
    else
    {    
      Serial.print("Getting response failed: ");
      Serial.println(err);
    }
  }
  else
  {
    Serial.print("Connect failed: ");
    Serial.println(err);
  }
  https.stop();

  // And just stop, now that we've tried a download
  while(1);
  // wifiConnection.wifiInfo();
  // takeMeasurements();


  // Serial.print("Sensor 1: ");
  // Serial.println(distance[0]);

}

void takeMeasurements() {
    //Taking measurement.
  distance[0] = sensor1.getCM();
  delay(100);

  distance[1] = sensor2.getCM();
  delay(100);

  distance[2] = sensor3.getCM();
  delay(100);

  distance[3] = sensor4.getCM();
  delay(100);
}