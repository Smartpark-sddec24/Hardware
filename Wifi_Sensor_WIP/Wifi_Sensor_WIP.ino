#include "WifiConnection.h"
#include "SensorArray.h"
#include "arduino_secrets.h"
#include <DistanceSensor.h>  //Library by Segilmez06
#include <ArduinoHttpClient.h>
#include <string.h>
#include <TimerOne.h>

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

// //WiFi vars
char ssid[] = SECRET_SSID;
WifiConnection wifiConnection_HTTP(ssid);

// static boolean toggle = true;
// static boolean tmp = toggle;

void setup() {
  Serial.begin(9600);
  delay(5000);
  // Sensor Pin mode
  sensorArray_LED.SensorSetup(S_Trig, S_Echo);
  //RGB LED Pin Mode
  sensorArray_LED.LEDsetup();
  // Wifi connection
  Serial.println("WiFi connection begin");
  wifiConnection_HTTP.begin();
  //Interrupt Setup
  // interruptSetup();
}

void loop() {
  // wifiConnection.wifiInfo();

  for (int i = 0; i < 4; i++) {
    sensorArray_LED.setStatus(sensorArr[i], i);
    delay(5000);

    Serial.print("Status: ");

    Serial.println(sensorArray_LED.getStatus(i));             // gets the status of a spot (open, occupied)
    sensorArray_LED.setLED(i, sensorArray_LED.getStatus(i));  //sets the LED to the correct color. Eventually will use serverGetStatus instead of getStatus
    delay(5000);

    // wifiConnection_HTTP.serverGetStatus(); //serverGetStatus returns a number value to use in setLED()

    // wifiConnection_HTTP.serverUpdateSpot(sensorArrayLIB.getStatus(i), i); // post request posts the sensor data to a spot

    // Set timer TC3 to call the TC3_Handler at 1Hz
  }
}



/************************** Interrupt Setup and Handling **********************************/
// void interruptSetup() {
//   GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN |  // Set GCLK0 (48MHz) as clock source for timer TC3
//                       GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3;

//   TC3->COUNT16.CTRLA.reg = TC_CTRLA_PRESCSYNC_PRESC |    // Wrap around on next prescaler clock
//                            TC_CTRLA_PRESCALER_DIV1024 |  // Set prescaler to 1024, 48MHz/1024 = 46.875kHz
//                            TC_CTRLA_WAVEGEN_MFRQ;        // Put the timer TC3 into match frequency (MFRQ) mode

//   TC3->COUNT16.CC[0].reg = 5000;  // 5Hz: 48MHz /(1024 * 5Hz) - 1 = 9374
//   while (TC3->COUNT16.STATUS.bit.SYNCBUSY)
//     ;  // Wait for synchronization

//   NVIC_SetPriority(TC3_IRQn, 0);  // Set the Nested Vector Interrupt Controller (NVIC) priority for TC3 to 0 (highest)
//   NVIC_EnableIRQ(TC3_IRQn);       // Connect TC3 to Nested Vector Interrupt Controller (NVIC)

//   TC3->COUNT16.INTENSET.reg = TC_INTENSET_OVF;  // Enable TC3 overflow interrupts

//   TC3->COUNT16.CTRLA.bit.ENABLE = 1;  // Enable TC3
//   while (TC3->COUNT16.STATUS.bit.SYNCBUSY)
//     ;  // Wait for synchronization
// }

// void loop() {
// Serial.print(toggle);
// Serial.print("\n");
// }

// void TC3_Handler()  // Interrupt Service Routine (ISR) for timer TC3
// {
//   if (TC3->COUNT16.INTFLAG.bit.OVF)  // Check for overflow (OVF) interrupt
//   {
//     TC3->COUNT16.INTFLAG.bit.OVF = 1;  // Clear the OVF interrupt flag
//     // Put your timer overflow (OVF) code here...
//     for (int i = 0; i < 4; i++) {
//       sensorArray_LED.setStatus(sensorArr[i], i);
//       delay(5000);

//       Serial.print("Status: ");

//       Serial.println(sensorArray_LED.getStatus(i));  // gets the status of a spot (open, occupied)
//       sensorArray_LED.setLED(i, sensorArray_LED.getStatus(i));
//     }
//   }
// }

// FQBN: arduino:samd:nano_33_iot
// Using board 'nano_33_iot' from platform in folder: C:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14
// Using core 'arduino' from platform in folder: C:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14

// Detecting libraries used...
// C:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\arm-none-eabi-gcc\7-2017q4/bin/arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -w -x c++ -E -CC -DF_CPU=48000000L -DARDUINO=10607 -DARDUINO_SAMD_NANO_33_IOT -DARDUINO_ARCH_SAMD -DCRYSTALLESS -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8057 -DUSBCON -DUSB_MANUFACTURER="Arduino LLC" -DUSB_PRODUCT="Arduino NANO 33 IoT" -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS\4.5.0/CMSIS/Include/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS-Atmel\1.2.0/CMSIS/Device/ATMEL/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated-avr-comp -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\variants\nano_33_iot C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\Wifi_Sensor_WIP.ino.cpp -o nul
// Alternatives for WiFiNINA.h: [WiFiNINA@1.8.14]
// ResolveLibrary(WiFiNINA.h)
//   -> candidates: [WiFiNINA@1.8.14]
// C:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\arm-none-eabi-gcc\7-2017q4/bin/arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -w -x c++ -E -CC -DF_CPU=48000000L -DARDUINO=10607 -DARDUINO_SAMD_NANO_33_IOT -DARDUINO_ARCH_SAMD -DCRYSTALLESS -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8057 -DUSBCON -DUSB_MANUFACTURER="Arduino LLC" -DUSB_PRODUCT="Arduino NANO 33 IoT" -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS\4.5.0/CMSIS/Include/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS-Atmel\1.2.0/CMSIS/Device/ATMEL/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated-avr-comp -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\variants\nano_33_iot -IC:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\Wifi_Sensor_WIP.ino.cpp -o nul
// Alternatives for DistanceSensor.h: [DistanceSensor@1.0.2]
// ResolveLibrary(DistanceSensor.h)
//   -> candidates: [DistanceSensor@1.0.2]
// C:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\arm-none-eabi-gcc\7-2017q4/bin/arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -w -x c++ -E -CC -DF_CPU=48000000L -DARDUINO=10607 -DARDUINO_SAMD_NANO_33_IOT -DARDUINO_ARCH_SAMD -DCRYSTALLESS -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8057 -DUSBCON -DUSB_MANUFACTURER="Arduino LLC" -DUSB_PRODUCT="Arduino NANO 33 IoT" -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS\4.5.0/CMSIS/Include/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS-Atmel\1.2.0/CMSIS/Device/ATMEL/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated-avr-comp -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\variants\nano_33_iot -IC:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src -IC:\Users\sears\Documents\Arduino\libraries\DistanceSensor\src C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\Wifi_Sensor_WIP.ino.cpp -o nul
// Alternatives for ArduinoHttpClient.h: [ArduinoHttpClient@0.6.1]
// ResolveLibrary(ArduinoHttpClient.h)
//   -> candidates: [ArduinoHttpClient@0.6.1]
// C:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\arm-none-eabi-gcc\7-2017q4/bin/arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -w -x c++ -E -CC -DF_CPU=48000000L -DARDUINO=10607 -DARDUINO_SAMD_NANO_33_IOT -DARDUINO_ARCH_SAMD -DCRYSTALLESS -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8057 -DUSBCON -DUSB_MANUFACTURER="Arduino LLC" -DUSB_PRODUCT="Arduino NANO 33 IoT" -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS\4.5.0/CMSIS/Include/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS-Atmel\1.2.0/CMSIS/Device/ATMEL/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated-avr-comp -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\variants\nano_33_iot -IC:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src -IC:\Users\sears\Documents\Arduino\libraries\DistanceSensor\src -IC:\Users\sears\Documents\Arduino\libraries\ArduinoHttpClient\src C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\Wifi_Sensor_WIP.ino.cpp -o nul
// Using cached library dependencies for file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\SensorArray.cpp
// Using cached library dependencies for file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\WifiConnection.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\WiFi.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\WiFiClient.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\WiFiSSLClient.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\WiFiServer.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\WiFiStorage.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\WiFiUdp.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\utility\WiFiSocketBuffer.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\utility\nano_rp2040_support.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\utility\server_drv.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\utility\spi_drv.cpp
// Alternatives for SPI.h: [SPI@1.0]
// ResolveLibrary(SPI.h)
//   -> candidates: [SPI@1.0]
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src\utility\wifi_drv.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\DistanceSensor\src\DistanceSensor.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\ArduinoHttpClient\src\HttpClient.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\ArduinoHttpClient\src\URLEncoder.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\ArduinoHttpClient\src\WebSocketClient.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\ArduinoHttpClient\src\b64.cpp
// Using cached library dependencies for file: C:\Users\sears\Documents\Arduino\libraries\ArduinoHttpClient\src\utility\URLParser\http_parser.c
// Using cached library dependencies for file: C:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\libraries\SPI\SPI.cpp
// Generating function prototypes...
// C:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\arm-none-eabi-gcc\7-2017q4/bin/arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -w -x c++ -E -CC -DF_CPU=48000000L -DARDUINO=10607 -DARDUINO_SAMD_NANO_33_IOT -DARDUINO_ARCH_SAMD -DCRYSTALLESS -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8057 -DUSBCON -DUSB_MANUFACTURER="Arduino LLC" -DUSB_PRODUCT="Arduino NANO 33 IoT" -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS\4.5.0/CMSIS/Include/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\CMSIS-Atmel\1.2.0/CMSIS/Device/ATMEL/ -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino/api/deprecated-avr-comp -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\cores\arduino -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\variants\nano_33_iot -IC:\Users\sears\Documents\Arduino\libraries\WiFiNINA\src -IC:\Users\sears\Documents\Arduino\libraries\DistanceSensor\src -IC:\Users\sears\Documents\Arduino\libraries\ArduinoHttpClient\src -IC:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\libraries\SPI C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\Wifi_Sensor_WIP.ino.cpp -o C:\Users\sears\AppData\Local\Temp\2293771967\sketch_merged.cpp
// C:\Users\sears\AppData\Local\Arduino15\packages\builtin\tools\ctags\5.8-arduino11/ctags -u --language-force=c++ -f - --c++-kinds=svpf --fields=KSTtzns --line-directives C:\Users\sears\AppData\Local\Temp\2293771967\sketch_merged.cpp
// Compiling sketch...
// "C:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\arm-none-eabi-gcc\\7-2017q4/bin/arm-none-eabi-g++" -mcpu=cortex-m0plus -mthumb -c -g -Os -w -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD -DF_CPU=48000000L -DARDUINO=10607 -DARDUINO_SAMD_NANO_33_IOT -DARDUINO_ARCH_SAMD -DCRYSTALLESS -D__SAMD21G18A__ -DUSB_VID=0x2341 -DUSB_PID=0x8057 -DUSBCON "-DUSB_MANUFACTURER=\"Arduino LLC\"" "-DUSB_PRODUCT=\"Arduino NANO 33 IoT\"" "-IC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\CMSIS\\4.5.0/CMSIS/Include/" "-IC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\CMSIS-Atmel\\1.2.0/CMSIS/Device/ATMEL/" "-IC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\samd\\1.8.14\\cores\\arduino/api/deprecated" "-IC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\samd\\1.8.14\\cores\\arduino/api/deprecated-avr-comp" "-IC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\samd\\1.8.14\\cores\\arduino" "-IC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\samd\\1.8.14\\variants\\nano_33_iot" "-IC:\\Users\\sears\\Documents\\Arduino\\libraries\\WiFiNINA\\src" "-IC:\\Users\\sears\\Documents\\Arduino\\libraries\\DistanceSensor\\src" "-IC:\\Users\\sears\\Documents\\Arduino\\libraries\\ArduinoHttpClient\\src" "-IC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\samd\\1.8.14\\libraries\\SPI" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\sketch\\Wifi_Sensor_WIP.ino.cpp" -o "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\sketch\\Wifi_Sensor_WIP.ino.cpp.o"
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\SensorArray.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\sketch\WifiConnection.cpp.o
// Compiling libraries...
// Compiling library "WiFiNINA"
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\utility\WiFiSocketBuffer.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\utility\nano_rp2040_support.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\utility\server_drv.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\utility\wifi_drv.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\WiFiSSLClient.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\WiFiClient.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\WiFiServer.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\utility\spi_drv.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\WiFi.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\WiFiStorage.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\WiFiNINA\WiFiUdp.cpp.o
// Compiling library "DistanceSensor"
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\DistanceSensor\DistanceSensor.cpp.o
// Compiling library "ArduinoHttpClient"
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\ArduinoHttpClient\utility\URLParser\http_parser.c.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\ArduinoHttpClient\b64.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\ArduinoHttpClient\HttpClient.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\ArduinoHttpClient\WebSocketClient.cpp.o
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\ArduinoHttpClient\URLEncoder.cpp.o
// Compiling library "SPI"
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\libraries\SPI\SPI.cpp.o
// Compiling core...
// Using previously compiled file: C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6\core\variant.cpp.o
// Using precompiled core: C:\Users\sears\AppData\Local\Temp\arduino\cores\arduino_samd_nano_33_iot_1afea033f3b154916cfbd0f59840e7d4\core.a
// Linking everything together...
// "C:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\arm-none-eabi-gcc\\7-2017q4/bin/arm-none-eabi-g++" "-LC:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6" -Os -Wl,--gc-sections -save-temps "-TC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\samd\\1.8.14\\variants\\nano_33_iot/linker_scripts/gcc/flash_with_bootloader.ld" "-Wl,-Map,C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6/Wifi_Sensor_WIP.ino.map" --specs=nano.specs --specs=nosys.specs -mcpu=cortex-m0plus -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -o "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6/Wifi_Sensor_WIP.ino.elf" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\sketch\\SensorArray.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\sketch\\WifiConnection.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\sketch\\Wifi_Sensor_WIP.ino.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\WiFi.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\WiFiClient.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\WiFiSSLClient.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\WiFiServer.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\WiFiStorage.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\WiFiUdp.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\utility\\WiFiSocketBuffer.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\utility\\nano_rp2040_support.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\utility\\server_drv.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\utility\\spi_drv.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\WiFiNINA\\utility\\wifi_drv.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\DistanceSensor\\DistanceSensor.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\ArduinoHttpClient\\HttpClient.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\ArduinoHttpClient\\URLEncoder.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\ArduinoHttpClient\\WebSocketClient.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\ArduinoHttpClient\\b64.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\ArduinoHttpClient\\utility\\URLParser\\http_parser.c.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\libraries\\SPI\\SPI.cpp.o" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6\\core\\variant.cpp.o" -Wl,--start-group "-LC:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\CMSIS\\4.5.0/CMSIS/Lib/GCC/" -larm_cortexM0l_math -lm "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6/..\\..\\cores\\arduino_samd_nano_33_iot_1afea033f3b154916cfbd0f59840e7d4\\core.a" -Wl,--end-group
// "C:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\arm-none-eabi-gcc\\7-2017q4/bin/arm-none-eabi-objcopy" -O binary "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6/Wifi_Sensor_WIP.ino.elf" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6/Wifi_Sensor_WIP.ino.bin"
// "C:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\arm-none-eabi-gcc\\7-2017q4/bin/arm-none-eabi-objcopy" -O ihex -R .eeprom "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6/Wifi_Sensor_WIP.ino.elf" "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6/Wifi_Sensor_WIP.ino.hex"

// Using library WiFiNINA at version 1.8.14 in folder: C:\Users\sears\Documents\Arduino\libraries\WiFiNINA
// Using library DistanceSensor at version 1.0.2 in folder: C:\Users\sears\Documents\Arduino\libraries\DistanceSensor
// Using library ArduinoHttpClient at version 0.6.1 in folder: C:\Users\sears\Documents\Arduino\libraries\ArduinoHttpClient
// Using library SPI at version 1.0 in folder: C:\Users\sears\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.8.14\libraries\SPI
// "C:\\Users\\sears\\AppData\\Local\\Arduino15\\packages\\arduino\\tools\\arm-none-eabi-gcc\\7-2017q4/bin/arm-none-eabi-size" -A "C:\\Users\\sears\\AppData\\Local\\Temp\\arduino\\sketches\\BDF326A815C6F59912C3D0B196A176C6/Wifi_Sensor_WIP.ino.elf"
// Sketch uses 39128 bytes (14%) of program storage space. Maximum is 262144 bytes.
// Global variables use 4588 bytes (14%) of dynamic memory, leaving 28180 bytes for local variables. Maximum is 32768 bytes.
// Performing 1200-bps touch reset on serial port COM8
// Waiting for upload port...
// No upload port found, using COM8 as fallback
// "C:\Users\sears\AppData\Local\Arduino15\packages\arduino\tools\bossac\1.7.0-arduino3/bossac.exe" -i -d --port=COM8 -U true -i -e -w -v "C:\Users\sears\AppData\Local\Temp\arduino\sketches\BDF326A815C6F59912C3D0B196A176C6/Wifi_Sensor_WIP.ino.bin" -R
