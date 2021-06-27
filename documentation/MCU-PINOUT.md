# Microcontroller pinout

This project utilises a PIC12f683 microcontroller to control the animations and LEDs.
The pinout is as follows (following pin numbers specified in the datasheet):

Pin # | Name | Configuration | Function
--- | --- | --- | ---
1 | VDD | POWER | +5V power source
2 | GP5 | OUTPUT | Shift register serial data
3 | GP4 | OUTPUT | Shift register latch
4 | GP3 | INPUT | Program button (HIGH to change)
5 | GP2 | OUTPUT | Green LEDs (PWM-driven)
6 | GP1 | OUTPUT | Shift register serial clock
7 | GP0 | OUTPUT | White LED
8 | VSS | POWER | Ground