#include "config.h"


//GPIO shadow register
union GPIOshadow_t {
    struct {
        unsigned GP0 : 1;
        unsigned GP1 : 1;
        unsigned GP2 : 1;
        unsigned GP3 : 1;
        unsigned GP4 : 1;
        unsigned GP5 : 1;
        unsigned : 2;
    };
    struct {
        unsigned GPIO : 6;
        unsigned : 2;
    };
};
extern union GPIOshadow_t GPIOshadow;

//Blue LED array
union blueLeds_t {
    struct {
        unsigned LED1 : 1;
        unsigned LED2 : 1;
        unsigned LED3 : 1;
        unsigned LED4 : 1;
        unsigned LED5 : 1;
        unsigned LED6 : 1;
        unsigned LED7 : 1;
        unsigned LED8 : 1;
    };
    struct {
        unsigned SR_BYTE : 8;
    };
};
extern union blueLeds_t blueLeds;


void gpio_latch(void);

unsigned char is_btn_pressed(void);

void set_led_white(unsigned char en);
void set_led_green(unsigned char duty);
void set_led_blue(unsigned char data);

void update_led_blue(void);
static void shift_reg_byte(unsigned char data);