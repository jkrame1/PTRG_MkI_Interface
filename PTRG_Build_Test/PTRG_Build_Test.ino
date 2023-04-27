//This is code to test the non-audio Hardware on the PTRG Teensy Platform

#include <WS2812Serial.h>  // Non-blocking PJRC Library for Neopixels


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

//Define colors (My pixels are GRB format)
#define RED 0x00FF00
#define GREEN 0xFF0000
#define BLUE 0x0000FF
#define YELLOW 0xB0FF00
#define PINK 0x10FF88
#define ORANGE 0x58E000
#define WHITE 0xFFFFFF

elapsedMillis timer1;
elapsedMillis timer2;
elapsedMillis timer3;

void setup() {
  Serial.begin(9600);
  Serial.println("This code will test your knobs and buttons in a very quick and crude way.");
  delay(1000);

  leds.begin();
  leds.setPixel(0, YELLOW);
  leds.show();
  delay(10);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
}

void loop() {
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


  int refresh1 = map(analogRead(POT_PIN), 0, 1023, 3000, 0);

  if (timer1 > refresh1) {
    leds.setPixel(0, random(0, 16777215));
    leds.show();
    timer1 = 0;
  }

  int refresh2 = map(analogRead(POT_PIN_2), 0, 1023, 3000, 0);

  if (timer2 > refresh2) {
    leds.setPixel(1, random(0, 16777215));
    leds.show();
    timer2 = 0;
  }

  int refresh3 = map(analogRead(POT_PIN_3), 0, 1023, 3000, 0);

  if (timer3 > refresh3) {
    leds.setPixel(2, random(0, 16777215));
    leds.show();
    timer3 = 0;
  }

  delay(50);
}
