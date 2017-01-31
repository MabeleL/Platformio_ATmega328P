/* Temperature sensor and Light sensor code on ATmega328P using platformio                   */

#include "Arduino.h"
#include <LiquidCrystal.h>
#include <stdio.h>

//const int gasPin = A4; //GAS sensor output pin to Arduino analog A4 pin
const int LightPin = A1;  //Light sensor pin
const int TempPin = A0;   // Temperature sensor code
int thresholdValue = 700;  //threshold value for light intensity
LiquidCrystal lcd(12,11,5,4,3,2);   //initialize all the LCD connnections
const int B = 4250;
int thresholdvalue = 15;              //thresholdvalue of temperature to switch the warmers on

int Light;                           //initialize light here
float Temperature;                  //initialize temperature type here



void displaySerial()
 {
      Serial.print(Light);             //print light intensity on serial
      Serial.println(" lux");          //using illuminance SI unit
      Serial.print(Temperature);       //print temperature on serial
      Serial.println(" °C");           //temperature is in Celsius

  }

void setup()
{
	 Serial.begin(115200); //Initialize serial port - 9600 bps
         delay(1000);    //delay one second before printing the next value
         lcd.begin(16,2);    //LCD initialization

}

void loop()
{

  //read light sensor
  Light = analogRead(A1);

  if( Light > thresholdValue){
	  digitalWrite(13, HIGH);
  }
  else{
	  digitalWrite(13, LOW);
  }

//read the temperature sensor
  int val = analogRead(TempPin);

  // Determine the current resistance of the thermistor based on the sensor value.
  float resistance = (float)(1023-val)*10000/val;

  // Calculate the temperature based on the resistance value.
  Temperature = 1/(log(resistance/10000)/B+1/298.15)-273.15;

  if(Temperature < thresholdvalue)          //LED turns on if temperature falls below 15 degrees
 {
     digitalWrite(9, HIGH);
 }
 else
 {
     digitalWrite(9, LOW);
 }
 // Wait one second between measurements.
 delay(1000);


  displaySerial();                  //function to print the values on serial 

   lcd.setCursor(0,0);
   lcd.print("Light: ");
   lcd.print(Light);
   lcd.setCursor(0,1);
   lcd.print("Temp: ");
   lcd.print(Temperature);
 //turn the LED on (HIGH is the voltage level)
 //digitalWrite(13, HIGH);

// wait for a second
delay(1000);
// turn the LED off by making the voltage LOW
//digitalWrite(13, LOW);

// wait for a second
 delay(1000);
}
