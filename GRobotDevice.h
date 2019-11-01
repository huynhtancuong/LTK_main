/**********************************
 * GRobot copyright GARASTEM 2018
 */

#ifndef _G_ROBOT_DEVICE_H_
#define _G_ROBOT_DEVICE_H_

#include "Adafruit_NeoPixel.h"
#include "IRremote.h"



int GetFollowLine(byte port, byte slot);
int GetUltrasonicDistance(byte port);
int GetChannel_D(byte port);
int GetChannel_A(byte port);
int GetHumidity(byte port);
int GetTemperature(byte port);
int GetRealtime(byte field); // day of week: Sunday = 1, Saturday = 7	
void SetRealtime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr);

int wDigital (byte port, bool state);
int wAnalog (byte port, int state);
int buzzer (bool state);

byte GetColor(byte field);

//Led ring 
extern byte rgb_data[3];
extern Adafruit_NeoPixel strip_1, strip_2;

void colorWipe(uint32_t color, int wait);
uint32_t colorToRGB (byte color);
void ledRing_OFF();
void ledRing_wipeColor(byte color,byte wait);
void ledRing_wipeRGB(byte red, byte green, byte blue, byte wait);
void ledRing_pxColor(byte pixel,byte color);
void ledRing_pxRGB(byte pixel,byte red, byte green, byte blue);

//IR led
extern unsigned long IRcommand[12];
extern unsigned long IRvalue;
extern IRrecv irrecv;
extern decode_results results;


bool IRChannel(byte channel);
void GetIRsignal();
void IR_Learning(byte IRnumber,byte colorLEDRING);

#endif


/*
- FollowLine Sensor
- Ultrasonic Sensor
- GetChannel_D(byte port);
- GetChannel_A(byte port);
- Humidity DHT Sensor
- Temperature DHT Sensor

- wDigital(byte port, bool state);
- wAnalog(byte port, int state);
- buzzer (return 0/1)

*/
