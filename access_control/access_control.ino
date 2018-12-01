#include <Wire.h>
#include <RTClib.h>

// RTC type declaration
RTC_DS1307 RTC;

// PINS
const int insideLaser = 6;
const int outsideLaser = 9;
const int outsideSensor = 3;
const int insideSensor = 4;

// GLOBAL VARIABLES
int firstSensor = 0;
int secondSensor = 0;
int lastActivated = 0;
int activated = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //RTC.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  
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

  if (inside == 0 and outside == 0 and lastActivated == 0) return;
  
  if (inside == 1 and lastActivated == 0){
    lastActivated = 1;
    return;
  }
  else if (outside == 1 and lastActivated == 0){
    lastActivated = 2;
    return;
  }
  else if (lastActivated != 0 and inside == 0 and outside == 0){
    activated = lastActivated;
    lastActivated = 0;
  } 
  else return;
    
    
  if (firstSensor == 0) 
    firstSensor = activated;
  else if (activated != firstSensor and secondSensor == 0) {
    secondSensor = activated;
    DateTime rtcTime = RTC.now();
    Serial.println("{\"direction\": \"" + getDirection(firstSensor, secondSensor) + "\", \"date\": \"" + getDate(rtcTime) + "\", \"time\": \"" + getTime(rtcTime) + "\", \"quantity\": \"1\"}");
    firstSensor = 0;
    secondSensor = 0;
    activated = 0;
    lastActivated = 0;
  }
    
}

String getDirection(int first, int second) {
  if (first == 1 and second == 2)
    return "E"; //entrada
  else 
    return "S"; //saída
}

String getDate(DateTime now) {
  String dateStr;
  //dateStr = String(now.year()) + '-' + String(now.month()) + '-' + String(now.day());
  dateStr = "2018-12-01";
  return dateStr;  
}

String getTime(DateTime now) {
  String timeStr;
  //timeStr = String(now.hour()) + ':' + String(now.minute()) + ':' + String(now.second());
  timeStr = "12:01:23";
  return timeStr;  
}
