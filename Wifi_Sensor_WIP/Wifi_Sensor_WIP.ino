#include "WifiConnection.h"
#include "SensorArray.h"
#include "arduino_secrets.h"
#include <DistanceSensor.h>  //Library by Segilmez06
#include <ArduinoHttpClient.h>
#include <string.h>

//Distance Sensors
int S_Trig[] = { 5, 7, 9, 11 };
int S_Echo[] = { 6, 8, 10, 12 };
DistanceSensor sensorArr[] = {
  DistanceSensor(S_Trig[0], S_Echo[0]),
  DistanceSensor(S_Trig[1], S_Echo[1]),
  DistanceSensor(S_Trig[2], S_Echo[2]),
  DistanceSensor(S_Trig[3], S_Echo[3])
};

SensorArray sensorArray_LED = SensorArray();

//WiFi vars
char ssid[] = SECRET_SSID;
WifiConnection wifiConnection_HTTP(ssid);

// static boolean toggle = true;
// static boolean tmp = toggle;
bool is_reserved[4] = { 0, 0, 0, 0 };
volatile bool timerFlag = false;

void setup() {
  Serial.begin(9600);
  delay(5000);
  // Sensor Pin mode
  sensorArray_LED.SensorSetup(S_Trig, S_Echo);
  //RGB LED Pin Mode
  sensorArray_LED.LEDsetup();

  // Take initial measurements
  for (int i = 0; i < 4; i++) {
    sensorArray_LED.setStatus(sensorArr[i], i);
  }

  // Wifi connection
  Serial.println("WiFi connection begin");
  wifiConnection_HTTP.begin();
  //Interrupt Setup
  interruptSetup();
}

void loop() {

  bool* is_occupied_arr = sensorArray_LED.getStatus();
  // Make a POST request and handle setting LEDs
  if (timerFlag) {
    timerFlag = false;
    // is_reserved = wifiConnection_HTTP.serverUpdateSpot(/*test_status -- TODO: figure out how to */, 1);  // post request posts the sensor data to a spot
    // is_reserved = wifiConnection_HTTP.serverUpdateSpot(is_occupied_arr, /*TODO:*/{ 1, 2, 3, 4 });  // post request posts the sensor data to a spot

  }

  // Take measurements and print their values
  for (int i = 0; i < 4; i++) {
    char distPrint[100];
    sprintf(distPrint, "avgDist %d:", i + 1);
    Serial.print(distPrint);
    sensorArray_LED.setStatus(sensorArr[i], i);
    delay(1000);//Eventually delete but for troubleshooting leave
  }

  is_occupied_arr = sensorArray_LED.getStatus();
  for (int i = 0; i < 4; i++) {
    if (is_reserved[i] == 1) {        // checks if the server has the spot reserved
      sensorArray_LED.setLED(i, 2);   // if the spot is reserved then turn yellow
    } else if (is_occupied_arr[i]) {  //checks if our system has the spot as occupied or open
      sensorArray_LED.setLED(i, 1);   //if the spot is occupied turn red
    } else {
      sensorArray_LED.setLED(i, 0);  //if the spot is open turn green
    }
    delay(500); //Eventually delete but for troubleshooting leave
  }

  /****************** Everything below this line is unofficial and subject to deletion in loop() ******************/
  // is_reserved = wifiConnection_HTTP.serverUpdateSpot(test_status, 1);  // post request posts the sensor data to a spot

  // And just stop, now that we've tried a download
  // while (1)
  //   ;
  
}

/************************** Interrupt Setup and Handling **********************************/
void interruptSetup() {
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN |  // Set GCLK0 (48MHz) as clock source for timer TC3
                      GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3;

  TC3->COUNT16.CTRLA.reg = TC_CTRLA_PRESCSYNC_PRESC |    // Wrap around on next prescaler clock
                           TC_CTRLA_PRESCALER_DIV1024 |  // Set prescaler to 1024, 48MHz/1024 = 46.875kHz
                           TC_CTRLA_WAVEGEN_MFRQ;        // Put the timer TC3 into match frequency (MFRQ) mode

  TC3->COUNT16.CC[0].reg = 46874;  // 1Hz: 48MHz /(1024 * 1Hz) - 1 = 46874
  while (TC3->COUNT16.STATUS.bit.SYNCBUSY && wifiConnection_HTTP.status != WL_CONNECTED)
    ;  // Wait for synchronization

  NVIC_SetPriority(TC3_IRQn, 0);  // Set the Nested Vector Interrupt Controller (NVIC) priority for TC3 to 0 (highest)
  NVIC_EnableIRQ(TC3_IRQn);       // Connect TC3 to Nested Vector Interrupt Controller (NVIC)

  TC3->COUNT16.INTENSET.reg = TC_INTENSET_OVF;  // Enable TC3 overflow interrupts

  TC3->COUNT16.CTRLA.bit.ENABLE = 1;  // Enable TC3

  while (TC3->COUNT16.STATUS.bit.SYNCBUSY)
    ;  // Wait for synchronization
}

void TC3_Handler()  // Interrupt Service Routine (ISR) for timer TC3
{
  if (TC3->COUNT16.INTFLAG.bit.OVF)  // Check for overflow (OVF) interrupt
  {
    TC3->COUNT16.INTFLAG.bit.OVF = 1;  // Clear the OVF interrupt flag
    // Put your timer overflow (OVF) code here...
    timerFlag = true;
  }
}
