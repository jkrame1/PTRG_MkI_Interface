#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>        //for Buttons
#include <WS2812Serial.h>  // for Neopixels


// GUItool: begin automatically generated code
AudioSynthWaveformModulated waveformMod1;  //xy=207,159
AudioSynthWaveformModulated waveformMod2;  //xy=208,198
AudioSynthWaveformModulated waveformMod3;  //xy=209,236
AudioEffectEnvelope ENV1;                  //xy=371,157
AudioEffectEnvelope ENV2;                  //xy=371,196
AudioEffectEnvelope ENV3;                  //xy=372,233
AudioMixer4 mixer1;                        //xy=515,185
AudioFilterStateVariable filter1;          //xy=665,184
AudioOutputI2S i2s1;                       //xy=804,182
AudioConnection patchCord1(waveformMod1, ENV1);
AudioConnection patchCord2(waveformMod2, ENV2);
AudioConnection patchCord3(waveformMod3, ENV3);
AudioConnection patchCord4(ENV1, 0, mixer1, 0);
AudioConnection patchCord5(ENV2, 0, mixer1, 1);
AudioConnection patchCord6(ENV3, 0, mixer1, 2);
AudioConnection patchCord7(mixer1, 0, filter1, 0);
AudioConnection patchCord8(filter1, 0, i2s1, 0);
AudioConnection patchCord9(filter1, 2, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=373.33331298828125,373.33331298828125
// GUItool: end automatically generated code



//create objects to read buttons, debounce, and store states
Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);
Bounce button2 = Bounce(2, 15);

//********Variables and objects for Neopixels
const int numled = 3;
const int pixelPin = 14;

byte drawingMemory[numled * 3];          //  3 bytes per LED
DMAMEM byte displayMemory[numled * 12];  // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pixelPin, WS2812_GRB);  //create led object

//Create an array to store the desired wavshapes from the availbile list
int shapeArray[5] = { 0, 3, 11, 9, 7 };  //sine(0), triangle(3), square BL (11), saw BL(9), Samp&Hold(7)
int wav = 0;                             //create a variable to use as an index to select from our curated wav array

void setup() {
  //Setup Buttons
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  AudioMemory(12);  //

  sgtl5000_1.enable();     //start chip on audio shield
  sgtl5000_1.volume(0.5);  // Set volume on headphones

  ENV1.release(600);
  ENV2.release(600);
  ENV3.release(600);

  waveformMod1.begin(0.5, 440, WAVEFORM_SINE);  //Output a waveform, and set the amplitude and base frequency.
  waveformMod2.begin(0.5, 440, WAVEFORM_SINE);  //Output a waveform, and set the amplitude and base frequency.
  waveformMod3.begin(0.5, 440, WAVEFORM_SINE);  //Output a waveform, and set the amplitude and base frequency.

  leds.begin();  //start the Neopixel (WS2812Serial) library
  delay(300);
  Serial.begin(9600);
}

void loop() {
  // Read the buttons and knobs, scale knobs to 0-1.0
  button0.update();
  button1.update();
  button2.update();

  //*****Update the Filter
  float cutoffFreq = analogRead(A3) + 1 * 20;
  filter1.frequency(cutoffFreq);

  //Get Base Frequency
  float baseFreq = analogRead(A2) + 1 * 20;
  
  //Set the frequencies of the three oscillators to harmonic relationships (or not)
  waveformMod1.frequency(baseFreq);
  waveformMod2.frequency(baseFreq * 1.5);  // * 1.3 for a minor third, 1.5 for a perfect fifth, 2 for an octave
  waveformMod3.frequency(baseFreq * 2);    // * 1.3 for a minor third, 1.5 for a perfect fifth, 2 for an octave



  if (button0.fallingEdge()) {  //Start Envelope when button pressed
    ENV1.noteOn();
    //use a custom function to combine the rgb values into the right format for the pixel library
    int ledColor = rgbColor(10, 10, 0);
    leds.setPixel(0, ledColor);
    leds.show();  //update the pixel colors
  }

  if (button0.risingEdge()) {  //Go into Release on Envelope whe button pressed
    ENV1.noteOff();
  }

  if (button1.fallingEdge()) {
    ENV2.noteOn();
    int ledColor = rgbColor(10, 0, 10);
    leds.setPixel(1, ledColor);
    leds.show();  //update the pixel colors
  }

  if (button1.risingEdge()) {
    ENV2.noteOff();
  }

  if (button2.fallingEdge()) {
    ENV3.noteOn();
    int ledColor = rgbColor(0, 10, 10);
    leds.setPixel(2, ledColor);
    leds.show();  //update the pixel colors
  }

  if (button2.risingEdge()) {
    ENV3.noteOff();
  }

  //******Turn off LEDs when Envelopes have finshed the Release stage
  if (!ENV1.isActive()) {
    int ledColor = rgbColor(0, 0, 0);
    leds.setPixel(0, ledColor);
    leds.show();  //update the pixel colors
  }

  if (!ENV2.isActive()) {
    int ledColor = rgbColor(0, 0, 0);
    leds.setPixel(1, ledColor);
    leds.show();  //update the pixel colors
  }

  if (!ENV3.isActive()) {
    int ledColor = rgbColor(0, 0, 0);
    leds.setPixel(2, ledColor);
    leds.show();  //update the pixel colors
  }

  //read the first knob and map the value to select a waveform from our curated array
  //wav = map(analogRead(A1), 0, 1023, 0, 4);

  //Pots are logrithmic, so map() function didn't work well for dividing the pot into rougly equal zones
  int rawKnob1Val = analogRead(A1);
  Serial.println(rawKnob1Val);

  if (rawKnob1Val < 50) {
    wav = 0;
  }

  else if (rawKnob1Val < 100) {
    wav = 1;
  }

  else if (rawKnob1Val < 180) {
    wav = 2;
  }

  else if (rawKnob1Val < 800) {
    wav = 3;
  }

  else {
    wav = 4;
  }
  waveformMod1.begin(shapeArray[wav]);  //update Waveform
  waveformMod2.begin(shapeArray[wav]);  //update Waveform
  waveformMod3.begin(shapeArray[wav]);  //update Waveform


  //short delay for stability
  delay(10);
}



//This is a custom function to allow the user to input RGB values in a range of 0 - 255
//It will convert the result into a number that is formatted appropriately for the WS2812Serial library
int rgbColor(byte r, byte g, byte b) {
  int grbVal = ((g << 16) + (r << 8) + b);  //the input values are shuffled, bit shifted, and added together
  return grbVal;
}
