/*
 * sensores laser com RTC
 * 
 */

#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

// PINS
const int insideLaser = 6;
const int outsideLaser = 9;
const int outsideSensor = 7;
const int insideSensor = 8;

// GLOBAL VARIABLES
int firstSensor = 0;
int secondSensor = 0;
int lastActivated = 0;
int activated = 0;
bool standby = true;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  pinMode(outsideLaser, OUTPUT);
  pinMode(insideLaser, OUTPUT);
  pinMode(outsideSensor, INPUT);
  pinMode(insideSensor, INPUT);
  
  digitalWrite(outsideLaser, HIGH);
  digitalWrite(insideLaser, HIGH);
}

void loop() {

  int inside = !digitalRead(insideSensor);
  int outside = !digitalRead(outsideSensor);

  if (inside == 0 and outside == 0) {
    standby = true;
    if (secondSensor != 0 and firstSensor != 0) {
      firstSensor = 0;
      secondSensor = 0;
      activated = 0;
      lastActivated = 0;
    }
    return;
  } else 
    standby = false;
  
  if (inside == 1)
    activated = 1;
  else if (outside == 1)
    activated = 2;

  if (firstSensor == 0) 
    firstSensor = activated;
  else if (activated != firstSensor and secondSensor == 0) {
    secondSensor = activated;
    
    Serial.println(getDirection(firstSensor, secondSensor) + ' ' + getTime());
  }
    
}

String getDirection(int first, int second) {
  if (first == 1 and second == 2)
    return "i";
  else 
    return "o";
}

String getTime() {
  String dateStr;
  String timeStr;

  DateTime now = RTC.now();

  dateStr = String(now.year()) + '-' + String(now.month()) + '-' + String(now.day());
  timeStr = String(now.hour()) + ':' + String(now.minute()) + ':' + String(now.second());

  return dateStr + ' ' + timeStr;  
}


