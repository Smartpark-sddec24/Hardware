// #include "WifiConnection.h"
// #include "SensorArray.h"
// #include "arduino_secrets.h"
// #include <DistanceSensor.h>  //Library by Segilmez06
// #include <ArduinoHttpClient.h>
// #include <string.h>

// //Distance Sensors
// int S_Trig[] = { 5, 7, 9, 11 };
// int S_Echo[] = { 6, 8, 10, 12 };
// DistanceSensor sensorArr[] = {
//   DistanceSensor(S_Trig[0], S_Echo[0]),
//   DistanceSensor(S_Trig[1], S_Echo[1]),
//   DistanceSensor(S_Trig[2], S_Echo[2]),
//   DistanceSensor(S_Trig[3], S_Echo[3])
// };

// SensorArray sensorArray_LED = SensorArray();

// // //WiFi vars
// char ssid[] = SECRET_SSID;
// WifiConnection wifiConnection_HTTP(ssid);

// void setup() {
//   Serial.begin(9600);
//   delay(5000);
//   // Sensor Pin mode
//   sensorArray_LED.SensorSetup(S_Trig, S_Echo);
//   //RGB LED Pin Mode
//   sensorArray_LED.LEDsetup();
//   // Wifi connection
//   Serial.println("WiFi connection begin");
//   // wifiConnection_HTTP.begin();
// }


// void loop() {
//   // wifiConnection.wifiInfo();

//   for (int i = 0; i < 4; i++) {
//     sensorArray_LED.setStatus(sensorArr[i], i);
//     delay(5000);

//     Serial.print("Status: ");

//     Serial.println(sensorArray_LED.getStatus(i));            // gets the status of a spot (open, occupied)
//     sensorArray_LED.setLED(i, sensorArray_LED.getStatus(i));  //sets the LED to the correct color. Eventually will use serverGetStatus instead of getStatus
//     delay(5000);
//   }


//   // wifiConnection_HTTP.serverGetStatus(); //serverGetStatus returns a number value to use in setLED()

//   // wifiConnection_HTTP.serverUpdateSpot(sensorArrayLIB.getStatus(i), i); // post request posts the sensor data to a spot


//   // And just stop, now that we've tried a download
//   while (1)
//     ;
// }
// Set timer TC3 to call the TC3_Handler at 1Hz

static boolean toggle = true;
static boolean tmp = toggle;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN |        // Set GCLK0 (48MHz) as clock source for timer TC3
                      GCLK_CLKCTRL_GEN_GCLK0 |    
                      GCLK_CLKCTRL_ID_TCC2_TC3;    
  
  TC3->COUNT16.CTRLA.reg = //TC_CTRLA_PRESCSYNC_PRESC |    // Wrap around on next prescaler clock                          
                           //TC_CTRLA_PRESCALER_DIV1024 |  // Set prescaler to 1024, 48MHz/1024 = 46.875kHz                          
                           TC_CTRLA_WAVEGEN_MFRQ;        // Put the timer TC3 into match frequency (MFRQ) mode
  
  // TC3->COUNT16.CC[0].reg = 46874;                 // Set the TC3 period to 1Hz: 48MHz / (1024 * 1Hz) - 1 = 46874
  // TC3->COUNT16.CC[0].reg = 9599;                  // Set the TC3 period to 5kHz: 48MHz / (1 * 5000Hz) - 1 = 9599
  TC3->COUNT16.CC[0].reg = 9600000;                  // 5Hz: 48MHz /(1 * 5Hz) - 1 = 9600000
  while (TC3->COUNT16.STATUS.bit.SYNCBUSY);       // Wait for synchronization

  NVIC_SetPriority(TC3_IRQn, 0);    // Set the Nested Vector Interrupt Controller (NVIC) priority for TC3 to 0 (highest)
  NVIC_EnableIRQ(TC3_IRQn);         // Connect TC3 to Nested Vector Interrupt Controller (NVIC)

  TC3->COUNT16.INTENSET.reg = TC_INTENSET_OVF;    // Enable TC3 overflow interrupts
 
  TC3->COUNT16.CTRLA.bit.ENABLE = 1;              // Enable TC3                
  while (TC3->COUNT16.STATUS.bit.SYNCBUSY);       // Wait for synchronization
}

void loop() {
  Serial.print(toggle);
  Serial.print("\n");
}

void TC3_Handler()                                // Interrupt Service Routine (ISR) for timer TC3
{  
  if (TC3->COUNT16.INTFLAG.bit.OVF)               // Check for overflow (OVF) interrupt     
  {
    TC3->COUNT16.INTFLAG.bit.OVF = 1;             // Clear the OVF interrupt flag
    // Put your timer overflow (OVF) code here...   
    digitalWrite(LED_BUILTIN, toggle);
    toggle = !toggle;
  }
}