#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum { PORT_A, PORT_B } GPIO_Port;
typedef enum { GPIO_INPUT, GPIO_OUTPUT } Mode;

/*
  GPIO_Pin struct that takes port A or B
  Pin: Port pin integer 
  Mode: INPUT / OUTPUT
*/
typedef struct { 
  GPIO_Port port; 
  uint8_t pin;
  Mode mode; 
} GPIO_Pin;

// Takes a pointer to a pin and holds a state for it
typedef struct {
  GPIO_Pin *pin; 
  int state;
} Pin_State;

bool Config_GPIO(GPIO_Pin *pin); 
bool Write_GPIO(GPIO_Pin *pin, bool state);
bool Read_GPIO(GPIO_Pin *p);
bool SetupPort_GPIO(GPIO_Pin *arr, int len);
bool Display_GPIO(Pin_State *st, int len);

#endif