#include <SPI.h>
#include <WiFi.h>

char ssid[] = "........";  // the name of your network
char password[] = "........";

int status = WL_IDLE_STATUS;  // the Wifi radio's status

byte mac[6];  // the MAC address of your Wifi shield

void setup()
{
    Serial.begin(115200);

    status = WiFi.begin("IASTATE");

    if (status != WL_CONNECTED)
    {
        Serial.println("Couldn't get a wifi connection");
        while (true)
            ;
    }
    // if you are connected, print your MAC address:
    else
    {
        WiFi.macAddress(mac);
        Serial.print("MAC: ");
        Serial.print(mac[5], HEX);
        Serial.print(":");
        Serial.print(mac[4], HEX);
        Serial.print(":");
        Serial.print(mac[3], HEX);
        Serial.print(":");
        Serial.print(mac[2], HEX);
        Serial.print(":");
        Serial.print(mac[1], HEX);
        Serial.print(":");
        Serial.println(mac[0], HEX);
    }
}

void loop() {}