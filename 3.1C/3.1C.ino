#include "GPIO.h"
#include "Blink.h"

const uint32_t FREQ = 1000; // Length of one full cycle
const uint32_t TWINKLE_FREQ = FREQ / 5; // 5Hz 
const uint32_t STARFALL_FREQ = TWINKLE_FREQ * 10; // 0.5Hz
const uint32_t DEMO_CYCLE = 5000; // Cycle length for all modes excluding Starrace
const uint32_t STARRACE_CYCLE = 40000; // Standalone cycle for Starrace 

uint32_t currentCycle = DEMO_CYCLE; // to track the current cycle length. Switches in main timer in loop

unsigned long lastDemoMode = 0; // holds a tick counter value from the start of a demo cycle
uint8_t mode = -1; // mode will be updated to 0 (Default) on first iteration of loop()

GPIO_Pin leds[] = {
  { PORT_A, 6, GPIO_OUTPUT }, // D7
  { PORT_B, 10, GPIO_OUTPUT }, // D2
  { PORT_A, 18, GPIO_OUTPUT }, // D8
  { PORT_A, 20, GPIO_OUTPUT }, // D9
  { PORT_B, 11, GPIO_OUTPUT }, // D3
  { PORT_A, 7, GPIO_OUTPUT }, // D4
};
const int LED_LENGTH = sizeof(leds)/sizeof(leds[0]);

Pin_State state[LED_LENGTH];

// Assign the address of each pin to a Pin_State held within state[] array
void buildStateStructs(){
  for (int i = 0; i < LED_LENGTH; i++)
    state[i].pin = &leds[i];
}

void setup() {
  Serial.begin(9600);
  while(!Serial);

  if (!SetupPort_GPIO(leds, LED_LENGTH)) {
    Serial.println("Error configuring LED pins");
    Serial.flush();
    while (1);
  }
  randomSeed(analogRead(A0)); // required for randomise() to work from Blink driver

  buildStateStructs();
  randomiseState(); // assigns a random state to each pin stored in state[]
}

void loop() {
  if ((millis() - lastDemoMode) >= currentCycle){
    mode = (mode + 1) % 5;
    lastDemoMode = millis();
    // assign the correct current cycle duration depending on mode
    currentCycle = (mode == STARRACE) ? STARRACE_CYCLE : DEMO_CYCLE;

    switch(mode){
      case START:
        Serial.println("Mode: Default"); 
        randomiseState(); break;
      case INVERT:
        Serial.println("Mode: Invert");
        invert(); break;
      case TWINKLE:
        Serial.println("Mode: Twinkle"); 
        resetBlink(); break;
      case STARFALL:
        Serial.println("Mode: Starfall");
        resetBlink(); break;
      case STARRACE:
        Serial.println("Mode: Star Race");
        resetRandomise(); break;
    }
  }
  
  if (mode == TWINKLE) blink(TWINKLE_FREQ);
  if (mode == STARFALL) blink(STARFALL_FREQ);
  if (mode == STARRACE) randomise();

  Display_GPIO(state, LED_LENGTH);
}