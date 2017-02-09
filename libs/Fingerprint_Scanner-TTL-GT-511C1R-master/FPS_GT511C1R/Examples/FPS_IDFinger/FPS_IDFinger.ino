/* 
	FPS_Enroll.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
	Created by Josh Hawley, July 23rd 2013
	Licensed for non-commercial use, must include this license message
	basically, Feel free to hack away at it, but just give me credit for my work =)
	TLDR; Wil Wheaton's Law

	This sketch will attempt to identify a previously enrolled fingerprint.
*/

#include "FPS_GT511C1R.h"
#include "SoftwareSerial.h"

// Hardware setup - FPS connected to:
//	  digital pin 4(arduino rx, fps tx)
//	  digital pin 5(arduino tx - 560ohm resistor fps tx - 1000ohm resistor - ground)
//		this brings the 5v tx line down to about 3.2v so we dont fry our fps

FPS_GT511C1R fps(4, 5);
int LEDpin = 11;      // connect Red LED to pin 11 (PWM pin)

void setup() {
	Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
	delay(100);
  //fps.UseSerialDebug = true; // so you can see the messages in the serial debug screen
	fps.Open();
	fps.SetLED(true);
}

void loop() {
	// Identify fingerprint test
	if (fps.IsPressFinger()) {
		fps.CaptureFinger(false);
		int id = fps.Identify1_N();
		if (id < 20) {
			Serial.print("Verified ID:");
			Serial.println(id);
      digitalWrite(LEDpin, HIGH);
		} else {
			Serial.println("Finger not found");
		}
	} else {
		Serial.println("Please press finger");
	}
	delay(100);
}
