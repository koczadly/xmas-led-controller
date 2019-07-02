#include "main.h"
#include "io.h"
#include "patterns.h"


volatile unsigned char initStage = 0;

volatile signed char btnDelayTimerCounter = 15;



void init(void) {
    //Configure oscillator
    OSCCON = 0b01100001;
    
    //Configure IO
    TRISIObits.TRISIO0 = 0; //GP0 | LED-W   White LED
    TRISIObits.TRISIO1 = 0; //GP1 | SRCLK   Serial clock
    TRISIObits.TRISIO2 = 0; //GP2 | LED-G   Green LEDs
    TRISIObits.TRISIO3 = 1; //GP3 | INPUT   Button
    TRISIObits.TRISIO4 = 0; //GP4 | RCLK    Latch
    TRISIObits.TRISIO5 = 0; //GP5 | SER     Serial data
    
    //Initialise shadow register
    GPIOshadow.GPIO = 0x00;
    gpio_latch();
    
    //Timers
    T2CON = 0b1111111; //Timer2 for PWM
    OPTION_REG = 0b01000110; //Timer0, 1:128 prescaler
    
    //CCP1 PWM
    CCP1CON = 0b001100;
    
    //Interrupt registers
    IOC = 0b001000; //IOC for GP3
    INTCONbits.T0IE = 1; //Timer0 interrupt enable
    INTCONbits.GPIE = 1; //GPIO interrupt enable
    INTCONbits.PEIE = 1; //Peripheral interrupt
    INTCONbits.GIE = 1; //Global interrupt enable
}


void main(void) {
    init();
    
    set_led_white(0);
    set_led_green(0x00);
    set_led_blue(0x00);
    
    initStage = 1; //Initialise stage: setup registers
    
    //Load pattern mode from eeprom
    patternMode = eeprom_read(EEPROM_ADDR_MODE);
    
    __delay_ms(10);
    initStage = 2; //Initialise stage: loaded EEPROM
    
    while(1) __delay_ms(1000); //Prevent main() return
}


void interrupt ISR(void) {
    //Timer0
    if(TMR0IF) {
        timer0_isr(); //Handle
        TMR0IF = 0; //Clear flag
    }
    
    //Button (GP3)
    if(GPIF) {
        gpio_isr(); //Handle
        GPIF = 0; //Clear flag
    }
}


//Interrupt for timer0 (15.26 Hz, 1 cycle = 65.53ms)
void timer0_isr(void) {
    if(initStage < 2) return; //Skip if not initialised
    
    if(btnDelayTimerCounter > 0 && !is_btn_pressed()) {
        btnDelayTimerCounter--;
    } else if(btnDelayTimerCounter > BTN_MODE_HOLD_DELAY && btnDelayTimerCounter <= 0 && is_btn_pressed()) {
        if(--btnDelayTimerCounter == BTN_MODE_HOLD_DELAY) {
            pattern_change(); //Change pattern
            btnDelayTimerCounter = BTN_MODE_COOLDOWN_DELAY; //Set button delay
        }
    }
    
    pattern_step();
}


//Interrupt for GPIO
bit wasBtnPressed = 0;

void gpio_isr(void) {
    if(initStage < 2) return; //Skip if not initialised
    
    if(is_btn_pressed()) {
        //Button has been pressed
    } else if(wasBtnPressed) {
        //Button has been released
        btnDelayTimerCounter = BTN_MODE_COOLDOWN_DELAY; //Set button delay
    }
    
    wasBtnPressed = is_btn_pressed();
}