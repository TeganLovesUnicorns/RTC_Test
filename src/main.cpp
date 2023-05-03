#include <Arduino.h>
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include<Adafruit_BusIO_Register.h>


RTC_DS3231 RTC;


void setup () {


  Serial.begin(57600); // Begins Serial feed to commandline monitor
  Wire.begin(); //Activiates I2C communication bus
  RTC.begin(); //Initializes the defined RTC unit

  // RTC.adjust(DateTime(__DATE__, __TIME__)); // Uncomment this to set time for RTC to system time at the moment code was compiled

  RTC.writeSqwPinMode(DS3231_OFF); //Sets SQW pin output, in this case to off. Check library's .h for other possible settings.
  RTC.disable32K(); //Sets External 32k output pin output, in to off. Check library's .h for other possible settings.
  // RTC.enable32K(); //(NOT RECOMMENDED) Enable this if you want to read the 32k raw output off the OSC.
  
  delay(250);

  if (RTC.readSqwPinMode() == 28) //Displays status of RTC's SQW output pin in Serial
  {
    Serial.println("RTC's SQW output is disabled");
  }
  else{
    Serial.println("RTC's SQW Output is enabled");
  }
  
  if (RTC.isEnabled32K() == 0)    //Displays status of RTC's 32K output pin in Serial
  {
    Serial.println("RTC's 32k output is disabled");
  }
  else{
    Serial.println("RTC's 32k Output is enabled");
  }
  
  if (RTC.lostPower() == 1)       //Displays status of RTC's battery in Serial, assumes that if battery dead or missing and clock loses power this will true.
  {
    Serial.println("RTC chip lost power... check battery");
  }
  else{
    Serial.println("RTC chip has not lost power, batt is good");
  }
  
  delay(2000);
}


byte lastSec=0;
void loop () 
{
  DateTime now = RTC.now();
  if(lastSec!=now.second())
  {lastSec=now.second();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }
}