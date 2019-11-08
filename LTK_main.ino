#include "0LTK_functions.h"
#include "GRobotDevice.h"
#include "GRobotMovements.h"

void LTK_setup() {
  Serial.println("Serial connected as baudrate 9600");
}

void LTK_loop() {

    GRobot_motor_1(100);
//    delay(2000);
//    GRobot_motor_1(-100);
//    delay(2000);
    if (phatHienVatCan(0, 30)) {
      GRobot_motor_2(50);
      delay(1500);
      GRobot_motor_2(0);
      delay(3000);
      GRobot_motor_2(-255);
      delay(200);
    }
}
