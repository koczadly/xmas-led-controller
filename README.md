# 'ey up!

## Introduction
This repository contains files from a personal project. The aim was to create a small microcontroller-driven LED module to replace a broken incandescent bulb from a fibre optic Christmas tree. This is my first project involving PIC microcontrollers, and the second PCB I've designed; mistakes and uncommon design techniques are to be expected.

Feel free to re-use or modify this project to fit your needs, or use as a reference for PCB design or PIC software development.

## Finished product
A range of final images can be found under the [/demo/ folder](/demo).
<img src="demo/pcb-final.jpg" alt="Finished PCB" width="450"/>
<img src="demo/prog1-demo.gif" alt="Tree running program 1's animation" width="300"/>

## Bill of materials (BOM)
MPN | Type | Quantity | Unit cost (GBP) | Purpose
--- | --- | --- | --- | ---
[**PIC12F683**](https://www.microchip.com/wwwproducts/en/PIC12F683) (DIP) | Microcontroller | 1 | £0.40 | Controls visual animations and user input
[**74HC595**](http://www.ti.com/lit/ds/symlink/sn74hc595.pdf) (DIP) | 8-bit Shift Register | 1 | £0.05 | Controls outputs to outer blue LEDs from the MCU
N/A | 3mm Blue LED | 8 | £0.01 | Outer LED ring
N/A | 5mm Green LED | 3 | £0.01 | Inner LEDs (PWM-driven)
N/A | 5mm White LED | 1 | £0.01 | Inner strobing LED
[**2N3904**](https://www.onsemi.com/pub/Collateral/2N3903-D.PDF) (TO-92) | NPN Transistor | 10 | £0.01 | Drives each individual controllable LED group (8x Blue, 1x Green, 1x White)
[N/A](https://www.ebay.co.uk/itm/AC-1-5A-250V-3A-125V-Red-Square-Momentary-SPST-Push-Button-Switch-6-Pcs/183740567110) | SPST Momentary Switch | 1 | £0.30 | User input for changing displayed animation/colour
N/A | 1000μF (25V) Electrolytic Capacitor | 1 | £0.10 | Supply voltage smoothing
N/A | 100nF (50V) Ceramic Capacitor | 1 | £0.01 | Decoupling capacitor for MCU
N/A | 10k Resistor (1/4W) | 1 | £0.01 | Input switch pull-down resistor
N/A | 1k Resistor (1/4W) | 10 | £0.01 | Transistor base current limiters
N/A | 150R Resistor (1/4W) | 8 | £0.01 | Driving blue LEDs
N/A | 120R Resistor (1/4W) | 3 | £0.01 | Driving green LEDs
N/A | 62R Resistor (1/4W) | 1 | £0.01 | Driving white LED

---

**Total component cost: £1.31**  
**PCB panel cost (DIY): £0.36**  
**Total cost: £1.67** *(Not including etchant, solder or original tree product)*  

---

## Design notes & constraints
There were various constraints throughout this project, the most difficult one being that I could only produce a single-sided PCB, making overlaps impossible without using space for a 0Ω link. The size of the board was also restricted to *68mm x 92mm*, otherwise the module wouldn't fit into the tree's current plastic base housing. Drill holes also had to be made and inserted at defined locations so the board could easily be screwed into the unit using pre-existing screw mounts from the previous incandescent arrangement.