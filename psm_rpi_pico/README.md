# How to Flash
1. Open ARduino IDE 2
2. Make sure you have installed Raspberry Pico line of microcontrollers, if not go to this turtorial: https://randomnerdtutorials.com/programming-raspberry-pi-pico-w-arduino-ide/
3. Now after you are done, restart arduino IDE
4. Slelect board in Raspberry Pico series called: Waveshare RP2040 Zero
5. Now Compile the code
6. Then in top left corner of arduino IDE slelect "Sketch" -> "Export Compilled Binary"
7. Now exit Arduino IDE, in the same folder as this read me file in the "psm_rp2040_zero" folder you should see a new folder apear named "build", navigate to it and find a file named "psm_rp2040_zero.ino.uf2", this is the file you will flash into the MCU
8. Now unplugg ALL the ports on your PC
9. Now HOLD "boot" button on the rp2040 zero, while you are HOLDING the "boot" button plug the USB-C cable from your PC to the rp2040 zero, continue hOLDING "boot" button. This is a bit tricky since you need 2 hands, one holding button and the other plugging it at the same time, so ask for help if to hard :)
10. Now it is verry important that you continue HOLDING "boot" button in after plugging in. Afger a few seconds a popup screen apears with external memory folder. Dont close this
11. If you have failed getting the popup folder, you need to start from point 8. again lol. Else contiue to step 12.
12. Now take your "psm_rp2040_zero.ino.uf2" and copy it over to this new folder. Once complete the folder will close itself and the RP2040 zero MCU sould blink red and then stay green.
13. Congradulations, you have flasshed the RP2040 zero :D
