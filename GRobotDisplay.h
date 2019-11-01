/**********************************
 * GRobot copyright GARASTEM 2018
 */
#include "LiquidCrystal_I2C.h"

#ifndef _G_ROBOT_DISPLAY_H_
#define _G_ROBOT_DISPLAY_H_

//LCD
void LCD_Setup();
void LCD_Print(String str, byte col, byte row);
void LCD_scrollLeft();
void LCD_scrollRight();
void LCD_clear();

//Matrix 
void strMatrix(String str); //Truyền chuỗi, max 
void scrollLeft (byte column, byte delayTime); 
void scrollRight (byte column, byte delayTime);
void alignMatrix(boolean edge); //Attiny Call: W for Align Left, w for Align Right
void cusChar(boolean index, byte font[8]);
#endif
