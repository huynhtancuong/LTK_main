#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include "GRobotEnvironment.h"
   int pinD[8] ;
   int pinA[8] ;    
   int PIN_EnA ;       
   int PIN_DirA;        
   int PIN_EnB ;        
   int PIN_DirB;        
   int PIN_buzzerPin ;  
   int PIN_Mode;
   int PIN_RGB_1,PIN_RGB_2;
   int PIN_IRrcv,PIN_IRxmt;   
   int boardID;
   //Creator Arduino UNO  (255 255)
   //B-Creator G_UNO 	  (1 1)
   //Mini Creator   	  (1 2)
   //B-Innovator - Arduino Mega(2 1) 
	
void boardDefine(String BLUETOOTH_NAME, int board_ID)
{
  String ATname = "";
  boolean flagAT = 0;
  Serial.write("AT+NAME?");
  delay(50);
  while (Serial.available() > 0) //Đọc bluetooth_name hiện tại 
  {
    char test = Serial.read();
    if (flagAT) ATname = ATname + String(test);
    if (test == ':') flagAT = 1;
  }
  
  
  if (ATname != ("GRobot_" + BLUETOOTH_NAME)) //so sánh => đổi tên
  {
    Serial.print("AT+NAMEGRobot_" + BLUETOOTH_NAME);
    delay(50);
  }

  
  if ((EEPROM.read(0) != (board_ID/10)) || (EEPROM.read(1) != (board_ID%10))) //so sánh => đổi boardid
  {
    EEPROM.write(0, board_ID/10);
    EEPROM.write(1, board_ID%10);
  }	
}
   
void readPinMap()
{
	//Creator Arduino UNO
    const int pinD_AUNO[6] ={8,13,2,12,10,9}; 
    const int pinA_AUNO[4] ={A0,A1,A2,A3}; 
	//B-Creator G_UNO
	const int pinD_GUNO[6] ={9,8,3,11,13,12};
	const int pinA_GUNO[4] ={A7,A6,A0,A2};  	
	
	//Mini Creator
    const int pinD_mCr[2] ={8,13};
    const int pinA_mCr[2] ={A0,A1};     


   
	int add_0 = EEPROM.read(0);
	int add_1 = EEPROM.read(1);
	if((add_0==255)&&(add_1==255)) //Creator Arduino UNO (0 0)
	{
		Serial.println("A-Creator");
		boardID = 0;
		for (int i=0;i<6;i++)
			pinD[i] = pinD_AUNO[i];
		for (int i=0;i<4;i++)
			pinA[i] = pinA_AUNO[i];    
		PIN_EnA 		= 6;       
		PIN_DirA		= 7;        
		PIN_EnB 		= 5;        
		PIN_DirB		= 4;        
		PIN_buzzerPin   = 11;  
		PIN_Mode		= 3;		
	}

	if((add_0==1)&&(add_1==1)) //B-Creator (1 1)
	{
		Serial.println("B-Creator");
		boardID = 11;
		for (int i=0;i<6;i++)
			pinD[i] = pinD_GUNO[i];
		for (int i=0;i<4;i++)
			pinA[i] = pinA_GUNO[i];    
		PIN_EnA 		= 5;       
		PIN_DirA		= 7;        
		PIN_EnB 		= 6;        
		PIN_DirB		= 4;        
		PIN_buzzerPin   = 10;  
		PIN_RGB_1		= A3;
		PIN_Mode		= 2;
		PIN_IRrcv		= A1; 		
	}
	
	if((add_0==1)&&(add_1==2)) //Mini Creator - Arduino Nano(1 2)
	{
		Serial.println("B-Maker");
		boardID = 12;
		for (int i=0;i<2;i++)
			pinD[i] = pinD_mCr[i];
		for (int i=0;i<2;i++)
			pinA[i] = pinA_mCr[i];    
		PIN_EnA 		= 6;       
		PIN_DirA		= 7;        
		PIN_EnB 		= 5;        
		PIN_DirB		= 4;        
		PIN_buzzerPin   = 11;  
		PIN_RGB_1		= 12;
		PIN_RGB_2		= 10;
		PIN_Mode		= 3;	
		
		//GND WS2812
		pinMode(A2,OUTPUT);
		pinMode(2,OUTPUT);
		digitalWrite(A2,LOW);
		digitalWrite(2,LOW);
	}	
	
	if((add_0==2)&&(add_1==1)) //B-Innovator - Arduino Mega(2 1)
	{
		Serial.println("B-Innovator");
		boardID = 21;
		int PINd[8] =  pinD_Pre;
		int PINa[8] =  pinA_Pre;
		for (int i=0;i<8;i++)
			pinD[i] = PINd[i];
		for (int i=0;i<8;i++)
			pinA[i] = PINa[i];    
		PIN_EnA 		= 12;       
		PIN_DirA		= 48;        
		PIN_EnB 		= 11;        
		PIN_DirB		= 49;        
		PIN_buzzerPin   = 44;  
		PIN_RGB_1		= 26;
		PIN_RGB_2		= 25;		
		PIN_Mode		= 19;
		PIN_IRrcv		= 18;
		PIN_IRxmt		= 24;	
	}		
	
}
