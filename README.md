# PTRG_MkI_Interface
This repository has a few folders with sketches that can serve as starter code for the Performance Control Reasearch Group's DIY Audio Interface Teensy Platform, currently in development.

01_HARDWARE BUILD TEST
* Audio_Interface_0.0.1 - This sketch turns the hardware into a basic USB audio interface with 2 Line Outputs (copied to the stereo headphone out) and an input that is selectible between the stereo Line Inputs on the PCB or the built-in electret microphone. Clicking "Button 0" toggles between the Line In and Mic In and the color of Pixel 0 reflects your selection (yellow = line in, pink - mic). Knob A1 adjust the sensitivity on the input.
* Interface_hardware_test - For testing the hardware on the PCB. Use the serial monitor to check the status of the knobs and buttons. Observe the flashing pixels.

02_SMALL EXAMPLES
* Basic_Pixels - example code for setting the color of the NeoPixels on the PTRG board
* Bit_Crusher-Simple - An example of an audio effect. The built-in mic goes through a bit crusher and comes out of the Line Outputs (and headphone out). Knobs A1 and A2 control effect parameters.
* PTRG_SynthVoice1 - a quick example of making a simple synth voice using the Teensy Platform

03_FUN SKETCHES
* AudioShieldRandomGrainTest - fun test that stereo audio is being produced at the L and R line outputs and the stereo headphone output.
* Blinking_Pixels - ?


