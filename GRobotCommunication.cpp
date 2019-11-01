#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "GRobotCommunication.h"

String getSerial()
{		
	char cBuffer = '\0';
	if (Serial.available() > 0) 
		cBuffer = Serial.read();
	return(String(cBuffer));
}

bool press_RaceScreen(String str)
{
	if (getSerial()==str) return 1;
	else return 0;
}

void SerialPrintln(String str)
{
	Serial.println(str);
}

