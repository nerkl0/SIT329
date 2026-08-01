#include "GPIO.h"

GPIO_Pin LED_1 = { PORT_A, 7, GPIO_OUTPUT }; // will map to D4 

void blink(int duration){
  Write_GPIO(&LED_1, true);
  delay(duration*1000);
  Write_GPIO(&LED_1, false);
  delay(duration*1000);
}
void setup() {
  Config_GPIO(&LED_1);
}

void loop() {
  blink(1);
}
