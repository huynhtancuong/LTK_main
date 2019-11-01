/**********************************
 * GRobot copyright GARASTEM 2018
 */
#include <EEPROM.h> 
#if defined (__AVR_ATmega2560__)
  #define pinD_Pre {4,5,2,3,6,15,A7,A5}
  #define pinA_Pre {A11,A12,A13,A14,A9,14,A8,A6}	
  #define PIN_IRrcv_define 18
#else 
  #define pinD_Pre {0,0,0,0,0,0,0,0}  
  #define pinA_Pre {0,0,0,0,0,0,0,0}	
  #define PIN_IRrcv_define A1
  
#endif
#include <Wire.h> 

  extern int pinD[8];
  extern int pinA[8];    
  extern int PIN_EnA;       
  extern int PIN_DirA;        
  extern int PIN_EnB;        
  extern int PIN_DirB;        
  extern int PIN_buzzerPin;  
  extern int PIN_Mode;  
  extern int PIN_RGB_1, PIN_RGB_2;
  extern int PIN_IRrcv,PIN_IRxmt;  
  extern int boardID;   
  

#ifndef _G_ROBOT_PIN_H_
#define _G_ROBOT_PIN_H_

  void readPinMap();
  void boardDefine(String BLUETOOTH_NAME, int board_ID);
  //B-Innovator
  #define PIN_LDR	A10
  
#endif
  /*
  Blue    5V
  Yellow  A4
  Green   A5
  Red     D
  Black   A
  White   GND 
  */
