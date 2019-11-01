#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include "GRobotDisplay.h"
#include "GRobotEnvironment.h"

LiquidCrystal_I2C LCD(16,2);  

//============ LCD ===============
void LCD_Setup()
{
	uint8_t addr=0;
	int error=1;
	Wire.begin();
	Wire.beginTransmission(0x3f);
	error = Wire.endTransmission();
	if (error == 0) addr=0x3f;

	Wire.beginTransmission(0x27);
	error = Wire.endTransmission();
	if (error == 0) addr=0x27;

	LCD.init(addr);
	LCD.backlight();
}
void LCD_Print(String str, byte col, byte row)
{
	LCD.setCursor(col,row);
	LCD.print(str);
}

void LCD_scrollLeft()
{
	LCD.scrollDisplayLeft();
}

void LCD_scrollRight()
{
	LCD.scrollDisplayRight();
}

void LCD_clear()
{
	LCD.clear();
}

//=========== Matrix =============

void strMatrix(String str)
{
    Wire.beginTransmission(0x02); 
    Wire.println("*S" + str + "#");
    Wire.endTransmission();
}

void scrollLeft (byte column, byte delayTime)
{
	String temp="";
	if(column<10) temp= "0" + String(column);
	else temp = String(column);
	
	if(delayTime<10) temp= temp + "0"+String(delayTime);
	else temp = temp + String(delayTime);
    Serial.println("*L" + temp + "#");
	Wire.beginTransmission(0x02); 
    Wire.println("*L" + temp + "#");
    Wire.endTransmission();
}

void scrollRight (byte column, byte delayTime)
{
	String temp="";
	if(column<10) temp= "0" + String(column);
	else temp = String(column);
	
	if(delayTime<10) temp= temp + "0"+String(delayTime);
	else temp = temp + String(delayTime);
    
	Wire.beginTransmission(0x02); 
    Wire.println("*R" + temp + "#");
    Wire.endTransmission();
}

void alignMatrix(boolean edge) //Attiny Call: W for Align Left, w for Align Right
{
	
}
void cusChar(boolean index, byte font[8])
{
	
}
