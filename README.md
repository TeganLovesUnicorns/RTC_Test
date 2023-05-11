RTC TEST 
======

## Objective
This project is for the initial setup and testing of a DS3231 RTC chip. You can find DS3231 breakout boards for a decent price online.

**NOTE:** A lot of the breakouts for this chip that you find online will say that they are compatible with the CR2032 coin battery. This is only true if the diode and resistor for the battery charge circuit are removed, rendering that "feature" disabled. It was a very crude way to charge a li-po battery and will cause fires with a regular CR2032.

**_YOU HAVE BEEN WARNED..._**

## The Hardware
For this project I used an Arduino Mega 2560, but you can use any micro controller that supports Arduino's version of C++ such as an Expressif ESP32 chipset or an Arduino Uno. The DS3231 communicates on the I2C bus so just be aware of that if you have other I2C devices you're planning on using.

**NOTE:** Please check with the specs of the RTC Breakout and your microcontroller to make sure that you don't overwhelm the circuits on you microcontroller with too much voltage. (*Don't let the magic smoke out of your components*)

## The Program

This program is written in the Platformio IDE for VS Code. Here are links to their sites. https://platformio.org/ and https://code.visualstudio.com/

### Setup

First we added all the library includes to use Arduino, I2C and the RTC. I used the library that had already been written by Adafruit for varius RTC chips including this one.

After that we run the setup code. after the initializing statements you will see this commented out code.
```c++
  // RTC.adjust(DateTime(__DATE__, __TIME__)); // Uncomment this to set time for RTC to system time at the moment code was compiled
```
This code is there for when you are first testing an RTC. This grabs the system time from when the code was compiled and then updates the chips memory with that. Please note that you may want to comment this code out after the first test so that you don't reset your clock on a reset of the microcontroller.


In the code below I put in the functions from the RTC library to disable certain parts of the RTC that I don't plan on using, such as the Square Wave output as well as the raw oscilator signal. Feel free to comment in and out the functions that suit your project's needs.
```c++
  RTC.writeSqwPinMode(DS3231_OFF); //Sets SQW pin output, in this case to off. Check library's .h for other possible settings.
  // RTC.writeSqwPinMode(DS3231_SquareWave1Hz); // Sets the SQW output to 1hz.
  // RTC.writeSqwPinMode(DS3231_SquareWave1kHz); // Sets the SQW output to 1khz.
  // RTC.writeSqwPinMode(DS3231_SquareWave4kHz); // Sets the SQW output to 4khz.
  // RTC.writeSqwPinMode(DS3231_SquareWave8kHz); // Sets the SQW output to 8khz. 

  RTC.disable32K(); //Sets External 32k output pin output, in to off. Check library's .h for other possible settings.
  // RTC.enable32K(); //(NOT RECOMMENDED) Enable this if you want to read the 32k raw output off the OSC.
  ```

  after that code I put some if statements. These statements use functions from the RTC library to query the chip as to whether or not our settings took and then display that information in a human readable format into the serial monitor. Please note that I only wrote the if statements to suit my needs if you require your situation to be in a human readable format, please add and test that code to this sketch and contribute back to the community.

  ### Loop
  The loop is pretty straight forward. In this sketch it basically keeps asking the RTC if the time has changed and then, when it does, it will update the serial monitor. Now this will cause the RTC chip to slightly warm up, but it has built in temperature compensation and shouldn't really have an issue.