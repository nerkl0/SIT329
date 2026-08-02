#include "GPIO.h"
#include "sam.h" 

/*
  Configures a pin to I/O
  Parameters: 
    *p: address of GPIO_Pin struct
  p->port: Assigned port A/B
  p->pin: port pin
  p->mode: Input/Output
  Creates a mask to identify the correct pin in the register, assigns INPUT using DIRCLR, and DIRSET if OUTPUT
  .INEN is configured to make the I/O value readable by indexing into the pin
*/
bool Config_GPIO(GPIO_Pin *p){
  // Validation for struct
  if (p == NULL) return false;
  if (p->pin > 31) return false; // ensures pin value is bounded within the bit field register

  uint32_t mask = 1u << p->pin;
  switch(p->mode){
    case GPIO_INPUT:
      PORT->Group[p->port].DIRCLR.reg = mask; break;
    case GPIO_OUTPUT:
      PORT->Group[p->port].DIRSET.reg = mask; break;
    default:
      return false; 
  }

  // INEN set to 1 enables the pins input buffer, which can then be sampled making the value readable
  PORT->Group[p->port].PINCFG[p->pin].bit.INEN = 1;
  return true;
}

/*
  Drives a GPIO pin by setting output state to high or low
  Parameters:
    *p: address of GPIO_PIN struct
    state: a boolean setting the output state to HIGH / LOW
  If the *p mode is INPUT, the function returns early
*/
bool Write_GPIO (GPIO_Pin *p, bool state){
  if (p->mode != GPIO_OUTPUT) 
    return false;
    
  // creates a mask for the selected pin
  uint32_t mask = 1u << p->pin;
  if (state){
    PORT->Group[p->port].OUTSET.reg = mask; // OUTSET "sets" pin (1) drives pin to HIGH
  } else {
    PORT->Group[p->port].OUTCLR.reg = mask; // OUTCLR "clears" pin (0) drives pin to LOW
  }
  return true;
}
/*
  Read_GPIO returns the input state of the pin. 
  Parameter: the address of GPIO_PIN *p
  IN.reg reads a copy of the entire 32 bit register; 
  Isolates the pin value by: shifting right >> to position 0
  & 1u discards all bits above leaving pin output value 0 -> LOW, 1 -> HIGH
  - Only works if the pins input buffer (.INEN) is configured to 1 
*/
bool Read_GPIO(GPIO_Pin *p){
  return (PORT->Group[p->port].IN.reg >> p->pin) & 1u;
}