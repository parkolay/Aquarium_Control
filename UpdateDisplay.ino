/*
    GetLine1();//Text describing device
    GetLine2();//air quality reading time of date  date
  //GetLine3();//not used at this time
    GetLine4();//Humidity % Rh  pressure kPa readings
    GetLine5();//Temp *f  Temp *c readings
  //GetLine6();//not used at this time

    
*/

void UpdateDisplay()
{
  GetLine1();
  GetLine2();
  //GetLine3();
  GetLine4();
  GetLine5();
  //GetLine6();
}

void GetLine1()
{
    u8g2.setFont(u8g2_font_ncenB12_tr);
    //u8g2.drawStr(0,13,"Air Quality Sensor");//I don't know if this will fit on display :(
    u8g2.drawStr(0,13,"AirQltySensor");
}

void GetLine2()
{
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0,24);
    u8g2.print(AirQualitySensorValue);
    
    //Slide cursor over to add clock to line 2
    u8g2.setCursor(32,24);  //put clock in the middle
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
    
    u8g2.setCursor(83,24); //put calendar in the right side
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

void GetLine3()
{
    u8g2.setCursor(0,34);
    u8g2.print("012345678901234567890"); 
//    u8g2.print(samples[1]); 
//    u8g2.setCursor(42,34);
//    u8g2.print(TempSensorAverage); 
    
}

void GetLine4()
{
    u8g2.setCursor(0,44);
    //u8g2.print("012345678901234567890"); 
    u8g2.print(BME280_Humidity); 
    //u8g2.setCursor(32,44); 
    u8g2.print("%RH"); 
    u8g2.setCursor(60,44);
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
    //u8g2.setCursor(0,64);
    //u8g2.print("012345678901234567890"); 

}
