#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s2;                 //xy=333.08331298828125,125.08332824707031
AudioEffectBitcrusher bitcrusher1;  //xy=471.08331298828125,117.08332824707031
AudioOutputI2S i2s1;                //xy=632.0833129882812,151.08334350585938
AudioConnection patchCord1(i2s2, 0, bitcrusher1, 0);
AudioConnection patchCord2(bitcrusher1, 0, i2s1, 0);
AudioConnection patchCord3(bitcrusher1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=484.08331298828125,414.08331298828125
// GUItool: end automatically generated code



void setup() {
  AudioMemory(10);         //allocate some memory for the Teensy Audio System
  sgtl5000_1.enable();     //Turn on the audio shield
  sgtl5000_1.volume(0.5);  //Set the Headphone volume (0.8 is pretty darn loud!)
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC); //Set the source to the built-in mic - line would be AUDIO_INPUT_LINEIN 
  sgtl5000_1.micGain(37);  //Gain is in dB, values between 0 - 63.
}

void loop() {
  //Read the knobs, map the input range to relevant output ranges, then store them as viariables to be used in Bit Crusher functions
  int sampRate = map(analogRead(A1), 0, 1023, 44100, 0); //knob range is 0 - 1023. Sample rate goes from 0 - 44100Hz
  int bitDepth = map(analogRead(A2), 0, 1023, 16, 0);  //knob range is 0 - 1023. Bit depth goes from 1 - 16

  bitcrusher1.sampleRate(sampRate); //set the sample rate using the variable "sampRate"
  bitcrusher1.bits(bitDepth); //set the bit depth using the variable "bitDepth"
}
