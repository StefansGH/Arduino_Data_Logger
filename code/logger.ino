#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

const int redSensorPin = A0;  // pin with the photoresistor with the red gel
int redSensorValue = 0; // variable to hold the value from the red sensor

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
}

void loop() {
  tmElements_t tm;

  redSensorValue = analogRead(redSensorPin);
  delay(5);
  
  if (RTC.read(tm)) {
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.write('-'); 
    Serial.print(tm.Month);
    Serial.write('-'); 
    Serial.print(tm.Day);
    Serial.write(' ');         
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.write(',');
    //Serial.print();
    Serial.print(redSensorValue);
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
   
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
