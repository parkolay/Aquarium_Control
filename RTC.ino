/*
 * UpdateTime - Reads the RTC and set multiple varibles for use in other parts of the code
 *  pinout +5V-SDA-SCL-N/C-GND I think the N/C is an alarm pin...?
 * 
 * DAP - 09-17-2021 Initial rev
 * DAP - 09-28-2021 added more vars 
 * DAP - 11-11-2022 updated setupRTC() 
 * DAP - 11-11-2022 Added DST SW and SunRise/SunSet
 */

void SetupRTC()
{
  //initialize RTC
  rtc.begin();
 
  if (! rtc.isrunning()) //if RTC is not running try to set it 
  {
    char t[32];
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
    DateTime now = rtc.now();
    sprintf(t, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
    Serial.print(F("Date/Time: "));
    Serial.println(t);
  }

  if (rtc.isrunning())  //if RTC is running, send out time
  {
    Serial.println("RTC has begun");
    UpdateRTC();
    GetSunriseSunset();
  }
  
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