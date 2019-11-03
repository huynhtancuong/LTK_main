#include "0LTK_functions.h"

void LTK_setup() {
  Serial.println("Serial connected as baudrate 9600");
}

void LTK_loop() {
  if (phatHienVatCan(5)) Serial.println("");
}
