#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "GRobot.h"

  
  // DEFAULTS
  bool  Bluetooth_ServoMode     = 0;
  int   Bluetooth_Speed         = 250;
  int   Bluetooth_Val           = 250;
  char  Bluetooth_Buffer        = 'S';
  unsigned long timer = 0;

  int 		S4A_Mode_Index = 3;
  int   	S4A_Speed               = 250;
  boolean 	S4A_SetupFlag           = 0;
  boolean 	S4A_PlayFlag			= 0;
  boolean 	S4A_RequestFlag			= 0;  
  String   	S4A_SetupCommand        = "";
  String 	S4A_Request 			= "";
  String 	S4A_Respone 			= "";
  int spdList[6] = {0,50,100,150,200,250};
  int angleList[5] = {0,45,90,135,180};
//strip_1 = Adafruit_NeoPixel(60, PIN_RGB, NEO_GRB + NEO_KHZ800);
  
/*************************************************************
 * GENERAL FUNCTIONS
 */

  /***
   * Reset 
   */
 
 void(* resetFunc) (void) = 0;

  /***
   * Setup Pin Layout for all modes
   */
  void ResetPinLayout() {
	if ((boardID == 0)||(boardID==11)) //Creator Aruino UNO   ||    B_Creator
	{	
		for(int i = 0; i < 6 ; i++)
			pinMode(pinD[i], INPUT);	
		for(int i = 0; i < 4 ; i++)
			pinMode(pinA[i], INPUT);
	}
	
	if (boardID == 12)//mini Creator
	{	
		for(int i = 0; i < 2 ; i++)
			pinMode(pinD[i], INPUT);	
		for(int i = 0; i < 2 ; i++)
			pinMode(pinA[i], INPUT);	
	}

	if (boardID == 21) //B_Innovator
	{	
		for(int i = 0; i < 8 ; i++)
			pinMode(pinD[i], INPUT);	
		for(int i = 0; i < 8 ; i++)
			pinMode(pinA[i], INPUT);
	}	
  }
   
  void SetupPinLayout() {
    pinMode(PIN_EnA,      OUTPUT);
    pinMode(PIN_DirA,     OUTPUT);
    pinMode(PIN_EnB,      OUTPUT);
    pinMode(PIN_DirB,     OUTPUT);   
	if (boardID == 0) //Creator Aruino UNO
	{	
		for(int i = 0; i < 6 ; i++)
			pinMode(pinD[i], INPUT);	
		for(int i = 0; i < 4 ; i++)
			pinMode(pinA[i], INPUT);
	}
	
	if (boardID == 11) //B_Creator
	{	
		for(int i = 0; i < 6 ; i++)
			pinMode(pinD[i], INPUT);	
		for(int i = 0; i < 4 ; i++)
			pinMode(pinA[i], INPUT);
		strip_1 = Adafruit_NeoPixel(12, PIN_RGB_1, NEO_GRB + NEO_KHZ800);
		strip_1.begin();
		strip_1.show();
		strip_1.setBrightness(15);
		irrecv.enableIRIn();
	}
	
	if (boardID == 12)//mini Creator
	{	
		for(int i = 0; i < 2 ; i++)
			pinMode(pinD[i], INPUT);	
		for(int i = 0; i < 2 ; i++)
			pinMode(pinA[i], INPUT);	
		strip_1 = Adafruit_NeoPixel(1, PIN_RGB_1, NEO_GRB + NEO_KHZ800);
		strip_1.begin();
		strip_1.show();
		strip_1.setBrightness(15);

		strip_2 = Adafruit_NeoPixel(1, PIN_RGB_2, NEO_GRB + NEO_KHZ800);
		strip_2.begin();
		strip_2.show();
		strip_2.setBrightness(15);		
	}
	
	if (boardID == 21) //B_Innovator
	{	
		for(int i = 0; i < 8 ; i++)
			pinMode(pinD[i], INPUT);	
		for(int i = 0; i < 8 ; i++)
			pinMode(pinA[i], INPUT);
		strip_1 = Adafruit_NeoPixel(12, PIN_RGB_1, NEO_GRB + NEO_KHZ800);
		strip_1.begin();
		strip_1.show();
		strip_1.setBrightness(15);
		
		strip_2 = Adafruit_NeoPixel(2, PIN_RGB_2, NEO_GRB + NEO_KHZ800);
		strip_2.begin();
		strip_2.show();
		strip_2.setBrightness(15);		
		irrecv.enableIRIn();
	}	
  }
  
  /***
   * Begin Mode Calls
   */
  void BeginMode(byte *mode) {
    ResetPinLayout();
    switch(*mode) {
      case 0: //Red 
	  	if (boardID == 11) 	colorWipe(strip_1.Color(255, 0, 0), 40);//B_Creator 
		if (boardID == 12)//mini Creator 
		{
			strip_1.setPixelColor(0, strip_1.Color(255, 0, 0));
			strip_2.setPixelColor(0, strip_2.Color(255, 0, 0));
			strip_1.show();			
			strip_2.show();	
        }
		if (boardID == 21)	//B_Innovator
		{
			colorWipe(strip_1.Color(255, 0, 0), 40);		
			strip_2.setPixelColor(0, colorToRGB(0)); //Red
			strip_2.setPixelColor(1, colorToRGB(0)); //Red			
			strip_2.show();		
		}
		begin_GameBluetooth();
        break;
      case 1: //Green 
		if (boardID == 11) colorWipe(strip_1.Color(0, 255, 0), 40);//B_Creator 
		if (boardID == 12)//mini Creator 
		{
			strip_1.setPixelColor(0, strip_1.Color(0, 255, 0));
			strip_2.setPixelColor(0, strip_2.Color(0, 255, 0));	
			strip_1.show();			
			strip_2.show();				
        }	  
		if (boardID == 21)	//B_Innovator
		{
			colorWipe(strip_1.Color(0, 255, 0), 40);		
			strip_2.setPixelColor(0, colorToRGB(1)); //Green
			strip_2.setPixelColor(1, colorToRGB(1)); //Green			
			strip_2.show();		
		}		
        begin_GameIR_Remote();
        break;
	  case 2: //Blue
	  	if (boardID == 11)  colorWipe(strip_1.Color(0,  0, 255), 40);  //B_Creator 
		if (boardID == 12)//mini Creator 
		{
			strip_1.setPixelColor(0, strip_1.Color(0,  0, 255));
			strip_2.setPixelColor(0, strip_2.Color(0,  0, 255));	
			strip_1.show();			
			strip_2.show();				
        }	  
		if (boardID == 21)	//B_Innovator
		{
			colorWipe(strip_1.Color(0, 0, 255), 40);		
			strip_2.setPixelColor(0, colorToRGB(2)); //Blue
			strip_2.setPixelColor(1, colorToRGB(2)); //Blue			
			strip_2.show();		
		}			
        begin_GameObjectAvoider();
        break;
      case 3: //Yellow
	  	if (boardID == 11) colorWipe(strip_1.Color(125, 125, 0), 40);  //B_Creator 
		if (boardID == 12)//mini Creator 
		{
			strip_1.setPixelColor(0, strip_1.Color(125, 125, 0));
			strip_2.setPixelColor(0, strip_2.Color(125, 125, 0));
			strip_1.show();			
			strip_2.show();				
        }	
		if (boardID == 21)	//B_Innovator
		{
			colorWipe(strip_1.Color(125, 125, 0), 40);		
			strip_2.setPixelColor(0, colorToRGB(3)); //Yellow
			strip_2.setPixelColor(1, colorToRGB(3)); //Yellow			
			strip_2.show();		
		}			
        begin_GameS4A();
        break;
      case 4: //White
	  	if (boardID == 11) colorWipe(strip_1.Color(255, 255, 255), 40);  //B_Creator 
		if (boardID == 12)//mini Creator 
		{
			strip_1.setPixelColor(0, strip_1.Color(255, 255, 255));
			strip_2.setPixelColor(0, strip_2.Color(255, 255, 255));	
			strip_1.show();			
			strip_2.show();				
        }	  
		if (boardID == 21)	//B_Innovator
		{
			colorWipe(strip_1.Color(255, 255, 255), 40);		
			strip_2.setPixelColor(0, colorToRGB(4)); //White
			strip_2.setPixelColor(1, colorToRGB(4)); //White			
			strip_2.show();		
		}					
        break;		
    }
  }
  
  /***
   * End Mode Calls
   */
  void EndMode(byte mode) {
    switch(mode) {
      case 0:
        end_GameBluetooth();
        break;
      case 1:
        end_GameIR_Remote();
        break;
      case 2:
        end_GameObjectAvoider();
        break;
      case 3:
        end_GameS4A();
        break;
	  case 4:
	    end_Programming();
		break;
    }
  }
void end_Programming()
{
	GRobot_ServoDetach(4);
	GRobot_ServoDetach(5);
}

  
/*************************************************************
 * GAME BLUETOOTH
 */

  /***
   * Code khi bat dau game bluetoothGAME_SERVO
   */
  void begin_GameBluetooth() {
    Serial.println("Begin Bluetooth");
    Bluetooth_ServoMode = 0;  
    Bluetooth_Val       = 0;
    Bluetooth_Buffer    = 'S';

	byte ServoPort;
	if(boardID==0) ServoPort = 4;	
	if(boardID==11) ServoPort = 4;
	if(boardID==12) ServoPort = 0; //Maker
	if(boardID==21) ServoPort = 0;  //Innovator==== Chưa quy ước 	
	GRobot_ServoAttach(ServoPort);
	GRobot_ServoWrite(ServoPort,90);
    wDigital(5,1); //Relay port 6 -  OFF
	timer= millis();
  }

  /***
   * Code khi ra khoi game bluetooth
   */
  void end_GameBluetooth() {
    //Serial.println("End Bluetooth");
	byte ServoPort;
	if(boardID==0) ServoPort = 4;	
	if(boardID==11) ServoPort = 4;
	if(boardID==12) ServoPort = 0; //Maker
	if(boardID==21) ServoPort = 0;  //Innovator==== Chưa quy ước 	
	GRobot_ServoDetach(ServoPort);
	GRobot_Stop();
  }

  
//========================================
//===========  Bluetooth 1 ===============
//========================================
  void loop_GameBluetooth()
  {   
	byte ServoPort;
	if(boardID==0) ServoPort = 4;	
	if(boardID==11) ServoPort = 4;
	if(boardID==12) ServoPort = 0; //Maker
	if(boardID==21) ServoPort = 0;  //Innovator==== Chưa quy ước 
    if (Serial.available() > 0) {
      //đọc dữ liệu gửi về
      Bluetooth_Buffer = Serial.read();
      Serial.println(Bluetooth_Buffer);
    }
    switch (Bluetooth_Buffer) {
      case 'W': //Front Light ON (PORT 4)
        wDigital(3,1);
        break;
      case 'w': //Front Light OFF
        wDigital(3,0);
        break;

      case 'U': //Relay ON (PORT 6)
        wDigital(5,0);
        break;

      case 'u':
        wDigital(5,1);
        break;
		
      case 'F':
        GRobot_Forward(Bluetooth_Speed);
        break;

      case 'B':
        GRobot_Back(Bluetooth_Speed);
        break;

      case 'S':
        GRobot_Stop();
        break;

      case 'L':
        GRobot_RotateLeft(Bluetooth_Speed);
        break;

      case 'R':
        GRobot_RotateRight(Bluetooth_Speed);
        break;

      case 'G':
        GRobot_ForwardLeft(Bluetooth_Speed);
        break;

      case 'I':
        GRobot_ForwardRight(Bluetooth_Speed);
        break;

      case 'H':
        GRobot_BackLeft(Bluetooth_Speed);
        break;

      case 'J':
        GRobot_BackRight(Bluetooth_Speed);
        break;

	  case 'V':
        buzzer(1);
        break;
		
	  case 'v':
        buzzer(0);
        break;
			
      case 'X':
        Bluetooth_ServoMode = 1;
        break;

      case 'x':
        Bluetooth_ServoMode = 0;
        break;
    
      case '0':
        Bluetooth_Val = 0;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '1':
        Bluetooth_Val = 25;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '2':
        Bluetooth_Val = 50;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '3':
        Bluetooth_Val = 75;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '4':
        Bluetooth_Val = 100;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '5':
        Bluetooth_Val = 125;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '6':
        Bluetooth_Val = 150;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '7':
        Bluetooth_Val = 175;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '8':
        Bluetooth_Val = 200;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case '9':
        Bluetooth_Val = 225;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;

      case 'q':
        Bluetooth_Val = 250;
        if (Bluetooth_ServoMode) GRobot_ServoWrite(ServoPort, map(Bluetooth_Val,0,250,0,180));
        else Bluetooth_Speed = Bluetooth_Val;
        break;
    }
  }

//========================================
//===========  Bluetooth 2 ===============
//========================================


void loop_GameBluetooth_2()
  {   
	byte ServoMin=15;
	byte ServoMax=60;
	byte ServoPort;
	if(boardID==0) ServoPort = 4;	
	if(boardID==11) ServoPort = 4;
	if(boardID==12) ServoPort = 0;
	if(boardID==21) ServoPort = 0;
    if (Serial.available() > 0) {
      //đọc dữ liệu gửi về
      Bluetooth_Buffer = Serial.read();
      Serial.println(Bluetooth_Buffer);
    }

	if(((millis() - timer)>50)||(Bluetooth_Buffer=='L')||(Bluetooth_Buffer=='R')||(Bluetooth_Buffer=='S'))
	{
		timer = millis();
		switch (Bluetooth_Buffer) {

		  case 'F':
			Bluetooth_Val=Bluetooth_Val+5;
			if (Bluetooth_Val>=180) Bluetooth_Val = 180;
			GRobot_ServoWrite(5, Bluetooth_Val);
			break;

		  case 'B':
			Bluetooth_Val=Bluetooth_Val-5;
			if (Bluetooth_Val<=0) Bluetooth_Val = 0;
			GRobot_ServoWrite(5, Bluetooth_Val);        
			break;

		  case 'S':
			GRobot_Stop();
			break;

		  case 'L':
			GRobot_motor_1(30);
			break;

		  case 'R':
			GRobot_motor_1(-30);
			break;
		
		  case '0':
			GRobot_ServoWrite(ServoPort, map(0,0,10,0,180));
			break;

		  case '1':
			GRobot_ServoWrite(ServoPort, map(1,0,10,0,180));
			break;

		  case '2':
			GRobot_ServoWrite(ServoPort, map(2,0,10,0,180));
			break;

		  case '3':
			GRobot_ServoWrite(ServoPort, map(3,0,10,0,180));
			break;

		  case '4':
			GRobot_ServoWrite(ServoPort, map(4,0,10,0,180));
			break;

		  case '5':
			GRobot_ServoWrite(ServoPort, map(5,0,10,0,180));
			break;

		  case '6':
			GRobot_ServoWrite(ServoPort, map(6,0,10,0,180));
			break;

		  case '7':
			GRobot_ServoWrite(ServoPort, map(7,0,10,0,180));
			break;

		  case '8':
			GRobot_ServoWrite(ServoPort, map(8,0,10,0,180));
			break;

		  case '9':
			GRobot_ServoWrite(ServoPort, map(9,0,10,0,180));
			break;

		  case 'q':
			GRobot_ServoWrite(ServoPort, map(10,0,10,0,180));
			break;
		}
	
	}
  }

  
/*************************************************************
 * GAME IR_Remote
 */

  /***
   * Code khi bat dau game GAME IR_Remote
   */
  void begin_GameIR_Remote() {
	Serial.println("Begin GameIR_Remote");  
	IR_EEPROOM_Read();
	timer = 0;
	IRvalue = 0;
  }

  /***
   * Code khi ra khoi GameIR_Remote
   */
  void end_GameIR_Remote() {
	GRobot_Stop();
	for(int i=0;i<12;i++) IRcommand[i]= 1 ;
	timer = 0;
	IRvalue = 0;
  }

  
//========================================
//===========  GAME IR_Remote ============
//========================================
unsigned long timer_IRlearning = 0;
#define GameIRChannel 5
void IR_EEPROOM_Read()
{
	for(int i=0;i<GameIRChannel;i++) //5 channel
	{
		IRcommand[i]=0;
		for (int k = 0; k < 4; k++)//4byte per channel
			IRcommand[i] = IRcommand[i] * 256 + EEPROM.read(10 + i*4 + k);
	}

}
void IR_EEPROOM_Write()
{
	unsigned long temp;
	int eep[4];
	for(int i=0;i<GameIRChannel;i++) //5 channel
	{
		temp = IRcommand[i];
		for (int k = 0; k < 4; k++)//4byte per channel
		{
			eep[k] = temp % 256;
			temp = temp / 256;
		}
		for (int k = 3; k >= 0; k--)
			EEPROM.write(10 + i*4 + 3-k, eep[k]);
	}
	
}

  void loop_GameIR_Remote()
  {   
	IRvalue=0;
	if (irrecv.decode(&results)) 
	{
		IRvalue = results.value;
		irrecv.resume(); // Receive the next value
		Serial.print("value ");
		Serial.println(IRvalue);
		timer = millis();
		if(timer_IRlearning==0) timer_IRlearning = timer;
	}
	if (((millis() - timer) >200)&&(timer!=0))	{timer = 0; timer_IRlearning = 0;}
	
	if (((millis() - timer_IRlearning)>2000)&&(timer_IRlearning!=0))  
	{
		PlaySoundStart(); 
		while (irrecv.decode(&results)) {IRvalue = results.value; irrecv.resume();}
		delay(2000); 
		IR_Learning(5,1); 
		IR_EEPROOM_Write();
		timer = 0; 
		timer_IRlearning = 0;
	}

	if(IRcommand[0] == IRvalue) GRobot_Forward(100);
	if(IRcommand[1] == IRvalue) GRobot_Back(100);
	if(IRcommand[2] == IRvalue) GRobot_RotateLeft(80);
	if(IRcommand[3] == IRvalue) GRobot_RotateRight(80);
	if(IRcommand[4] == IRvalue) GRobot_Stop();
  }
  
/*************************************************************
 * GAME OBJECT AVOIDER 
 */

  /***
   * Code khi bat dau game GameObjectAvoider
   */
  void begin_GameObjectAvoider() {
    Serial.println("Begin ObjectAvoider");
  }

  /***
   * Code khi ra khoi game GameObjectAvoider
   */
  void end_GameObjectAvoider() {
	GRobot_Stop();
  }
  
  /***
   * Code chay mai trong loop cho game follow line
   */
  void loop_GameObjectAvoider()
  {
    // Convert to pair of sinals in bits (left,right): i.e 10=(1,0) meaning left is on and right is off
    //byte IR_Value        = GetFollowLine(1,1)*2 + GetFollowLine(1,0);
  
    // scan ultrasonic distance (to know when to stop)
    int distance = 0;
	if(boardID==11) distance = GetUltrasonicDistance(2); //BCreator dùng port 3
	else distance = GetUltrasonicDistance(0);

    //Serial.println("ir = " + String(IR_Value) + ", d = " + String(distance));
	//Serial.println(distance);
    //distance 0 is reserved for timeout
    
	if (distance<25 && distance>0) {
      GRobot_Back(120);
	  delay(800);
	  switch(random(1))
	  {
		  case 0: 	GRobot_RotateLeft(170);
					delay(300);
					break;
		  case 1: 	GRobot_RotateRight(170);
					delay(300);
					break;
	  }
    } 
	GRobot_Forward(120);
  }


/*************************************************************
 * GAME S4A
 */

/* Old Version */
void begin_GameS4A() {
    Serial.println("Begin S4A");
    S4A_SetupFlag = 0;
	S4A_PlayFlag=0;
    S4A_SetupCommand = "";
    Bluetooth_Buffer = 'S';
	while ((!S4A_PlayFlag)&&(GetISRMode()==S4A_Mode_Index))
    if (Serial.available() > 0) {
		//đọc dữ liệu gửi về
		Bluetooth_Buffer = Serial.read();
		if ((Bluetooth_Buffer == '#')&& S4A_SetupFlag)
		{
			S4A_SetupFlag = 0;
			S4A_PlayFlag = 1;
			S4A_Setup(S4A_SetupCommand);
			Serial.println(S4A_SetupCommand);
		}
		if((Bluetooth_Buffer>47)&&((Bluetooth_Buffer<97)||(Bluetooth_Buffer>122))) S4A_SetupFlag = 0;
		if (S4A_SetupFlag) S4A_SetupCommand = S4A_SetupCommand + Bluetooth_Buffer;

		if (Bluetooth_Buffer == '*')
		{
			  S4A_SetupFlag = 1;
			  S4A_SetupCommand=""; 
		}
    }
}


 void S4A_Setup(String S4A_SetupCommand)
{
	for (int i = 0; i<6; i++)
	{
		switch(S4A_SetupCommand[i])
		{
			case 'c':
				GRobot_ServoAttach(i);
				GRobot_ServoWrite(i, angleList[0]);
				break;
			default:
				break;
		}
	}
	//Respone OK
	Serial.println("*G#");
}
  /***
   * Code khi ra khoi game S4A
   */
  void end_GameS4A() {
    //Serial.println("End S4A");
	GRobot_ServoDetach(4);
	GRobot_ServoDetach(5);
	GRobot_Stop();
  }



void S4A_Motor(String S4A_Request)
{	
	int spd=0;
	int index = (S4A_Request[1]-48);
	
	if ((S4A_Request [0]=='m') || (S4A_Request[0] == 'M'))
	{
		if (index < 5) spd = -spdList[5 - index];
		else spd = spdList[index-5];
	}
	else spd = spdList[index];
	
	switch (S4A_Request[0]) {
		case 'E':
			GRobot_ServoWrite(4, angleList[index]);
			break;
		case 'e':
			GRobot_ServoWrite(5, angleList[index]);
			break;
		case 'm':
			GRobot_motor_1(spd);
			break;
		case 'M':
			GRobot_motor_2(spd);
			break;			
		case 'F':
			GRobot_Forward(spd);
			break;
		case 'B':
			GRobot_Back(spd);
			break;
		case 'S':
			GRobot_Stop();
			break;
		case 'L':
			GRobot_RotateLeft(spd);
			break;
		case 'R':
			GRobot_RotateRight(spd);
			break;

		case 'G':
			GRobot_ForwardLeft(spd);
			break;

		case 'I':
			GRobot_ForwardRight(spd);
			break;

		case 'H':
			GRobot_BackLeft(spd);
			break;

		case 'J':
			GRobot_BackRight(spd);
			break;
		default:
			break;
	}
	
}

  void loop_GameS4A()
  {		
	String respone="*";
	int value;
	if(S4A_PlayFlag)
	{	
		//Read Serial for Request
		if (Serial.available() > 0) 
		{
			Bluetooth_Buffer = Serial.read();
			if(Bluetooth_Buffer=='#') 	
			{
				S4A_RequestFlag=0;
				Serial.println(S4A_Request);
				S4A_Motor(S4A_Request);	
				if(S4A_Request=="0") {end_GameS4A(); begin_GameS4A();}
				else S4A_Motor(S4A_Request);	
			}

			if (S4A_RequestFlag) S4A_Request = S4A_Request + Bluetooth_Buffer;
			
			if(Bluetooth_Buffer == '*')
			{
				S4A_Request="";	
				S4A_RequestFlag=1;
			}			
		}
		
		//Respone Sensor Value
		for (int i = 0; i<6; i++)
		{
			switch(S4A_SetupCommand[i])
			{
				case 'a':
					respone = respone + "00" + String(GetFollowLine(i, 0)) + "00" + String(GetFollowLine(i, 1)) + "|";
					break;
				case 'b':
					value=GetUltrasonicDistance(i);
					if (value<10) respone = respone + "00" + String (value) + "|";
					else 	if (value<100) respone = respone + "0" + String (value) + "|";
							else respone = respone + String (value) + "|";
					break;
				default: respone= respone+"|";
					break;
			}
		}
		value=respone.length();
		respone[value-1]='#';	
		Serial.println(respone);
	}
  }

   /* New Version 
void begin_GameS4A() {
    Serial.println("Begin S4A");
    S4A_SetupFlag = 0;
	S4A_PlayFlag=0;
    S4A_SetupCommand = "";
    Bluetooth_Buffer = 'S';
	while ((!S4A_PlayFlag)&&(GetISRMode()==S4A_Mode_Index))
    if (Serial.available() > 0) {
		//đọc dữ liệu gửi về
		Bluetooth_Buffer = Serial.read();
		if ((Bluetooth_Buffer == '#')&& S4A_SetupFlag)
		{
			S4A_SetupFlag = 0;
			S4A_PlayFlag = 1;
			S4A_Setup(S4A_SetupCommand);
			Serial.println(S4A_SetupCommand);
		}
		if((Bluetooth_Buffer>47)&&((Bluetooth_Buffer<97)||(Bluetooth_Buffer>122))) S4A_SetupFlag = 0;
		if (S4A_SetupFlag) S4A_SetupCommand = S4A_SetupCommand + Bluetooth_Buffer;

		if (Bluetooth_Buffer == '*')
		{
			  S4A_SetupFlag = 1;
			  S4A_SetupCommand=""; 
		}
    }
}


 void S4A_Setup(String S4A_SetupCommand)
{
	for (int i = 0; i<6; i++)
	{
		switch(S4A_SetupCommand[i])
		{
			case 'c':
				GRobot_ServoAttach(i);
				GRobot_ServoWrite(i, angleList[0]);
				break;
			default:
				break;
		}
	}
	//Respone OK
	Serial.println("*G#");
}


  void end_GameS4A() {
    //Serial.println("End S4A");
	GRobot_ServoDetach(4);
	GRobot_ServoDetach(5);
	GRobot_Stop();
  }



void S4A_Act(String S4A_Request)
{	
	int spd = 0;
	int index=0;
	switch (S4A_Request[0]) {
	case 'M': //Motion Request
		switch (S4A_Request[1]) {
		case 'E': //Servo  
			GRobot_ServoWrite(int(S4A_Request[2]-48), angleList[int(S4A_Request[3]-48)]); //port , angle 
			break;
			
		case 'M': //Single Motor
			index = int(S4A_Request[3]-48);
			if (index < 5) spd = -spdList[5 - index];
					else   spd =  spdList[index-5];		
			if(int(S4A_Request[2]-48)==1) GRobot_motor_1(spd);
			if(int(S4A_Request[2]-48)==2) GRobot_motor_2(spd);
			break;			
		
		//Movement
		case 'F':	
			index = int(S4A_Request[2]-48);
			spd = spdList[index];			
			GRobot_Forward(spd);
			break;
			
		case 'B':
			index = int(S4A_Request[2]-48);
			spd = spdList[index];			
			GRobot_Back(spd);
			break;
			
		case 'S':
			GRobot_Stop();
			break;
			
		case 'L':
			index = int(S4A_Request[2]-48);
			spd = spdList[index];				
			GRobot_RotateLeft(spd);
			break;
			
		case 'R':
			index = int(S4A_Request[2]-48);
			spd = spdList[index];	
			GRobot_RotateRight(spd);
			break;
			
		case 'G':
			index = int(S4A_Request[2]-48);
			spd = spdList[index];	
			GRobot_ForwardLeft(spd);
			break;
			
		case 'I':
			index = int(S4A_Request[2]-48);
			spd = spdList[index];	
			GRobot_ForwardRight(spd);
			break;

		case 'H':
			index = int(S4A_Request[2]-48);
			spd = spdList[index];	
			GRobot_BackLeft(spd);
			break;

		case 'J':
			index = int(S4A_Request[2]-48);
			spd = spdList[index];			
			GRobot_BackRight(spd);
			break;
		default:
			break;
		}
		break;
	
	case 'D': //Display Request
		switch (S4A_Request[1]) {
		case 'L': //LCD1602 - Print
			LCD_Print(S4A_Request.substring(4), byte(S4A_Request[2]-48), byte(S4A_Request[3]-48));
			break;
		case 'l': //LCD1602 - Command
			if(int(S4A_Request[2]-48)==0) LCD_clear();
			if(int(S4A_Request[2]-48)==1) LCD_scrollLeft();
			if(int(S4A_Request[2]-48)==2) LCD_scrollRight();
		case 'M': //Matrix - Print  
			break;
		case 'm': //Matrix - Command
			break;
		default:
			break;
		}
		break;
	
	case 'C': //Control Request
		switch (S4A_Request[1]) {
		case 'B': //Buzzer
			buzzer(bool(S4A_Request[2]-48));
			break;
		case 'D': //digitalWrite
			wDigital(byte(S4A_Request[2]-48),bool(S4A_Request[3]-48));
			break;
		case 'A': //analogWrite
			wAnalog(byte(S4A_Request[2]-48),int(S4A_Request[3]-48));			
			break;
		default:
			break;
		}
		break;
		
	default:
		break;
	}
}

  void loop_GameS4A()
  {		
	String respone="*";
	int value;
	
	//Read Serial for Request
	if (Serial.available() > 0) 
	{
		Bluetooth_Buffer = Serial.read();
		if(Bluetooth_Buffer=='#') 	
		{
			S4A_RequestFlag=0;
			if (S4A_Request=="0") {end_GameS4A(); begin_GameS4A();}
			else if (S4A_Request.length()>1) 
					S4A_Act(S4A_Request);	
		}

		if (S4A_RequestFlag) S4A_Request = S4A_Request + Bluetooth_Buffer;
		
		if(Bluetooth_Buffer == '*')
		{
			S4A_Request="";	
			S4A_RequestFlag=1;
		}			
    }

	//Respone Sensor Value
	for (int i = 0; i<6; i++)
	{
		
		switch(S4A_SetupCommand[i])
		{
			case 'a':
				respone = respone + "00" + String(GetFollowLine(i, 0)) + "00" + String(GetFollowLine(i, 1)) + "|";
				break;
			case 'b':
				value=GetUltrasonicDistance(i);
				if (value<10) respone = respone + "00" + String (value) + "|";
				else 	if (value<100) respone = respone + "0" + String (value) + "|";
						else respone = respone + String (value) + "|";
				break;
			case 'd':
				respone = respone + "00" + String(GetChannel_D(i)) + "|";
				break;

			case 'e':
				value=GetChannel_A(i);
				if (value<10) respone = respone + "000" + String (value) + "|";
				else 	if (value<100) respone = respone + "00" + String (value) + "|";
						else	if (value<1000) respone = respone + "0" + String (value) + "|";
								else respone = respone + String (value) + "|";
				break;
			case 'g':
				value=GetTemperature(i);
				if (value<10) respone = respone + "00" + String (value) + "|";
				else 	if (value<100) respone = respone + "0" + String (value) + "|";			
						else respone = respone + String (value) + "|";
				break;
			case 'h':
				value=GetHumidity(i);
				if (value<10) respone = respone + "00" + String (value) + "|";
				else 	if (value<100) respone = respone + "0" + String (value) + "|";			
						else respone = respone + String (value) + "|";
				break;
												
			default: respone= respone+"|";
				break;
		}
	}
	value=respone.length();
	respone[value-1]='#';	
	Serial.println(respone);
  }
*/
