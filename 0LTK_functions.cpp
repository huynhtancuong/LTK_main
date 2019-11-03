#include "GRobotDevice.h"

bool phatHienVatCan(int port, int khoang_cach) {
  if (GetUltrasonicDistance(port) < khoang_cach) {
    return 1;
  }
  return 0;
}
