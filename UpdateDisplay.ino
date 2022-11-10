/*
 
  U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2
  make -f Makefile.184.uno
  
   text     
   8732               default, all active
   8500     -232      -2.65%    no U8G2_WITH_CLIP_WINDOW_SUPPORT
   8316     -416      -4.76%    no U8G2_WITH_FONT_ROTATION
   8606     -126      -1.44%    no U8G2_WITH_UNICODE
   8692     -40       -0.45%    no U8G2_WITH_INTERSECTION
   8328     -404      -4.62%    no U8G2_WITH_INTERSECTION  no U8G2_WITH_CLIP_WINDOW_SUPPORT
   8718     -14       -4.86%    no U8G2_WITH_HVLINE_SPEED_OPTIMIZATION
   8026     -706      -8.08%    no U8G2_WITH_FONT_ROTATION   no U8G2_WITH_INTERSECTION  no U8G2_WITH_CLIP_WINDOW_SUPPORT
   
   Some flags depend on each other: `U8G2_WITH_INTERSECTION` is required for `U8G2_WITH_CLIP_WINDOW_SUPPORT`, so `U8G2_WITH_INTERSECTION` is partly active as long
   as `U8G2_WITH_CLIP_WINDOW_SUPPORT` is requested.
   
*/
/*
  U8glib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
  This is a page buffer example.    
*/

void UpdateDisplay()
{
  GetLine1();
  GetLine2();
  GetLine3();
  GetLine4();
  GetLine5();
  GetLine6();
}

void GetLine1()
{
 u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0,13);
    //u8g2.print(" "); 
    if (hours <=9)
    {
      u8g2.print("0"); 
    }
    u8g2.print(hours); 
    u8g2.print(":"); 
    if (minutes <=9)
    {
      u8g2.print("0"); 
    }
    u8g2.print(minutes); 
    u8g2.print(":"); 
    if (seconds <=9)
    {
      u8g2.print("0"); 
    }
    u8g2.print(seconds); 
    
    u8g2.setCursor(64,13); //start calendar in the middle
    if (days <=9)
    {
      u8g2.print("0"); 
    }
    u8g2.print(days); 
    u8g2.print("/"); 
    if (months <=9)
    {
      u8g2.print("0"); 
    }
    u8g2.print(months); 
    u8g2.print("/"); 
    u8g2.print(years); 
    u8g2.print(" ");  
}

void GetLine2()
{
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0,24);
    u8g2.print("Up ");
    u8g2.print(SunRiseHour);
    u8g2.print(":");
      if (SunRiseMinute <=9)
      {
        u8g2.print("0"); 
      }
    u8g2.print(SunRiseMinute);
    u8g2.print(" "); 
    u8g2.print(HoursOLight);
    u8g2.setCursor(72,24);
    u8g2.print("Dn ");
    u8g2.print(SunSetHour);
    u8g2.print(":");
      if (SunSetMinute <=9)
      {
        u8g2.print("0"); 
      }
    u8g2.print(SunSetMinute);
}

void GetLine3()
{
    u8g2.setCursor(0,34);
    u8g2.print("DP = ");
    u8g2.print(BME280_DewPoint);
    u8g2.println("*f");
    u8g2.setCursor(72,34);
    // u8g2.print(" AQ = ");
    // u8g2.print(AirQualitySensorValue);
    
    // u8g2.print("012345678901234567890");
    
}

void GetLine4()
{
    u8g2.setCursor(0,44);
    //u8g2.print("012345678901234567890"); 
    u8g2.print(BME280_Humidity); 
    //u8g2.setCursor(32,54); 
    u8g2.print("%RH"); 
    u8g2.setCursor(68,44);
    u8g2.print(BME280_Pressure);
    u8g2.print(" kPa ");
}

void GetLine5()
{
    //u8g2.setCursor(0,54);
    //u8g2.print("012345678901234567890"); 
    u8g2.setCursor(0,54);
    u8g2.print(BME280_Temperature);
    u8g2.print(" *C ");
    u8g2.setCursor(64,54);
    u8g2.print((BME280_Temperature * 9 / 5) + 32);
    u8g2.print(" *f ");
    //u8g2.setCursor(72,54); 
    //u8g2.setCursor(96,54); 
}

void GetLine6()
{
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0,64);
    // u8g2.print("Heat ");
    // u8g2.print(CoopHeat);
    // u8g2.print(" Light ");
    // u8g2.print(CoopLight);    
    // u8g2.print(" Vent ");
    // u8g2.print(CoopVent);
}
