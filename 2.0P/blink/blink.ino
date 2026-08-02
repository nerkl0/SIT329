#include "GPIO.h"
#include <sam.h>

GPIO_Pin LED_1 = { PORT_A, 17, GPIO_OUTPUT }; // will map to D13


/*
  A simple blink function that takes a duration argument in seconds and 
  writes HIGH then LOW to the pin. Calls the blocking delay() for the set
  duration and Write_GPIO from the GPIO.h driver to configure the output
*/
void blink(int duration){
  Write_GPIO(&LED_1, true);
  Serial.println(Read_GPIO(&LED_1));
  delay(duration*1000);

  Write_GPIO(&LED_1, false);
  Serial.println(Read_GPIO(&LED_1));
  delay(duration*1000);
}

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Config_GPIO(&LED_1);
}

void loop() {
  // Blink in-built LED for 1 second 
  blink(1);
}