#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

static int dim = 0;
static int count = 0;

char toggle_red2()		/* always toggle! */
{
  static char state = 0;

  switch (dim) {
  case 0:
    red_on = 1;
    dim = 1;
    return 1;
    break;
  case 1:
    red_on = 0;
    dim = 0;
    return 0;
    break;
  }
  return 1;             /* always changes an led */
}

char first_state() /* Dims red light and mantains green led on */
{
  if (count == 5000) {
    count = 0;
  }
  if (count < 1000) {
    red_on = 1;
    green_on = 1;
  }
  else if (count < 2000 && count % 2 == 0){
    red_on = 1;
  }
  else if (count < 3000 && count % 4 == 0){
    red_on = 1;
  }   
  else if (count < 4000 && count % 6 == 0){
    red_on = 1;
  } 
  else if (count < 5000 && count % 8 == 0){
    red_on = 1;
  }
  else red_on = 0;

  count += 1;
  return 1;
}
int state1 = 0;
int state11 = 0;
char first_state_1()
{
  //state11++;
  //if (state11 < 125) state1 = 1;
  // else state1 = 2;
  //  state1 = blink_count_1;
  switch(state1)
  {
    case 1:
      red_on = 1;
      green_on = 0;
      state1 = 2;
      break;
    case 2:
      red_on = 0;
      green_on = 1;
      state1 = 3;
      break;
    default:
      red_on = 0;
      green_on = 0;
      state1 = 1;
      break;
  }
}

char second_state()
{
  if (count == 1100) {
    count = 0;
  }
  if (count < 125) {
    red_on = 1;
    green_on = 1;
  }
  else if (count < 250) {
    red_on = 0;
    green_on = 1;
  }
  else if (count < 375) {
    red_on = 1;
    green_on = 1;
  }
  else if (count < 500) {
    red_on = 0;
    green_on = 0;  
  }
  else if (count < 625) {
    red_on = 1;
    green_on = 1;
  }
  else if (count < 750) {
    red_on = 1;
    green_on = 0;
  }
  else if (count < 875) {
    red_on = 1;
    green_on = 1;
  }
  else if (count < 1000) {
    red_on = 0;
    green_on = 0;  
  }

  
  count += 1;
  return 1;
}

char third_state()
{
  if (count == 2550) {
    buzzer_set_period(0);
    count = 0;
  }
  if (count < 125) buzzer_set_period(5102);
  else if (count < 200) buzzer_set_period(0);
  else if (count < 325) buzzer_set_period(5102);
  else if (count < 400) buzzer_set_period(0);
  else if (count < 525) buzzer_set_period(6079);
  else if (count < 600) buzzer_set_period(0);
  else if (count < 725) buzzer_set_period(5730);
  else if (count < 800) buzzer_set_period(0);
  else if (count < 925) buzzer_set_period(5102);
  else if (count <1000) buzzer_set_period(0);
  else if (count <1125) buzzer_set_period(4545);
  else if (count <1200) buzzer_set_period(0);
  else if (count <1325) buzzer_set_period(5102);
  else if (count <1400) buzzer_set_period(0);
  else if (count <1525) buzzer_set_period(5730);
  
  else if (count <1600) buzzer_set_period(0);
  else if (count <1725) buzzer_set_period(6079);
  else if (count <1800) buzzer_set_period(0);
  else if (count <1950) buzzer_set_period(6825);
  else if (count <2025) buzzer_set_period(0);
  else if (count <2150) buzzer_set_period(6079);
  else if (count <2225) buzzer_set_period(0);
  else if (count <2350) buzzer_set_period(6079);
  else if (count <2550) buzzer_set_period(0);
  count += 1;
  return 1;
}

char fourth_state()
{

  if (count == 2550) {
    buzzer_set_period(0);
    count = 0;
  }
  if (count < 125) buzzer_set_period(6079);
  else if (count < 200) buzzer_set_period(0);
  else if (count < 325) buzzer_set_period(5405);
  else if (count < 400) buzzer_set_period(0);
  else if (count < 525) buzzer_set_period(4545);
  else if (count < 600) buzzer_set_period(0);
  else if (count < 725) buzzer_set_period(5102);
  else if (count < 800) buzzer_set_period(0);
  else if (count < 925) buzzer_set_period(5405);
  else if (count <1000) buzzer_set_period(0);
  else if (count <1125) buzzer_set_period(5102);
  else if (count <1200) buzzer_set_period(0);
  else if (count <1425) buzzer_set_period(8132);
  else if (count <1650) buzzer_set_period(0);
  count += 1;
  return 1;
}
int state4 = 1;
char fourth_state_1()
{
  switch(state4)
  {
  case 1:
   buzzer_set_period(6079);
   break;
  case 2:
   buzzer_set_period(0);
   break;
  case 3:
   buzzer_set_period(5405);
   break;
  case 4:
    buzzer_set_period(0);
    break;
  case 5:
    buzzer_set_period(4545);
    break;
  case 6:
    buzzer_set_period(0);
    break;
  case 7:
    buzzer_set_period(5102);
    break;
  case 8:
    buzzer_set_period(0);
    break;
  case 9:
    buzzer_set_period(5405);
    break;
  case 10:
    buzzer_set_period(0);
    break;
  case 11:
    buzzer_set_period(5102);
    break;
  case 12:
    buzzer_set_period(0);
    break;
  case 13:
    buzzer_set_period(8132);
    break;
  case 14:
    buzzer_set_period(0);
    state4 = 0;
    break;
  default:
    buzzer_set_period(8132);
    break;
  }
  state4++;
  return 1;
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  
  
  if (state == 1) {
    changed = first_state();
  }
  if (state == 2) {
    changed = second_state();
  }
  if (state == 3) {
    changed = third_state();
  }
  if (state == 4) {
    changed = fourth_state();
  }

  led_changed = changed;
  led_update();
}
