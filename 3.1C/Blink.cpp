#include "Blink.h"

static unsigned long lastCycle = 0; // holds the tick counter value assigned by millis() to track cycle length
static bool lightState = false; // indicates when lights need to be switched ON/OFF

// Values assigned to the frequency argument for blink() within randomise()
static const uint32_t randomFreq[] = { 2000, 1000, 666, 400, 285, 200 };
const uint8_t FREQ_LEN = sizeof(randomFreq) / sizeof(randomFreq[0]);
const uint8_t BLINKS_PER_STEP = 5; 

static uint8_t step = 0, count = 0;
// keeps track of the direction in which the randomFreq are being assigned, either -1 or +1
static int8_t arrayDir = 1;

/*
  Inverts the current state of the lights. Called when the LEDs 
  have differing ON/OFF states, not for toggling all LEDs ON/OFF
*/
void invert(){
  for (int i = 0; i < LED_LENGTH; i++)
    state[i].state = !state[i].state;
}

// Switches all LEDs to the state passed in as the power argument
void toggleAll(bool power){
  for (int i = 0; i < LED_LENGTH; i++)
    state[i].state = power;
}

// Assign a random LED state to each pin. 
// randomSeed(); must be assigned to a floating pin in setup() for this function to work
void randomiseState(){
  for (int i = 0; i < LED_LENGTH; i++)
    state[i].state = random(0, 2);
}

/*
  Blink provides flashing functionality for the LEDs. 
  Uses the non-blocking millis() to track the cycle length, calling
  toggleAll() to handle the light state
  freq / 2 makes sure the blink is adhering to the frequency. Holds state on for half 
  the set frequency time, off for the other half.
*/
void blink(uint32_t freq){
  if (millis() - lastCycle >= (freq / 2)){
    lastCycle = millis();
    lightState = !lightState;
    toggleAll(lightState);
  }
}

/*
  In each cycle, if lightState switches to true, randomise which LEDs are lit
  If lightState switches to false, turn all LEDs off.
    count keeps track of the number of blinks for each BLINKS_PER_STEP in blink frequency 
  Cycles are assigned from the randomFreq array, assigned in an increasing then decreasing order
  arrayDir keeps track of which way the frequencies are being parsed within the array. Once an array
  bound is hit (0, FREQ_LEN), the +/- is switched triggering the direction reversal
*/
void randomise(){
  if (millis() - lastCycle < randomFreq[step] / 2)
    return;
  lastCycle = millis();
  lightState = !lightState;
  
  // Assign new random state values for each pin after one blink
  if (lightState){
     randomiseState();
  } else {
    toggleAll(false); // At the end of each blink step, switch all LEDs off / resetting the state

    // increment count, each cycle to have BLINKS_PER_STEP blinks
    if (++count >= BLINKS_PER_STEP){
      Serial.println("=========="); 
      Serial.println("Next cycle/step");
      count = 0;
      step += arrayDir; // incremement/decrement randomFreq index
       // if array bounds have been hit, flip the sign +/- so the array traverses in the opposite direction
      if (step == 0 || step == FREQ_LEN - 1)
        arrayDir = -arrayDir;
      Serial.print("Freq: ");Serial.println(randomFreq[step]);
    }
  }
}