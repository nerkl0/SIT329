#ifndef BLINK_H
#define BLINK_H

#include <Arduino.h>
#include "GPIO.h"

// An enum of the different Demo Modes available
typedef enum { START, INVERT, TWINKLE, STARFALL, STARRACE } DemoMode;

extern GPIO_Pin leds[];
extern const int LED_LENGTH;
extern Pin_State state[];

void setInitialState();
void invert();
void toggleAll(bool power);
void blink(uint32_t freq);
void randomise();
void randomiseState();

#endif