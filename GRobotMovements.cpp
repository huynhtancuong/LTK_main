#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "GRobotMovements.h"
#include "GRobotEnvironment.h"
Servo Gservo[6];
int GservoSTT[6] = {0,0,0,0,0,0};
void GRobot_ServoAttach(byte port)
{
	Gservo[port].attach(pinD[port]);
	GservoSTT[port] = 1;
}

void GRobot_ServoDetachAll()
{
	for(int i=0;i<6;i++)
		if(GservoSTT[i]) GRobot_ServoDetach(i);
}

void GRobot_ServoDetach(byte port)
{
	Gservo[port].detach();
	GservoSTT[port] = 0;
}
void GRobot_ServoWrite(byte port, int pos)
{
	if(!GservoSTT[port]) GRobot_ServoAttach(port);
	if (pos>=180) pos = 180;
	if (pos<=0) pos = 0;
	Gservo[port].write(pos);
}

void GRobot_motor_1(int spd)
{
  int dir=0;
  if (spd<0) spd = -spd ;
  else dir = 1;
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd);
  digitalWrite(PIN_DirA, dir);
}

void GRobot_motor_2(int spd)
{
  int dir=0;
  if (spd<0) spd = -spd ;
  else dir = 1;
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnB, spd);
  digitalWrite(PIN_DirB, dir);
}
  
void GRobot_Forward(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd);
  digitalWrite(PIN_DirA, HIGH);

  analogWrite(PIN_EnB, spd);
  digitalWrite(PIN_DirB, HIGH);
}

void GRobot_Back(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd);
  digitalWrite(PIN_DirA, LOW);

  analogWrite(PIN_EnB, spd);
  digitalWrite(PIN_DirB, LOW);
}

void GRobot_Stop()
{
  analogWrite(PIN_EnA, 0);
  analogWrite(PIN_EnB, 0);
}

void GRobot_RotateLeft(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd);
  digitalWrite(PIN_DirA, LOW);

  analogWrite(PIN_EnB, spd);
  digitalWrite(PIN_DirB, HIGH);
}

void GRobot_RotateRight(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd);
  digitalWrite(PIN_DirA, HIGH);

  analogWrite(PIN_EnB, spd);
  digitalWrite(PIN_DirB, LOW);
}

void GRobot_TurnLeft(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, 0);
  digitalWrite(PIN_DirA, HIGH);

  analogWrite(PIN_EnB, spd);
  digitalWrite(PIN_DirB, HIGH);
}

void GRobot_TurnRight(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd);
  digitalWrite(PIN_DirA, HIGH);

  analogWrite(PIN_EnB, 0);
  digitalWrite(PIN_DirB, HIGH);
}

void GRobot_ForwardLeft(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd*0.7);
  digitalWrite(PIN_DirA, HIGH);

  analogWrite(PIN_EnB, spd);
  digitalWrite(PIN_DirB, HIGH);
}

void GRobot_ForwardRight(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd);
  digitalWrite(PIN_DirA, HIGH);

  analogWrite(PIN_EnB, spd*0.7);
  digitalWrite(PIN_DirB, HIGH);
}


void GRobot_BackLeft(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd*0.7);
  digitalWrite(PIN_DirA, LOW);

  analogWrite(PIN_EnB, spd);
  digitalWrite(PIN_DirB, LOW);
}

void GRobot_BackRight(int spd)
{
  if(spd<0) spd = 0;
  if(spd>255) spd = 255;
  if ((boardID==12) && (spd>160)) spd = 160; 
  analogWrite(PIN_EnA, spd);
  digitalWrite(PIN_DirA, LOW);

  analogWrite(PIN_EnB, spd*0.7);
  digitalWrite(PIN_DirB, LOW);
}
