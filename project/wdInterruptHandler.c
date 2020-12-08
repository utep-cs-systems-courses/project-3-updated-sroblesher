#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == 1) {
    state_advance();
    blink_count = 0;
  }
  
  /*static char blink_count_1 = 0;
  
  if (state == 1)
  {
    if (++blink_count_1 == 250) {
      state_advance();
      blink_count_1 = 0;
    }  
  }*/
}
