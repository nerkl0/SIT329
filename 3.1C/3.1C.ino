#include "GPIO.h"
#include <sam.h>

GPIO_Pin leds[] = {
  { PORT_A, 6, GPIO_OUTPUT }, // D7
  { PORT_B, 10, GPIO_OUTPUT }, // D2
  { PORT_A, 18, GPIO_OUTPUT }, // D8
  { PORT_A, 20, GPIO_OUTPUT }, // D9
  { PORT_B, 11, GPIO_OUTPUT }, // D3
  { PORT_A, 7, GPIO_OUTPUT }, // D4
};

const int LED_LENGTH = sizeof(leds)/sizeof(leds[0]);

Pin_State state[] = {
  {&leds[0], HIGH},
  {&leds[1], LOW},
  {&leds[2], LOW},
  {&leds[3], HIGH},
  {&leds[4], HIGH},
  {&leds[5], LOW},
};

void invertLights(){
  for (int i = 0; i < LED_LENGTH; i++){
    state[i].state = !state[i].state;
  }
}

void alternateDisplay(){
  invertLights(); 
  Display_GPIO(state, LED_LENGTH);
}

void setup() {
  Serial.begin(9600);
  
  if (!SetupPort_GPIO(leds, LED_LENGTH)) {
    Serial.println("Error configuring LED pins");
    Serial.flush();
    while (1); // don't let program intiate 
  }

  Display_GPIO(state, LED_LENGTH);
}

void loop() {
  delay(1000);
  alternateDisplay();
}