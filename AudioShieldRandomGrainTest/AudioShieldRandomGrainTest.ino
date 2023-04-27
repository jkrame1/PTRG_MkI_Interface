//This code uses the Audio Library to genrate a
//random composition using The Audio Shield

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine sine1;   //xy=193,304
AudioSynthWaveformSine sine2;   //xy=195,349
AudioEffectGranular granular1;  //xy=356,301
AudioEffectGranular granular2;  //xy=366,358
AudioOutputUSB usbOut;          //xy=699,253
AudioOutputI2S i2sOut;          //xy=702,296
AudioConnection patchCord1(sine1, granular1);
AudioConnection patchCord2(sine2, granular2);
AudioConnection patchCord3(granular1, 0, usbOut, 0);
AudioConnection patchCord4(granular1, 0, i2sOut, 0);
AudioConnection patchCord5(granular2, 0, usbOut, 1);
AudioConnection patchCord6(granular2, 0, i2sOut, 1);
AudioControlSGTL5000 sgtl5000;  //xy=385,518
// GUItool: end automatically generated code

float notes[34] = {32.70,  38.89,  43.65,  49.00,  51.91,  58.27,  65.41,  77.78,  87.31,  98.00,  103.83,  116.54,  130.81,  155.56,  174.61,  196.00,  207.65,  233.08,  261.63,  311.13,  349.23,  392.00,  415.30,  466.16,  523.25,  622.25,  698.46,  783.99,  830.61,  932.33,  1046.50,  1396.91,  1567.98,  2093.00};

//set up a few timers
elapsedMillis timer1;
elapsedMillis timer2;
elapsedMillis timer3;

//set aside some memory for granular object
#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];
int16_t granularMemory2[GRANULAR_MEMORY_SIZE];

void setup() {
  randomSeed(analogRead(A4));
  AudioMemory(60);
  sgtl5000.enable();
  sgtl5000.volume(0.4);

  sine1.amplitude(.5);
  sine1.frequency(220);
  sine2.amplitude(.5);
  sine2.frequency(220);

  // the Granular effect requires memory to operate
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  granular2.begin(granularMemory2, GRANULAR_MEMORY_SIZE);
}

void loop() {
  int refresh1 = 4000;  //change parameter every 2000ms (twice per second)
  if (timer1 > refresh1) {
    float freq = notes[random(0, 35)]; //uncomment for quantized notes
    //int freq = random(80, 800); //comment this out for quantized
    sine1.frequency(freq);
    //freq = notes[random(0, 33)]; //uncomment for quantized notes
    sine2.frequency(freq/2);
    timer1 = 0;
  }

  int refresh2 = 200;  //This is a fun one to change!! 200

  if (timer2 > refresh2) {
    granular1.beginFreeze(random(10, 12800));
    granular2.beginFreeze(random(100, 12800));
    timer2 = 0;
  }


  int refresh3 = random(300, 2000);  //change parameter randomly
  if (timer3 > refresh3) {
    granular1.beginPitchShift(random(0, (1200 / 3)));
    granular2.beginPitchShift(random(2, (12800 / 3)));
    timer3 = 0;
  }
}
