//This is code to test the Non-audio Hardware (Buttons, Knobs, and Neopixels) on the PTRG Teensy Platform

#include <WS2812Serial.h>  // Non-blocking PJRC Library for Neopixels

//define all the pin attachments for the knobs, buttons, Neopixels, and SD Card
#define SD_CS_PIN 10
#define BUTTON_PIN 0
#define BUTTON_PIN_2 1
#define BUTTON_PIN_3 2
#define POT_PIN A1
#define POT_PIN_2 A2
#define POT_PIN_3 A3
#define PIXEL_PIN 14

//********Variables and objects for Neopixels
const int numled = 3;

byte drawingMemory[numled * 3];          //  3 bytes per LED
DMAMEM byte displayMemory[numled * 12];  // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, PIXEL_PIN, WS2812_GRB);  //create led object
//*********


void setup() {
  Serial.begin(9600); //open a serial connection to read values on the serial monitor
  Serial.println("This code will test your knobs, buttons, and lights.");
  delay(1000); //

  //configure the teensy button pins to read "LOW" when pressed
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);

  leds.begin(); //start the Neopixel (WS2812Serial) library

}

void loop() {
  //Read the values from the knobs and map to an appropriate range for our colors
  //store those values in variables named "red", "green", and "blue"
  int red = map(analogRead(POT_PIN), 0, 1023, 0, 255);
  int green = map(analogRead(POT_PIN_2), 0, 1023, 0, 255);
  int blue = map(analogRead(POT_PIN_3), 0, 1023, 0, 255);

  //use a custom function to combine the rgb values into the right format for the pixel library
  int ledColor = rgbColor(red, green, blue);

  //read the first button. If it is NOT PRESSED, set the pixel color according to the knobs
  //otherwise, set the pixel to off
  if (digitalRead(BUTTON_PIN) == HIGH) {
    leds.setPixel(0, ledColor);
  }
  else {
    leds.setPixel(0, 0);
  }

  //read the second button. If it is NOT PRESSED, light the pixel with a different color
  if (digitalRead(BUTTON_PIN_2) == HIGH) {
    leds.setPixel(1, rgbColor(blue, red, green)); //notice r, g, and b are shifted
  }
  else {
    leds.setPixel(1, 0);
  }

  //read the third button. If it is NOT PRESSED, light the pixel with another different color
  if (digitalRead(BUTTON_PIN_3) == HIGH) {
    leds.setPixel(2, rgbColor(green, blue, red));
  }
  else {
    leds.setPixel(2, 0);
  }

  leds.show(); //update the pixel colors

  //print a bunch of information to the Serial Monitor for some detailed feedback
  Serial.print("Button 1: ");
  Serial.println(digitalRead(BUTTON_PIN));
  Serial.print("Button 2: ");
  Serial.println(digitalRead(BUTTON_PIN_2));
  Serial.print("Button 3: ");
  Serial.println(digitalRead(BUTTON_PIN_3));
  Serial.print("Knob 1: ");
  Serial.println(analogRead(POT_PIN));
  Serial.print("Knob 2: ");
  Serial.println(analogRead(POT_PIN_2));
  Serial.print("Knob 3: ");
  Serial.println(analogRead(POT_PIN_3));

  Serial.print("red = ");
  Serial.println(red);

  Serial.print("green = ");
  Serial.println(green);

  Serial.print("blue = ");
  Serial.println(blue);

  Serial.print("Packed Number = ");
  Serial.println(ledColor);

  delay(50); //a short delay to improve stability.
}

//This is a custom function to allow the user to input RGB values in a range of 0 - 255
//It will convert the result into a number that is formatted appropriately for the WS2812Serial library

int rgbColor(byte r, byte g, byte b) {
  int grbVal = ((g << 16) + (r << 8) + b);
  return grbVal;
}
