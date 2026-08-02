#include "GPIO.h"

const uint32_t MODE_CYCLE = 2000;
const uint32_t TWINKLE_FREQ = MODE_CYCLE / 5;
const uint32_t STARFALL_FREQ = TWINKLE_FREQ * 10;
const uint32_t DEMO_CYCLE = 5000;
bool lightState = false;
uint32_t lastCycle = 0; 
uint32_t lastDemo = 0; 

enum { START, INVERT, TWINKLE, STARFALL } DemoMode;
int mode = START;

GPIO_Pin leds[] = {
  { PORT_A, 6, GPIO_OUTPUT }, // D7
  { PORT_B, 10, GPIO_OUTPUT }, // D2
  { PORT_A, 18, GPIO_OUTPUT }, // D8
  { PORT_A, 20, GPIO_OUTPUT }, // D9
  { PORT_B, 11, GPIO_OUTPUT }, // D3
  { PORT_A, 7, GPIO_OUTPUT }, // D4
};

const int LED_LENGTH = sizeof(leds)/sizeof(leds[0]);
const int initial[] = { HIGH, LOW, LOW, HIGH, HIGH, LOW };

Pin_State state[] = {
  {&leds[0], initial[0]},
  {&leds[1], initial[1]},
  {&leds[2], initial[2]},
  {&leds[3], initial[3]},
  {&leds[4], initial[4]},
  {&leds[5], initial[5]},
};

void invertLights(){
  for (int i = 0; i < LED_LENGTH; i++){
    state[i].state = !state[i].state;
  }
}

void resetState(){
  for (int i = 0; i < LED_LENGTH; i++){
    state[i].state = initial[i];
  }
}

void toggleAll(bool power){
  for (int i = 0; i < LED_LENGTH; i++){
    state[i].state = power;
  }
}

void setMode(uint32_t freq){
  if (millis() - lastCycle >= (freq / 2)){
    lastCycle = millis();
    lightState = !lightState;
    toggleAll(lightState);
  }
}

void setup() {
  Serial.begin(9600);
  while(!Serial);

  if (!SetupPort_GPIO(leds, LED_LENGTH)) {
    Serial.println("Error configuring LED pins");
    Serial.flush();
    while (1); // don't let program intiate 
  }
  Display_GPIO(state, LED_LENGTH);
}

void loop() {


  switch(mode){
    case START:
      Serial.println("Starting"); break;
    case INVERT:
      Serial.println("Invert"); break;
    case TWINKLE:
      Serial.println("Twinkle"); break;
    case STARFALL:
      Serial.println("Starfall"); break;
  }
  mode = (mode + 1) % 4;
}