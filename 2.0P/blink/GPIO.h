#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum { PORT_A, PORT_B } GPIO_Port;
typedef enum { GPIO_INPUT, GPIO_OUTPUT } Mode;

typedef struct { 
  GPIO_Port port; 
  uint8_t pin;
  Mode mode; 
} GPIO_Pin;

bool Config_GPIO(GPIO_Pin *pin); 
bool Write_GPIO(GPIO_Pin *pin, bool state);
bool Read_GPIO(GPIO_Pin *p);

#endif