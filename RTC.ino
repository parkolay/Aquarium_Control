void SetupRTC()
{
  //initialize RTC
  rtc.begin();
      //rtc.adjust(DateTime(__DATE__, __TIME__));   //--> this is to force the time is it is set to something already
    if (! rtc.isrunning()) 
    {
      Serial.println("RTC is NOT running!");
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(__DATE__, __TIME__));
      
    }

  Serial.println("RTC has begun");
}

void UpdateRTC()
{
    DateTime now = rtc.now();
    char buf[100];          //buffer for the RTC TimeDate Stamp
    strncpy(buf,"DD.MM.YYYY  hh:mm:ss\0",100);
    Serial.println(now.format(buf));
    delay(1000);
}
void UpdateTime()
{
  DateTime now = rtc.now();
//  strncpy(TimeBuffer,"DD.MM.YY  hh:mm:ss\0",100); //this formats the TimeBuffer array
//  TimeReadout = (now.format(TimeBuffer));
//  Serial.println(strncpy(TimeReadout, TimeBuffer, 20);
  //Serial.println(now.format(TimeBuffer));
      
    seconds = now.second();
    minutes = now.minute();
    hours   = now.hour();
    days    = now.day();
    months  = now.month();
    years   = (now.year()-2000);  //remove the first 2 digits

    //     char buf[100];          //buffer for the RTC TimeDate Stamp
    // strncpy(buf,"DD.MM.YYYY  hh:mm:ss\0",100);
    // Serial.println(now.format(buf));
    if (DSTSwitch_mode == 0)
    {
      hours -= 1;
      Serial.println(hours);
    }
    
}  // end void UpdateTime()

void GetSunriseSunset()
{
 
  calcSunriseSunset((years+2000), months, days, latitude, longitude, transit, sunrise, sunset);
  
  //Pull whole values from the decimal equivalents
  SunRiseHour = (sunrise + utc_offset);   
  SunRiseMinute = (((sunrise + utc_offset)-SunRiseHour) * 60);
  SunSetHour = (sunset + utc_offset);
  SunSetMinute = (((sunset + utc_offset)-SunSetHour) * 60);

  HoursOLight = (sunset - sunrise);

  // Print Debug results
  if (DebugOn == true)
  { 
  Serial.print("SunRise ");
  Serial.println((sunrise + utc_offset));   //this ended up being a decimal hour
  Serial.print(SunRiseHour);
  Serial.print(":");
    if (SunRiseMinute <=9)
    {
      Serial.print("0"); 
    }
  Serial.println(SunRiseMinute);
  Serial.print("Hours Of Light ");
  Serial.println(HoursOLight);
  Serial.print("SunSet ");
 // Serial.println((transit + utc_offset));
  Serial.println((sunset + utc_offset));
    Serial.print(SunSetHour);
  Serial.print(":");
    if (SunSetMinute <=9)
    {
      Serial.print("0"); 
    }
  Serial.println(SunSetMinute);
  }//if (DebugOn == true)
}//end void GetSunriseSunset()