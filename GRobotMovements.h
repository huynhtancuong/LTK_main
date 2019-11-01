/**********************************
 * GRobot copyright GARASTEM 2018
 */
#include <Servo.h>


#ifndef _G_ROBOT_ROBOTMOVEMENTS_H_
#define _G_ROBOT_ROBOTMOVEMENTS_H_
void GRobot_ServoAttach(byte port);
void GRobot_ServoDetach(byte port);
void GRobot_ServoDetachAll();
void GRobot_ServoWrite(byte port, int pos);

void GRobot_Forward(int spd);
void GRobot_Back(int spd);
void GRobot_Stop();
void GRobot_RotateLeft(int spd);
void GRobot_RotateRight(int spd);
void GRobot_TurnLeft(int spd);
void GRobot_TurnRight(int spd);
void GRobot_ForwardLeft(int spd);
void GRobot_ForwardRight(int spd);
void GRobot_BackLeft(int spd);
void GRobot_BackRight(int spd);
void GRobot_motor_1(int spd);
void GRobot_motor_2(int spd);

#endif
