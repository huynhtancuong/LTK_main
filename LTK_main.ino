#include "0LTK_functions.h"
#include "GRobotDevice.h"
#include "GRobotMovements.h"

void LTK_setup() {
  Serial.println("Serial connected as baudrate 9600");
}

void LTK_loop() {
  if (phatHienVatCan(5)) Serial.println("");
}
