#include <Time.h>
#include <TimeLib.h>
#include <DS1302RTC.h>

// Set pins:  RST, DAT,CLK
DS1302RTC RTC(2, 8, 7);



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

  // UNIX Timestamp
//   RTC.set(1544264040); // Time = 10:14:00, Date (D/M/Y) = 8/12/2018, DoW = 7

  
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

    tmElements_t tm;

    

    if (! RTC.read(tm)){
      Serial.println("{\"direction\": \"" + getDirection(firstSensor, secondSensor) + "\", \"date\": \"" + getDate(tm) + "\", \"time\": \"" + getTime(tm) + "\", \"quantity\": \"1\"}");
    }
//Serial.println(tm.Hour);
    
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

String getDate(tmElements_t tmNow) {
  String dateStr;
  dateStr = String(tmNow.Year + 1970) + '-' + parseTwoDigits(String(tmNow.Month)) + '-' + parseTwoDigits(String(tmNow.Day));
  //dateStr = "2018-12-01";
  return dateStr;  
}

String getTime(tmElements_t tmNow) {
  String timeStr;
  timeStr = parseTwoDigits(String(tmNow.Hour)) + ':' + parseTwoDigits(String(tmNow.Minute)) + ':' + parseTwoDigits(String(tmNow.Second));
//  timeStr = "12:01:23";
  return timeStr;  
}

String parseTwoDigits(String digit){
  if (digit.length() > 1) return digit;

  return '0' + digit;
}
