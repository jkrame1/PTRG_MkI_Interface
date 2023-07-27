//This is code to test the Non-audio Hardware (Buttons, Knobs, and Neopixels) on the PTRG Teensy Platform

#include <WS2812Serial.h>  // Non-blocking PJRC Library for Neopixels

//define the pin attachment for the Neopixels
#define PIXEL_PIN 14

//********Required declarations for Neopixels
const int numled = 3;                    //  3 LEDs
byte drawingMemory[numled * 3];          //  3 bytes per LED
DMAMEM byte displayMemory[numled * 12];  // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, PIXEL_PIN, WS2812_GRB);  //create led object
//*********

int maxBrightness = 30; //Set the max value of our RGB elements. 256 is the highest possible.

void setup() {
  leds.begin(); //start the Neopixel (WS2812Serial) library

}


void loop() {
  //get random values for red, green and blue and store them in variables
  int red = random(maxBrightness);
  int green = random(maxBrightness);
  int blue = random(maxBrightness);

  //use a custom function to combine the rgb values into the right format for the pixel library
  int ledColor = rgbColor(red, green, blue);

  //set the colors for the pixels (they will all be the same)
  leds.setPixel(0, ledColor);
  leds.setPixel(1, ledColor);
  leds.setPixel(2, ledColor);

  // Alternatively, pixels could each have thier own values by randomly selecting values for each element
  // Uncomment the following 3 lines to see
  //    leds.setPixel(0, rgbColor(random(maxBrightness),random(maxBrightness),random(maxBrightness)));
  //    leds.setPixel(1, rgbColor(random(maxBrightness),random(maxBrightness),random(maxBrightness)));
  //    leds.setPixel(2, rgbColor(random(maxBrightness),random(maxBrightness),random(maxBrightness)));

  leds.show(); //update the pixel colors


  delay(200); //wait 100 milliseconds then select three new values
}



//This is a custom function to allow the user to input RGB values in a range of 0 - 255
//It will convert the result into a number that is formatted appropriately for the WS2812Serial library
int rgbColor(byte r, byte g, byte b) {
  int grbVal = ((g << 16) + (r << 8) + b);  //the input values are shuffled, bit shifted, and added together
  return grbVal;
}
