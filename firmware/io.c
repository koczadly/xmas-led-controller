#include "io.h"


union GPIOshadow_t GPIOshadow;

union blueLeds_t blueLeds;



void gpio_latch(void) {
    GPIO = GPIOshadow.GPIO;
}


unsigned char is_btn_pressed(void) {
    return GPIObits.GP3;
}


void set_led_white(unsigned char en) {
    GPIOshadow.GP0 = en;
    gpio_latch();
}

void set_led_green(unsigned char duty) {
    CCPR1L = duty;
}

void set_led_blue(unsigned char data) {
    blueLeds.SR_BYTE = data;
    update_led_blue();
}

void update_led_blue(void) {
    //Shift reg
    shift_reg_byte(blueLeds.SR_BYTE);
    
    //Output latch
    GPIOshadow.GP4 = 1; //Latch
    gpio_latch();
    __delay_us(SHIFTREG_DELAY);
    GPIOshadow.GP4 = 0; //Latch
    gpio_latch();
}


static void shift_reg_byte(unsigned char data) {
    for(char i=0; i<8; i++) {
        if((data >> i) & 1 != 0) {
            GPIOshadow.GP5 = 1; //Serial data
            gpio_latch();
            __delay_us(SHIFTREG_DELAY);
        }
        
        GPIOshadow.GP1 = 1; //Serial clock
        gpio_latch();
        
        __delay_us(SHIFTREG_DELAY);
        
        GPIOshadow.GP1 = 0; //Serial clock
        GPIOshadow.GP5 = 0; //Serial data
        gpio_latch();
        
        __delay_us(SHIFTREG_DELAY);
    }
}