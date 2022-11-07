 /*
 * UpdateTime - Reads the RTC and set multiple varibles for use in other parts of the code
 * 
 * DAP - 09-17-2021 Initial rev
 * DAP - 09-28-2021 added more vars 
 */

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
}// end void UpdateTime()
