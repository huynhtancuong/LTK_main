#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "ModeButton.h"
#include "GRobotEnvironment.h"

  unsigned long t = 0;
  bool Flag_ButtonOnboard= 0;
  byte isr_mode   = 0;
   
/***
 * Detect mode button press
 */

  /***
   * Using ISR
   */
  void ISR_Mode() {
    if ((millis()-t)>300) {
      isr_mode ++;
      if (isr_mode>4) isr_mode=0;
    }
    t = millis();
  }

  // RETURN ISR CONTROLLED MODE
  byte GetISRMode() {
    return isr_mode;
  }

void SetButtonOnboard(boolean state)
{
	if(state) 
	{
		detachInterrupt(digitalPinToInterrupt(PIN_Mode));
		isr_mode = 4; //Ngắt xuất hiện trước khi thực hiện SetButtonOnboard => gán isr_mode về 4
		Flag_ButtonOnboard = 1;
	}
	else if(Flag_ButtonOnboard)
	{
		Flag_ButtonOnboard = 0;
		delay(500);
		noInterrupts(); 
		attachInterrupt(digitalPinToInterrupt(PIN_Mode), ISR_Mode, FALLING);
		interrupts();
		isr_mode=4;
	}

}

int GetButtonOnboard()
{
	return digitalRead(PIN_Mode);
}
