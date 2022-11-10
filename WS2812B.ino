void SetupNeoPix()
{
  pixels.begin(); // This initializes the NeoPixel library.
    Serial.println("WS2812b has begun...");
}

void UpdateNeo_Pix()
{
  while(PixelCycles > 0)    //we want to do something a bunch of times or while some condition is "right"
      {
        rainbow(100);           //here we are calling a function to run (look for it below)
        //rainbowCycle(100);      //another function call
        --PixelCycles;          //this is a decrement, which means we take the var and subtract '1' from it's value
      }
    
      if (PixelCycles <= 0) //check to see if we should turn off pixels
      {
        TurnOFFPixels();    //turn off pixels
        PixelCycles = 6;    //reset the count down 
      }

}//end UpdateNeo_Pix()


void rainbow(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<pixels.numPixels(); i++) 
    {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}//end void rainbow(uint8_t wait) 

void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) 
    {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}// end void rainbowCycle(uint8_t wait) 

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  
  else if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  
  else 
  {
     WheelPos -= 170;
     return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}//end uint32_t Wheel(byte WheelPos)

void TurnOFFPixels()
{
    pixels.clear();//set to 0
    pixels.show();//light 'em up (or not...)
    //pixels.setPixelColor(0,pixels.Color(0,0,0));
    //pixels.Show();
}
