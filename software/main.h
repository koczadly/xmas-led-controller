#include "config.h"

extern volatile unsigned char initStage;
extern volatile signed char btnDelayTimerCounter;


void main(void);

void init(void);

void interrupt ISR(void);

void timer0_isr(void);
void gpio_isr(void);