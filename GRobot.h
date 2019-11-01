/**********************************
 * GRobot copyright GARASTEM 2018
 */
#include "GRobotEnvironment.h"
#include "GRobotMovements.h"
#include "GRobotDevice.h"
#include "GRobotDisplay.h"
#include "GRobotCommunication.h"
#include "ModeButton.h"
#include "Sound.h"

//extern Adafruit_NeoPixel strip_1,strip_2;

#ifndef _G_ROBOT_GROBOT_H_
#define _G_ROBOT_GROBOT_H_

#define GRobot_Ver  "<v2.5.1m>"
void SetupPinLayout();
void BeginMode(byte *mode);
void EndMode(byte mode);

void end_Programming();

void begin_GameBluetooth();
void end_GameBluetooth();
void loop_GameBluetooth();
void loop_GameBluetooth_2(); 

void begin_GameIR_Remote();
void end_GameIR_Remote();
void loop_GameIR_Remote();
void IR_EEPROOM_Read();
void IR_EEPROOM_Write();

void begin_GameObjectAvoider();
void end_GameObjectAvoider();
void loop_GameObjectAvoider();

//RGB LED WS2812b
void colorWipe(uint32_t c, uint8_t wait, Adafruit_NeoPixel strip);

/* Old Version */
void S4A_Setup(String S4A_SetupCommand);
void S4A_Motor(String S4A_Request);
void begin_GameS4A();
void end_GameS4A();
void loop_GameS4A();

/* New Version
void S4A_Setup(String S4A_SetupCommand);
void S4A_Act(String S4A_Request);
void begin_GameS4A();
void end_GameS4A();
void loop_GameS4A();
*/
#endif
