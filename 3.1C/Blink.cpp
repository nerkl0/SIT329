#include "Blink.h"

static uint32_t lastCycle = 0;
static bool lightState = false;

void invertLights(){
  for (int i = 0; i < LED_LENGTH; i++)
    state[i].state = !state[i].state;
}

void toggleAll(bool power){
  for (int i = 0; i < LED_LENGTH; i++)
    state[i].state = power;
}

void blink(uint32_t freq){
  if (millis() - lastCycle >= (freq / 2)){
    lastCycle = millis();
    lightState = !lightState;
    toggleAll(lightState);
  }
}

void randomiseMode(){
}