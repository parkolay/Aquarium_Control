/* Aquarium_Control
//Anya's Nightlight --> using code from varioius sources listed below;
// Button Cycler example for the rainbow animations
//NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

 *  // Pinout
 *  //  Interrupt           --> PIN D02 with INT0
 *  //  BUTTON              --> PIN D03 (INT1)
 *  //  NEO_PIXEL(WS2812B)  --> PIN D04
 *  //  SCL                 --> A04 Tied HIGH W/ 3k3 Ohm resistor
 *  //  SDA                 --> A05 Tied HIGH W/ 3k3 Ohm resistor
*/
#include "Arduino.h"

#include "Wire.h"
#include "U8g2lib.h"
#include "RTClib.h"
#include "SparkFunBME280.h"
#include "Adafruit_NeoPixel.h"
#include "SolarCalculator.h"

// Which pin on the Arduino is connected to the NeoPixels?
#define NEO_PIN 4

//Add a button as an input
#define BUTTON_1  3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8

int PixelCycles = 6;  //set a number of cycles before turning OFF pixels 1 cycle ~= 150 sec

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

//Initialize BME280
BME280 bme280;

//Initialize SSD1306 Display
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//Initialize RTC
DS3231 rtc;

int DSTSwitch_mode = 1;
int DelayPeriod = 10;           //setup for using millis() instead of delay()
unsigned long Current_Time = 0; //the "other part" of millis() (roll over around 50 days which might not work in this application)

int seconds = 0;  // varible to store the seconds from clock
int minutes = 0;  // varible to store the minutes from clock
int hours   = 0;  // varible to store the hours from clock
int days    = 0;  // varible to store the seconds from clock
int months  = 0;  // varible to store the minutes from clock
int years   = 0;  // varible to store the hours from clock

// Location
double transit, sunrise, sunset;
double latitude = 39.7565;
double longitude = -77.966;
double HoursOLight = 0;
int utc_offset = -5;

int SunRiseHour = 0;
int SunRiseMinute = 0;
int SunSetHour = 0;
int SunSetMinute = 0;

bool DebugOn = true; //set to true for debug serial messages

void setup()    //This code is only ran at the very beginning of startup
{
  
  
  Serial.begin(57600);
  Wire.begin();
  Serial.println("Initializing Aquarium Control 11//2022...");
  Serial.println("Initializing WS2812b...");
  SetupNeoPix();
  SetupRTC();   //this will need to be commented out if not connected 
  
  u8g2.begin();
  Serial.println("SD1306 has begun...");
    // connect AREF to 3.3V and use that as VCC, less noisy!  
    //thank you for the tip Lady Ada
  analogReference(EXTERNAL);  

  SetupBME280();
  pinMode(BUTTON_1, INPUT_PULLUP);   // initialize the button pin as an input:
                                     //set as INPUT_PULLUP for condition where there is no switch present
				     // use soft pull down with switch
}

void loop() 
{
  int Button_1Value = digitalRead(BUTTON_1);    //set up an int var and set it to the value read on BUTTON_1

  if (Button_1Value == HIGH)  //this will compare the int var above to a value (HIGH) 
  {                           //if you push the button the cycle will start all over again
    UpdateTime();

    u8g2.firstPage();
      //delay(100); //there is already enough going on 
      do 
      {
        UpdateDisplay();  //this will jump to update the display
      } 
      while ( u8g2.nextPage() );
    UpdateNeo_Pix();
    
  }//end if (Button_1Value == HIGH)
  else 
  {
            //I got nothing
  }
}//end void loop() 


