#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include "GRobotEnvironment.h"
#include "Sound.h"

/***
 * Variables
 */

  //CONSTANTS

  // Notes in half periods in microseconds. To get frequency of note i: 1000000/NOTES[i]*2
  const int NOTES[]     = {
    31250, 29412, 27778, 26316, 23810, 22727, 21739, 20000, 19231, 17857, 17241, 16129, 15152, 14286, 13514, 12821, 12195, 11364, 10870, 10204, 
    9615, 9091, 8621, 8065, 7692, 7246, 6849, 6410, 6098, 5747, 5376, 5102, 4808, 4545, 4274, 4065, 3817, 3597, 3401, 3205, 3030, 2857, 2703, 
    2551, 2404, 2273, 2146, 2024, 1908, 1805, 1701, 1608, 1515, 1433, 1351, 1276, 1205, 1136, 1073, 1012, 956, 903, 852, 804, 759, 716, 676, 
    638, 602, 568, 536, 506, 478, 451, 426, 402, 379, 358, 338, 319, 301, 284, 268, 253, 239, 226, 213, 201, 190, 179, 169, 159, 151, 142, 134, 
    127, 119, 113, 106, 100, 95, 89, 84, 80, 75, 71, 67, 63
    };
  const int   MIDDLE_C  = 48;

/***
 * SOUND FUNCTIONS
 */

  /***
   * Play a note (from middle C) for ms milliseconds
   */
  void PlayNote(int note, int ms) {
    // restrict to range [25,98] as this range does not
    // get interfered by piezo frequency
    note = constrain(MIDDLE_C + note,25,98);
    int frequency = NOTES[note] * 2;
	PlayTone(frequency, ms);
  }
  
  /***
   * Play a tone in given frequency for x milliseconds
   */
  void PlayTone(int frequency, int ms) {
    unsigned long t = millis();
    int half_period = frequency/2;
  
    // we play only for 1/10 of period as on, this is to prevent piezo's
    // internal frequency from interfering (DC Piezo issue)
    int on_period = half_period/10;
    int off_period = 2*half_period-on_period;
    while (millis()-t<ms) {
      digitalWrite(PIN_buzzerPin,HIGH);
      delayMicroseconds(on_period);
      digitalWrite(PIN_buzzerPin,LOW);
      delayMicroseconds(off_period);
    }
  }

  /***
   * Sound sequence for start
   */
  void PlaySoundStart() {
    PlayNote(0, 200);
    PlayNote(4, 200);
    PlayNote(7, 200);
  }

  /***
   * Sound sequence for mode change
   */
  void PlaySoundChangeMode() {
    PlayNote(7, 100);
  }

