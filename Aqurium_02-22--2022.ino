/*
*/
/*  This sketch sets up a small OLED display and pulls analog signals from two sensors 
 * (HTM1735LF (RH && Temp) && MQ135(air quality --> SnO2 detects CO2 && VOC))
 * 
 *  Requirements:
 *
 *  * Nano or other Arduino board
 *  * Arduino 1.8.8+ IDE
 *  * Library: U8g2lib.h --> u8g2 by oliver was used
 *  * Library: RTClib.h -->  DS3231 RTC was used
 *
 * 
 * 
 *  // Pinout
 *  //  MQ135 analog Output --> A00
 *  //  RH Analog Output    --> A01
 *  //  Temp Analog Output  --> A02 Tied HIGH W/ 10k Ohm resistor 
 *  //  SCL                 --> A04
 *  //  SDA                 --> A05
 *   
 *   
 *   
 *   
 *   Created: Feb 6, 2019 by Dan Parkolay (with a lot of help from a lot of other people)
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <U8g2lib.h>
#include "RTClib.h"


//#ifdef U8X8_HAVE_HW_I2C
//#include <Wire.h>
//#endif

#define SEALEVELPRESSURE_KPA (101.325)
#define SEALEVELPRESSURE_HPA (1013.25)

// Which pin is connected to the NeoPixels?
#define PIN 2
//Add a button as an input
#define BUTTON_1  4
// How many NeoPixels are attached?
#define NUMPIXELS 10

int PixelCycles = 6;  //set a number of cycles before turning OFF pixels

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

Adafruit_BME280 bme280;// I2C

DS3231 rtc;       //DS3231 rtc support;


unsigned long delayTime;

int seconds = 0;  // varible to store the seconds from clock
int minutes = 0;  // varible to store the minutes from clock
int hours   = 0;  // varible to store the hours from clock
int days    = 0;  // varible to store the seconds from clock
int months  = 0;  // varible to store the minutes from clock
int years   = 0;  // varible to store the hours from clock


void setup(void) 
{
  Serial.begin(115200);
  Serial.println("initializing...");

  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(BUTTON_1, INPUT_PULLUP);   // initialize the button pin as an input:
      
unsigned status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme280.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme280.sensorID(),16);
        Serial.print("   ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("   ID of 0x60 represents a BME 280.\n");
        Serial.print("   ID of 0x61 represents a BME 680.\n");
        while (1);
    }
  
  u8g2.begin();
  u8g2.clearDisplay();
    // connect AREF to 3.3V and use that as VCC, less noisy!  
    //thank you for the tip Lady Ada
  analogReference(EXTERNAL);  

  rtc.begin();          //start the clock
//This will need to be commented out to run other code
//If NOT, the clock will rest to the compile time every time it is powered ON
//rtc.adjust(DateTime(__DATE__, __TIME__)); // force the adjust if the cock is already running
}

void loop(void) 
{
  UpdateMQ135();
  UpdateBME280();
  UpdateTime();
  UpdateLight();


  delay(100);
  u8g2.firstPage();
  do 
  {

    UpdateDisplay();
  } 
  while ( u8g2.nextPage() );
  //delay(1000);
}
