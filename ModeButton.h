/**********************************
 * GRobot copyright GARASTEM 2018
 */

#ifndef _G_ROBOT_MODEBUTTON_H_
#define _G_ROBOT_MODEBUTTON_H_

void ISR_Mode();
byte GetISRMode();
void SetButtonOnboard(boolean state);  //1 = Tắt iSR, 0= Bật ISR
int GetButtonOnboard();

#endif
