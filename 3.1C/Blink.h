#ifndef BLINK_H
#define BLINK_H

#include <Arduino.h>
#include "GPIO.h"

enum DemoMode { START, INVERT, TWINKLE, STARFALL, STARRACE };

extern GPIO_Pin leds[];
extern const int LED_LENGTH;
extern Pin_State state[];

void setInitialState();
void invertLights();
void toggleAll(bool power);
void blink(uint32_t freq);
void randomiseMode();

#endif