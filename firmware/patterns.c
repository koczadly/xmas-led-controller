#include "patterns.h"
#include "io.h"


volatile unsigned char patternMode = 0;
volatile unsigned int patternFrame = -1;


void pattern_change(void) {
    //Change mode and reset animation frame
    patternMode = (patternMode >= 13) ? 0 : patternMode + 1;
    patternFrame = -1;
    
    //Reset LEDs
    set_led_white(0);
    set_led_green(0x00);
    set_led_blue(0x00);
    
    eeprom_write(EEPROM_ADDR_MODE, patternMode); //Store mode in eeprom
}


//  15.26 Hz, 1 frame = 65.53ms

unsigned char randomFlashFrames = 17;

void pattern_step(void) {
    //Animate
    if(patternMode == 0 || patternMode == 1) { //Sparkling blue + breathing green + flashing white
        if(patternFrame == 0) {
            set_led_white(0);
            set_led_blue(0x00);
        }
        
        //White (flash)
        randomFlashFrames--;
        if(randomFlashFrames == 3 && patternMode == 0) {
            set_led_white(1);
        } else if(randomFlashFrames == 2 && patternMode == 0) {
            set_led_white(0);
        } else if(randomFlashFrames == 1) {
            set_led_white(1);
        } else if(randomFlashFrames == 0) {
            set_led_white(0);
            randomFlashFrames = (patternMode == 0 ? (rand(35) + 15) : (rand(120) + 30));
        }
        
        //Blue (sparkle)
        if(patternFrame % (patternMode == 0 ? 4 : 6) == 0) {
            set_led_blue(1 << ((patternFrame / (patternMode == 0 ? 4 : 6)) % 8));
        }
        
        //Green (breathe)
        if(patternFrame <= 255) {
            set_led_green(patternFrame);
        } else if(patternFrame > 270 && patternFrame <= 525) {
            set_led_green(255 - (patternFrame - 270));
        } else if(patternFrame == 536) {
            patternFrame = -1; //Reset frame
        }
    } else if(patternMode == 2) { //Sparkling blue + breathing green
        if(patternFrame == 0) {
            set_led_white(0);
            set_led_blue(0x00);
        }
        
        //Blue (sparkle)
        if(patternFrame % 4 == 0) {
            set_led_blue(1 << ((patternFrame / 4) % 8));
        }
        
        //Green (breathe)
        if(patternFrame <= 255) {
            set_led_green(patternFrame);
        } else if(patternFrame > 270 && patternFrame <= 525) {
            set_led_green(255 - (patternFrame - 270));
        } else if(patternFrame == 536) {
            patternFrame = -1; //Reset frame
        }
    } else if(patternMode == 3 || patternMode == 4) { //Sparkling (sparkling blue, sparkling blue + green)
        if(patternFrame == 0) {
            set_led_green(patternMode == 3 ? 0xFFu : 0x00u);
            set_led_blue(0x00);
            set_led_white(0);
        }
        
        if(patternFrame % 4 == 0) {
            set_led_blue(1 << ((patternFrame / 4) % 8));
        }
        
        if(patternFrame == 32) patternFrame = -1; //Reset frame
    } else if(patternMode >= 5 && patternMode <= 7) { //Breathing green (green, green + 100% blue, green + 50% blue
        if(patternFrame == 0) {
            set_led_blue(patternMode == 5 ? 0x00u : (patternMode == 6 ? 0xFFu : 0x55u));
            set_led_white(0);
        }
        
        if(patternFrame <= 255) {
            set_led_green(patternFrame);
        } else if(patternFrame > 270 && patternFrame <= 525) {
            set_led_green(255 - (patternFrame - 270));
        } else if(patternFrame == 530) {
            patternFrame = -1; //Reset frame
        }
    } else if(patternMode >= 8 && patternMode <= 11) { //Statics (green, blue, aqua (100%), aqua (50%)
        if(patternFrame == 0) {
            set_led_green(patternMode != 9 ? 0xFFu : 0x00u);
            set_led_blue(patternMode == 8 ? 0x00u : (patternMode == 11 ? 0x55u : 0xFFu));
            set_led_white(0);
        }
    } else if(patternMode == 12) {
        if(patternFrame == 0) {
            set_led_white(0);
            set_led_green(0xFF);
            set_led_blue(0x00);
        } else if(patternFrame == 38) {
            set_led_green(0x00);
            set_led_blue(0xFF);
        } else if(patternFrame == 75) {
            patternFrame = -1;
        }
    } else if(patternMode == 13) {
        if(patternFrame == 0) {
            set_led_green(0xFF);
            set_led_blue(0x00);
            set_led_white(0);
        } else if(patternFrame == 12) {
            set_led_green(0x00);
            set_led_blue(0xFF);
            set_led_white(0);
        } else if(patternFrame == 24) {
            set_led_green(0x00);
            set_led_blue(0x00);
            set_led_white(1);
        } else if(patternFrame == 35) {
            patternFrame = -1;
        }
    }
    
    patternFrame++; //Increment frame
}


unsigned short randSeed = 2857;

unsigned char rand(unsigned char upper) {
	return (randSeed = (48271 * randSeed) % 0x7FFF) % upper;
}