#include "config.h"

extern volatile unsigned char patternMode;
extern volatile unsigned int patternFrame;


void pattern_change(void);

void pattern_step(void);

unsigned char rand(unsigned char upper);