#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
int gasValue = A0; // smoke / gas sensor connected with analog pin A1 of the arduino / mega.
int data = 0; 
void setup()
{
randomSeed(analogRead(0));
mySerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
lcd.begin(16,2);
pinMode(gasValue, INPUT);
lcd.print (" Smoke Detection ");
lcd.setCursor(0,1);
lcd.print (" Alarm ");
delay(3000);
lcd.clear();
}
void loop()
{
data = analogRead(gasValue);
Serial.print("smoke Detection Level: ");
Serial.println(data);
lcd.print("Smoke Level: ");
lcd.print(data);
delay(1000);
if ( data > 400) //
{
SendMessage();
Serial.print("smoke Detector alarm");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Smoke Lvl Exceeded");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(1000);
}
else
{
Serial.print("smoke Level Low\n");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("smoke Level Normal");
delay(1000);
}
lcd.clear();
}
void SendMessage()
{
Serial.println("SMS NOTIFICATION IS SENDING");
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+919346228400\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Excess Smoke Detected, Please observe the Environment/Camera");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
