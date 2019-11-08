#include "GRobotDevice.h"

bool phatHienVatCan(int port, int khoang_cach) {
  int distance = GetUltrasonicDistance(port);
  Serial.print("distance = ");
  Serial.println(distance);
  if (distance < khoang_cach) {
    return 1;
  }
  return 0;
}
