void UpdateLight()
{
   // int Button_1Value = digitalRead(BUTTON_1);    //set up an int var and set it to the value read on BUTTON_1

//  if (Button_1Value == LOW)  //this will compare the int var above to a value (HIGH)
//  {                           //if you push the button the cycle will start all over again

    while(PixelCycles > 0)    //we want to do something a bunch of times or while some condition is "right"
    {
      rainbow(10);           //here we are calling a function to run (look for it below)
      rainbowCycle(50);      //another function call
      --PixelCycles;          //this is a decrement, which means we take the var and subtract '1' from it's value
    }
   
    if (PixelCycles <= 0) //check to see if we should turn off pixels
    {
      TurnOFFPixels();    //turn off pixels
      PixelCycles = 6;    //reset the count down
    }    
//  }//end if (Button_1Value == HIGH)
//  else
//  {
//            //I got nothing for here yet
//  }

}//end void loop()
  

void rainbow(uint8_t wait)
{
  uint16_t i, j;

  for(j=0; j<64; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 63));
    }
    pixels.show();
    delay(wait);
  }
}//end void rainbow(uint8_t wait)

void rainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  for(j=0; j<64*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 64 / pixels.numPixels()) + j) & 63));
    }
    pixels.show();
    delay(wait);
  }
}// end void rainbowCycle(uint8_t wait)

// Input a value 0 to 63 to get a color value. This was lowered from 255 as they were super bright to look at comfortaly 
//lowering the output also reduces the current draw
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
  WheelPos = 63 - WheelPos;
 
  if(WheelPos < 21)
  {
    return pixels.Color(63 - WheelPos * 3, 0, WheelPos * 3);
  }
 
  else if(WheelPos < 42)
  {
    WheelPos -= 21;
    return pixels.Color(0, WheelPos * 3, 63 - WheelPos * 3);
  }
 
  else
  {
     WheelPos -= 42;
     return pixels.Color(WheelPos * 3, 63 - WheelPos * 3, 0);
  }
}//end uint32_t Wheel(byte WheelPos)

void TurnOFFPixels()
{
    pixels.clear();//set to 0
    pixels.show();//light 'em up (or not...)
    //pixels.setPixelColor(0,pixels.Color(0,0,0));
    //pixels.Show();
}
