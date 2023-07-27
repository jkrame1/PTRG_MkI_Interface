# PTRG_MkI_Interface
This repository has a few sketches that can serve as starter code for the Performance Control Reasearch Group's DIY Audio Interface, currently in development.


* Interface_hardware_test - For testing the hardware on the PCB. Use the serial monitor to check the status of the knobs and buttons. Observe the flashing pixels.
* AudioShieldRandomGrainTest - fun test that stereo audio is being produced at the L and R line outputs and the stereo headphone output. 
* PAudio_Interface_0.0.1 - This sketch turns the hardware into a basic audio interface with 2 Line Outputs (copied to the stereo headphone out) and an input that is selectible between the Line Inputs on the PCB or the built-in electret microphone. Clicking "Button 0" toggles between the two inputs and the color of Pixel 0 reflects your selection (yellow = line in, pink - mic). Knob A1 adjust the sensitivity on the input.
* Bit_Crusher-Simple - An example of an audio effect. The built-in mic goes through a bit crusher and comes out of the Line Outputs (and headphone out). Knobs A1 and A2 control effect parameters.
* Basic_Pixels - example code for setting the color of the NeoPixels on the PTRG board
