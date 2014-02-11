
#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
uint32_t teal = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t purple = strip.Color(220, 30, 30);
uint32_t deep = strip.Color(255, 128, 0);
uint32_t off = strip.Color(0, 0, 0);
uint32_t white = strip.Color(255, 255, 255);
int sensorValue = 0;
int truevalue = 0;
int truevalueold = 0;
int truevalueoldagain = 0;
int v4 = 0;
int v5 = 0;
int v6 = 0;
int v7 = 0;
int v8 = 0;
int ledout = 0;

void setup() {
  strip.begin();
  strip.setBrightness(123);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  sensorValue = analogRead(A0);
  v8 = v7;
  v7 = v6;
  v6 = v5;
  v5 = v4;
  v4 = truevalueoldagain;
  truevalueoldagain = truevalueold;
  truevalueold = truevalue;
  truevalue = abs(sensorValue - 512)*2;
  truevalue = map(truevalue, 0, 850, 0, 29);
  ledout = (truevalue + truevalueold + truevalueoldagain + v4 + v5 + v6 + v7 + v8)/8;
  for (int i = 0; i < ledout; i++)
  {
    strip.setPixelColor(29 + i, chooseColor(29 + i));
    strip.setPixelColor(29 - i, chooseColor(29 - i));
  }
  for (int i = ledout; i < 31; i++)
  {
    strip.setPixelColor(29 + i, off);
    strip.setPixelColor(29 - i, off);
  }
  //strip.setPixelColor(29, white);
  //strip.setPixelColor(30, white);
  strip.show();
  delay(1);
  
}

void fillLEDs(int ledval)
{
}

uint32_t chooseColor(int value)
{
  if (value >= 25 && value < 35)
    return white;
  else if (value >= 20 && value < 40)
    return blue;
   else if (value >= 10 && value < 50)
    return teal;
  else
    return white;
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

