#include "Arduino.h"
#include "SensorArray.h"
#include <DistanceSensor.h>

//LED Pin Assignments
//          R, G, B
// LED1 = [A0,A1,A2]
// LED2 = [A3,A4,A5]
// LED3 = [A6,A7,D13]
// LED1 = [D4,D3,D2]
int redPin[] = { 14, 17, 20, 4 };    //[A0,A3,A6,D4]
int greenPin[] = { 15, 18, 21, 3 };  //[A1,A4,A7,D3]
int bluePin[] = { 16, 19, 13, 2 };   //[A2,A5,D13,D2]


SensorArray ::SensorArray() {
  for (int i = 0; i < 3; i++) {
    spotStatus[i] = false;
  }
}

// NOTE: Removed averageMeasurement function modified setStatus to include this averaging functionality
//TODO: Rip out averaging measurement here and put it into the main file loop
void SensorArray ::setStatus(DistanceSensor sensor, int statusIndex) {
  int measurements = 10;
  float avgDist = 0;

  for (int i = 0; i < measurements; i++) {
    avgDist += sensor.getCM();
  }
  avgDist /= measurements;
  
  Serial.print("Average distance: ");
  Serial.println(avgDist);
  if (avgDist <= 70.0) {
    spotStatus[statusIndex] = 1;
  } else {
    spotStatus[statusIndex] = 0;
  }
}

bool* SensorArray ::getStatus(){
  return spotStatus;
}

void SensorArray ::SensorSetup(int trigPins[], int echoPins[]) {
  //RGB LED Pin Mode
  for (int i = 0; i < 4; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
}

// LED ---------------------------
void SensorArray ::LEDsetup() {
  //RGB LED Pin Mode
  for (int i = 0; i < 4; i++) {
    pinMode(redPin[i], OUTPUT);
    pinMode(greenPin[i], OUTPUT);
    pinMode(bluePin[i], OUTPUT);
  }
}
void SensorArray ::setLED(int index, int status) {
  if (status == 0) {
    // Serial.println("green");
    setColor(0, 255, 0, index);  //Green
  } else if (status == 1) {
    // Serial.println("red");
    setColor(255, 0, 0, index);  //Red
  } else {
    // Serial.println("yellow");
    setColor(255, 255, 0, index);  //yellow
  }
}

void SensorArray ::setColor(int redValue, int greenValue, int blueValue, int index) {
  //Writing to LED
  digitalWrite(redPin[index], redValue);
  digitalWrite(greenPin[index], greenValue);
  digitalWrite(bluePin[index], blueValue);
}
