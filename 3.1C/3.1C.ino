#include "GPIO.h"
#include "Blink.h"

const uint32_t MODE_CYCLE = 1000;
const uint32_t TWINKLE_FREQ = MODE_CYCLE / 5;
const uint32_t STARFALL_FREQ = TWINKLE_FREQ * 10;
const uint32_t DEMO_CYCLE = 5000;

uint32_t lastDemoMode = 0;
uint8_t mode = -1;

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

Pin_State state[LED_LENGTH];

void setInitialState(){
  for (int i = 0; i < LED_LENGTH; i++){
    state[i].pin = &leds[i];
    state[i].state = initial[i];
  }
}

void setup() {
  Serial.begin(9600);
  while(!Serial);

  if (!SetupPort_GPIO(leds, LED_LENGTH)) {
    Serial.println("Error configuring LED pins");
    Serial.flush();
    while (1);
  }
  setInitialState(); 
}

void loop() {
  if ((millis() - lastDemoMode) >= DEMO_CYCLE){
    mode = (mode + 1) % 5;
    lastDemoMode = millis();

    switch(mode){
      case START:
        Serial.println("Default"); 
        setInitialState(); break;
      case INVERT:
        Serial.println("Invert");
        invertLights(); break;
      case TWINKLE:
        Serial.println("Twinkle"); break;
      case STARFALL:
        Serial.println("Starfall"); break;
      case STARRACE:
        Serial.println("Star Race"); break;
    }
  }
  
  if (mode == TWINKLE) blink(TWINKLE_FREQ);
  if (mode == STARFALL) blink(STARFALL_FREQ);
  //if (mode == STARRACE) randomiseMode();

  Display_GPIO(state, LED_LENGTH);
}