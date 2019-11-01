#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "GRobotDevice.h"
#include "GRobotEnvironment.h"
#include "ModeButton.h"
#include "i2cmaster.h"

Adafruit_NeoPixel strip_1, strip_2;



/***************************************
			IR Remote
***************************************/
IRrecv irrecv(PIN_IRrcv_define); 
decode_results results;
byte IRnumberMax = 12; //12 phím 
unsigned long IRcommand[12]={1,1,1,1,1,1,1,1,1,1,1,1};
unsigned long IRtimer=0;
unsigned long IRvalue=0;

void GetIRsignal()
{
	IRvalue = 0;
	if (irrecv.decode(&results)) 
	{
		IRvalue = results.value;
		irrecv.resume(); // Receive the next value
		//Serial.print("value: ");
		//Serial.println(value);
	}
	//return value;
}

bool IRChannel(byte channel)
{
	if(IRcommand[channel]==IRvalue) return 1;
	else return 0;
}

void IR_Learning(byte IRnumber, byte colorLEDRING)
{
	Serial.println("IR_Learning");
	unsigned long value=0;
	byte i = 0;
	if (IRnumber>12) IRnumber=12;
	ledRing_OFF();
	ledRing_pxColor(i,colorLEDRING);
	
	while(i<IRnumber)
	{
		if (irrecv.decode(&results))
		{
			value = results.value;
			irrecv.resume(); // Receive the next value	
					
			if((millis()-IRtimer)>400)
			{
				IRcommand[i] = value;
				Serial.println(IRcommand[i]);
				i++;
				ledRing_pxColor(i,colorLEDRING);				
				buzzer(1);
				delay(20);
				buzzer(0);
			}
			IRtimer = millis();	
		}
	}
	colorWipe(colorToRGB(colorLEDRING), 40);
}

/***************************************
			 RGB LED WS2812b 
***************************************/
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip_1.numPixels(); i++) { // For each pixel in strip...
    strip_1.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip_1.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void ledRing_OFF()
{
	colorWipe(strip_1.Color(0, 0, 0), 0);
}

uint32_t colorToRGB (byte color)
{
	switch(color)
	{
		case 0: return strip_1.Color(255, 0, 0); //Red
				break;
		case 1: return strip_1.Color(0, 255, 0); //Green
				break;
		case 2: return strip_1.Color(0, 0, 255); //Blue
				break;
		case 3: return strip_1.Color(125, 125, 0); //Yellow
				break;
		case 4: return strip_1.Color(255, 255, 255); //White
				break;				
		case 5: return strip_1.Color(0, 125, 125); //Cyan
				break;
		case 6: return strip_1.Color(125, 0, 125); //Magenta
				break;	
					
		default: 	return strip_1.Color(0, 0, 0); //OFF
					break;
	}
}

void ledRing_wipeColor(byte color,byte wait)
{
	colorWipe(colorToRGB(color), wait);
}

void ledRing_wipeRGB(byte red, byte green, byte blue, byte wait)
{
	colorWipe(strip_1.Color(red, green, blue), wait);
}

void ledRing_pxColor(byte pixel,byte color)
{
	if(pixel<12) 
	{
		strip_1.setPixelColor(pixel, colorToRGB(color));
		strip_1.show(); 
	}
}

void ledRing_pxRGB(byte pixel,byte red, byte green, byte blue)
{
	if(pixel<12)
	{
		strip_1.setPixelColor(pixel, strip_1.Color(red, green, blue));
		strip_1.show(); 
	}
}
/***************************************
            ColorSensor 
			I2C Address: 
***************************************/

boolean i2cINIT=1;
byte rgb_data[3]={0};
void iic_read(unsigned char add,unsigned char *data,unsigned char len)
{
	i2c_start_wait(0xb4);
	i2c_write(add);
	i2c_start_wait(0xb5);
	while(len-1)
	{
		*data++=i2c_readAck();
		len--;
    }
    *data=i2c_readNak();
    i2c_stop();
}

byte GetColor(byte field)
{
	if(i2cINIT) 
	{
		i2c_init();
		delay(1);
		i2cINIT=0;
	}
	unsigned char data[9] = {0};
	iic_read(0x0c, data, 3);
	rgb_data[0] = data[0]; //Red
	rgb_data[1] = data[1]; //Green
	rgb_data[2] = data[2]; //Blue
/*
	Serial.print("field: ");
	Serial.print(field);
	Serial.print("\t value:");
    Serial.println(rgb_data[field]);
*/
/*
	Serial.print("r:");
    Serial.print( rgb_data[0]);
    Serial.print(",g:");
    Serial.print( rgb_data[1]);
    Serial.print(",b:");
    Serial.println( rgb_data[2]);
*/	
	if (field < 3)	return rgb_data[field];
	else return 100; //Error: Invalid Input 
/*    
	Serial.print("r:");
    Serial.print( rgb_data[0]);
    Serial.print(",g:");
    Serial.print( rgb_data[1]);
    Serial.print(",b:");
    Serial.println( rgb_data[2]);
*/
}

/***************************************
            DS1307 (Realtime)
			I2C Address: 0x68
***************************************/
const byte NumberOfFields = 7;
int bcd2dec(byte num);
int dec2bcd(byte num);

// day of week: Sunday = 1, Saturday = 7	
int GetRealtime (byte field)
{
	int seconds, minute, hour, day, wday, month, year;
	Wire.beginTransmission(0x68);
	Wire.write((byte)0x00);
	Wire.endTransmission();
	Wire.requestFrom(0x68, NumberOfFields);
	
	seconds = bcd2dec(Wire.read() & 0x7f);
	minute = bcd2dec(Wire.read() );
	hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
	wday   = bcd2dec(Wire.read() );
	day    = bcd2dec(Wire.read() );
	month  = bcd2dec(Wire.read() );
	year   = bcd2dec(Wire.read() );
	year += 2000;    	
	switch (field)
	{
		case 0: return seconds;
		case 1: return minute;
		case 2: return hour;
		case 3: return wday;
		case 4: return day;
		case 5: return month;
		case 6: return year;
		default: return 100; //Error: Invalid Input 
	}
}

int bcd2dec(byte num)
{
        return ((num/16 * 10) + (num % 16));
}
int dec2bcd(byte num)
{
        return ((num/10 * 16) + (num % 10));
}

void SetRealtime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
{
	Wire.beginTransmission(0x68);
	Wire.write(byte(0x00)); 
	Wire.write(dec2bcd(sec));
	Wire.write(dec2bcd(min));
	Wire.write(dec2bcd(hr));
	Wire.write(dec2bcd(wd)); 
	Wire.write(dec2bcd(d)); 
	Wire.write(dec2bcd(mth));
	Wire.write(dec2bcd(yr));
	Wire.endTransmission();
}


/***************************************
   DHT SENSOR (Humidity & Temperature)
***************************************/

bool _lastresult;
byte lastPort=10;
uint8_t data[5];
uint32_t _lastreadtime=-2000, _maxcycles = microsecondsToClockCycles(1000);

boolean flagDHT_Begin=1;
uint32_t expectPulse(int d_Pin, bool level);
boolean read(int d_Pin, bool force);

int GetTemperature(byte port)
{
	
	int d_Pin = pinD[port];
	pinMode(d_Pin, INPUT_PULLUP);	

	int sample ;
	if(read(d_Pin, (lastPort!=port))) 
	{
		sample = data[2]; 
		lastPort=port;
		return (int)sample;
	}
	else 
	{
		lastPort=port;
		return NAN;
	}
}

int GetHumidity(byte port)
{
	int d_Pin = pinD[port];
	pinMode(d_Pin, INPUT_PULLUP);	

	int sample ;
	if(read(d_Pin, (lastPort!=port)))
	{
		sample = data[0];  
		lastPort=port;
		return (int)sample;
	}
	else 
	{
		lastPort=port;
		return NAN;
	}
}

uint32_t expectPulse(int d_Pin, bool level) 
{
  uint32_t count = 0;
  while (digitalRead(d_Pin) == level) if (count++ >= _maxcycles) return 0;
  return count;
}

boolean read(int d_Pin, bool force) 
{
  uint32_t currenttime = millis();
  
  if (!force && ((currenttime - _lastreadtime) < 2000)) return _lastresult;
  _lastreadtime = currenttime;

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

  digitalWrite(d_Pin, HIGH);
  delay(250);

  pinMode(d_Pin, OUTPUT);
  digitalWrite(d_Pin, LOW);
  delay(20);

  uint32_t cycles[80];
  {
    digitalWrite(d_Pin, HIGH);
    delayMicroseconds(40);

    pinMode(d_Pin, INPUT_PULLUP);
    delayMicroseconds(10);

    if (expectPulse(d_Pin, LOW) == 0) 
	{
      _lastresult = false;
      return _lastresult;
    }

	if (expectPulse(d_Pin, HIGH) == 0) 
	{
      _lastresult = false;
      return _lastresult;
    }

    for (int i=0; i<80; i+=2) 
	{
      cycles[i]   = expectPulse(d_Pin, LOW);
      cycles[i+1] = expectPulse(d_Pin, HIGH);
    }
  } 

  for (int i=0; i<40; ++i) 
  {
    uint32_t lowCycles  = cycles[2*i];
    uint32_t highCycles = cycles[2*i+1];
    if ((lowCycles == 0) || (highCycles == 0)) 
	{
      _lastresult = false;
      return _lastresult;
    }

    data[i/8] <<= 1;
	if (highCycles > lowCycles) data[i/8] |= 1;
  }

  if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) 
  {
    _lastresult = true;
    return _lastresult;
  }
  
  else 
  {
    _lastresult = false;
    return _lastresult;
  }
}

/***************************************
				BUZZER
***************************************/

int buzzer (bool state)
{
	analogWrite(PIN_buzzerPin,state*255);
	return state;
}



/***************************************
		DIGITAL - ANALOG WRITE
***************************************/

int wDigital (byte port, bool state)
{
	int d_Pin = pinD[port];
	pinMode(d_Pin, OUTPUT);
	digitalWrite(d_Pin,state);
	return state;
}

int wAnalog (byte port, int state)
{
	if(port >= 4)
	{
		int pwm_Pin = pinD[port];
		analogWrite(pwm_Pin,state);
		return state;
	}
}


/***************************************
		  2-Channel SENSOR
***************************************/
int GetChannel_D(byte port)
{
	int d_Pin = pinD[port];
	pinMode(d_Pin, INPUT);
	return digitalRead(d_Pin);
}
 
int GetChannel_A(byte port)
{
	int value = 0;
	value = analogRead(pinA[port]);
	return (int)value;
}
 
/***************************************
		   FOLLOWLINE SENSOR
***************************************/
int GetFollowLine(byte port, byte slot)
{
	int IR_RIGHT = pinD[port];
	int IR_LEFT = pinA[port];	
	bool IR_LEFT_state=0; //Board BCreator port 1 và 2 ko thể DigitalRead
	
	pinMode(IR_RIGHT, INPUT);
	
	if((boardID==11)&&(slot<2)) 
	{
		if(analogRead(IR_LEFT)>600) IR_LEFT_state = 1;
		else IR_LEFT_state = 0;
	}
	else  
	{
		pinMode(IR_LEFT, INPUT); //Ko phải Board BCreator 
		IR_LEFT_state = digitalRead(IR_LEFT);
	}
	
	if(slot) 	return digitalRead(IR_RIGHT);
	else		return IR_LEFT_state;
}
 
 
/***************************************
		    ULTRASONIC SENSOR
***************************************/
int GetUltrasonicDistance(byte port)
{
	if(boardID==12) delay(100);
	int TRIG = pinA[port]; 
	int ECHO = pinD[port];	
	pinMode(ECHO,INPUT);     
	pinMode(TRIG,OUTPUT); 		
	//trig  A_D8  8
    //echo  A_A0  A0
    unsigned long duration; 
    int distance;           
    digitalWrite(TRIG,0);   
    delayMicroseconds(2);
    digitalWrite(TRIG,1);   
    delayMicroseconds(5);  
    digitalWrite(TRIG,0);
    // timeout at 200ms 
    duration = pulseIn(ECHO,HIGH,200000);
    distance = int(duration/2/29.412);
	if(distance>50) distance=50;
	return(distance);
}
