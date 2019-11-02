#include "GRobotDevice.h"

bool phatHienVatCan(int port, int khoang_cach = 30) {
  if (GetUltrasonicDistance(port) < khoang_cach) {
    return 1;
  }
  return 0;
}

void LTK_setup() {
  Serial.println("Serial connected as baudrate 9600");
}

void LTK_loop() {
  if (phatHienVatCan(5, 40)) Serial.println("");
}
