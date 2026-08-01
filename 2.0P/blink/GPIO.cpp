#include "GPIO.h"
#include "sam.h" 

// configure any GPIO pin to act as input or output (Mode)
// bool Config_GPIO(char PortNum, char PinNum, Mode)
/*
  PortNum should allow for the GPIO groups A, B..
  PinNum refers to the position of the pin in the GPIO group
  Mode refers to input or output
*/

bool Config_GPIO(GPIO_Pin *p){
  uint32_t mask = 1u << p->pin;
  switch (p->mode) {
    case GPIO_INPUT:
      PORT->Group[p->port].DIRCLR.reg = mask;
      PORT->Group[p->port].PINCFG[p->pin].bit.INEN = 1;
      return true;
    case GPIO_OUTPUT:
      PORT->Group[p->port].PINCFG[p->pin].bit.INEN = 0;
      PORT->Group[p->port].DIRSET.reg = mask;
      return true;
  }
  return false;
}

bool Write_GPIO (GPIO_Pin *p, bool state){
  if (p->mode != GPIO_OUTPUT) 
    return false;
  
  uint32_t mask = 1u << p->pin;
  if (state){
    PORT->Group[p->port].OUTSET.reg = mask;
  } else {
    PORT->Group[p->port].OUTCLR.reg = mask;
  }
  return true;
}

bool Read_GPIO(GPIO_Pin *p){
  return (PORT->Group[p->port].IN.reg & (1u << p->pin)) != 0;
}