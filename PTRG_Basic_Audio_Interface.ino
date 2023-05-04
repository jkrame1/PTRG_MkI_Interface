//This sketch creates a USB audio interface using the Teensy 4.x and AudioShield REV D.
//It uses 1 button (pin 0), one knob (A1), and 1 Neopixel (pin 14).
//The button selects the input -- either the line inputs from the audio sheild or the 
//built in microphone (you must attach one to the shield yourself if you want to use it)
//The color of the Neopixel indicates which input is selected and the knob scales the 
//input.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Bounce2.h>       //for button
#include <WS2812Serial.h>  // for Neopixels

// Create A Button OBJECT
Button button1 = Button();

// SET A VARIABLE TO STORE THE INPUT STATE
bool inState = 0;  //0 = mic, 1 = lineIn

//********Variables and objects for Neopixels
const int numled = 3;
const int pixelPin = 14;

byte drawingMemory[numled * 3];          //  3 bytes per LED
DMAMEM byte displayMemory[numled * 12];  // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pixelPin, WS2812_GRB);  //create led object

//Define colors (My pixels are GRB format)
#define RED 0x00FF00
#define GREEN 0xFF0000
#define BLUE 0x0000FF
#define YELLOW 0xB0FF00
#define PINK 0x10FF88
#define ORANGE 0x58E000
#define WHITE 0xFFFFFF

// GUItool: begin automatically generated code for audio system
AudioInputUSB usbIn;      //xy=264,71
AudioInputI2S i2sIn;      //xy=267,183
AudioRecordQueue queue2;  //xy=459,283
AudioRecordQueue queue1;  //xy=460,247
AudioOutputI2S i2sOut;    //xy=577,69
AudioOutputUSB usbOut;    //xy=578,182
AudioConnection patchCord1(usbIn, 0, i2sOut, 0);
AudioConnection patchCord2(usbIn, 1, i2sOut, 1);
AudioConnection patchCord3(i2sIn, 0, queue1, 0);
AudioConnection patchCord4(i2sIn, 0, usbOut, 0);
AudioConnection patchCord5(i2sIn, 1, queue2, 0);
AudioConnection patchCord6(i2sIn, 1, usbOut, 1);
AudioControlSGTL5000 sgtl5000;  //xy=582,378
// GUItool: end automatically generated code

#define SD_CS_PIN 10
#define BUTTON_PIN 0
#define POT_PIN A1

void setup() {
  Serial.begin(9600);
  button1.attach(BUTTON_PIN, INPUT_PULLUP);  // connect button object to button pin
  button1.interval(15);                      // DEBOUNCE INTERVAL IN MILLISECONDS

  leds.begin();
  leds.setPixel(0, YELLOW);
  leds.show();
  delay(10);

  AudioMemory(60);
  sgtl5000.enable();
  sgtl5000.inputSelect(inState);
  sgtl5000.volume(0.5);
  sgtl5000.adcHighPassFilterDisable();  //disable HPF to reduce noise on the LineInput
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  button1.update();  //update (read) button
  if (button1.fell()) {
    if (inState == 0) {
      inState = 1;
      sgtl5000.inputSelect(inState);
      leds.setPixel(0, PINK);  //which Pixel, which color
      leds.show();             //change the pixel
    }

    else if (inState == 1) {
      inState = 0;
      sgtl5000.inputSelect(inState);
      leds.setPixel(0, YELLOW);
      leds.show();
    }
  }


  if (inState == 1) {
    float gain = map(analogRead(POT_PIN), 0, 1023, 0, 36);
    sgtl5000.micGain(gain);
  }

  else if (inState == 0){
    int level = map(analogRead(POT_PIN), 0, 1023, 0, 15);
    sgtl5000.lineInLevel(level);
  }



  delay(15);
}
