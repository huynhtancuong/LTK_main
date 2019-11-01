/**********************************
   GRobot copyright GARASTEM 2018
*/

#include "GRobot.h"
/* GARABLOCK PLACEHOLDERS (don't remove) */
#include "GRobotMovements.h"





/***
   Variables
*/

// dung de update mode hien tai
byte currentMode = 0;

// dung de check mode truoc la gi
byte previousMode = 0;

/***
   Scratch Generated Code
*/

void begin_Programming() {
      Serial.println("Programming Mode");
      /* GARABLOCK PLACEHOLDERS (don't remove) */
      LTK_setup();
    
}
void loop_Programming() {
      /* GARABLOCK PLACEHOLDERS (don't remove) */
      LTK_loop();
      
}

/***
   Setup code
*/

// SETUP TONG QUAT (khi moi chay hoac reset)
void setup() {
      //Setup Environment
      Serial.begin(9600);
      Wire.begin();
      readPinMap();
    
      // mode button pin
      pinMode(PIN_Mode, INPUT_PULLUP);
      pinMode(PIN_buzzerPin, OUTPUT);
      attachInterrupt(digitalPinToInterrupt(PIN_Mode), ISR_Mode, FALLING);
    
      //Setup PIN & LCD
      SetupPinLayout();
      LCD_Setup();
    
      //Start
      PlaySoundStart();
      Serial.print("Version: ");
      Serial.println(GRobot_Ver);
      Serial.println("G-Robot Started!");
      SetupMode();
}

// SETUP MODES
void SetupMode() {
      BeginMode(&currentMode);
      if (currentMode == 4) {
            begin_Programming();
      }
}

/***
   Loop code
*/
void loop() {
      // Poll xem coi nut Mode co duoc bam khong
      noInterrupts(); currentMode = GetISRMode(); interrupts();
    
      // So sanh coi mode co da duoc thay doi tu lan truoc
      // de biet co phai la lan dau tien vao loop khong
      if (currentMode != previousMode) {
            // give sound feedback
            PlaySoundChangeMode();
            // ket thuc mode truoc
            EndMode(previousMode);
            // goi setup de chay setup code cua cac mode
            SetupMode();
            previousMode = currentMode;
      }
    
      // SWITCH CHO CAC MODE
      //liên tục chạy lại led, khắc phục led rớt nguồn
      if (boardID == 12)//mini Creator
        switch (currentMode)
        {
              case 0: //Red
                strip_1.setPixelColor(0, strip_1.Color(255, 0, 0));
                strip_2.setPixelColor(0, strip_2.Color(255, 0, 0));
                strip_1.show();
                strip_2.show();
                break;
              case 1: //Green
                strip_1.setPixelColor(0, strip_1.Color(0, 255, 0));
                strip_2.setPixelColor(0, strip_2.Color(0, 255, 0));
                strip_1.show();
                strip_2.show();
                break;
              case 2: //Blue
                strip_1.setPixelColor(0, strip_1.Color(0,  0, 255));
                strip_2.setPixelColor(0, strip_2.Color(0,  0, 255));
                strip_1.show();
                strip_2.show();
                break;
              case 3: //Yellow
                strip_1.setPixelColor(0, strip_1.Color(125, 125, 0));
                strip_2.setPixelColor(0, strip_2.Color(125, 125, 0));
                strip_1.show();
                strip_2.show();
                break;
              case 4: //White
                strip_1.setPixelColor(0, strip_1.Color(255, 255, 255));
                strip_2.setPixelColor(0, strip_2.Color(255, 255, 255));
                strip_1.show();
                strip_2.show();
                break;
        }
    
      switch (currentMode)
      {
            case 0: loop_GameBluetooth();   		break;
            case 1: loop_GameIR_Remote();   		break;
            case 2: loop_GameObjectAvoider();     	break;
            case 3: loop_GameS4A();   				break;
            case 4: loop_Programming();     		break;
      }
}
