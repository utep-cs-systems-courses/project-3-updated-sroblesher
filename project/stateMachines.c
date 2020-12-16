#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "stateMachines.h"

static int dim = 0;
static int count = 0;
static int state1Count = 0;
static int state2Count = 0;
static int state3Count = 0;
static int state4Count = 0;
static int dimsCount = 0;

//100% luminosity
void dim1()
{
  //red_on = 1;
  //led_changed = 1;
   redLedOn();  //Using assembly
  led_update();
}

//25% luminosity
void dim2()
{
  if (state1Count % 4 == 0)
    red_on = 1;
  else red_on = 0;
  //dimsCount++;
  led_changed = 1;
  led_update;
}

//12.5% luminosity
void dim3()
{
  //if (dimsCount > 2000) dimsCount = 0;
  if (state1Count % 8 == 0)
    red_on = 1;
  else red_on = 0;
  //dimsCount++;
  led_changed = 1;
  led_update;
}


char new_first_state()
{
  //Select what luminosity to display
  int countFS;
  if(state1Count <= 1000) countFS = 1;
  else if(state1Count <= 2000) countFS = 2;
  else if(state1Count <= 3000) countFS = 3;
  else {
    state1Count = 0;
    countFS = 1;
  }
  
  switch(countFS)
  {
    case 1:
      dim1();  //All luminosity
      break;
    case 2:
      dim2();  //25%
      break;
    case 3:
      dim3();  //12.5%
      break;
    default:
      red_on = 0;
      state1Count = 1;
      break;
  }
  state1Count++;
  led_changed = 1;
  led_update();
}


//Defectuous button
char second_state()
{  
  count += 1;
  return 1;
}

//Dragon Ball GT song
char new_third_state()
{
  switch(state3Count)
    {
    case 0:
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
    case 12:
    case 14:
    case 16:
    case 18:
    case 20:
    case 22:
    case 24:
      buzzer_set_period(0);
      break;
    case 1:
    case 3:
      buzzer_set_period(5102);
      break;
    case 5:
    case 17:
    case 21:
    case 23:
      buzzer_set_period(6079);
      break;
    case 7:
    case 15:
      buzzer_set_period(5730);
      break;
    case 9:
    case 13:
      buzzer_set_period(5102);
      break;
    case 11:
      buzzer_set_period(4545);
      break;
    case 19:
      buzzer_set_period(6825);
      break;
    default:
      buzzer_set_period(0);  //Return to first position and note
      state3Count = 0;
      break;
    }
  state3Count++;
  return 1;
}

//Saint Seiya song
char new_fourth_state()
{
  switch(state4Count)
    {
    case 0:
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
    case 12:
    case 14:
      buzzer_set_period(0);
      break;
    case 1:
      buzzer_set_period(6079);
      break;
    case 3:
    case 9:
      buzzer_set_period(5405);
      break;
    case 5:
      buzzer_set_period(4545);
      break;
    case 7:
    case 11:
      buzzer_set_period(5102);
      break;
    case 13:
      buzzer_set_period(8132);
      break;
    default:
      buzzer_set_period(0);
      state4Count = 0; //Return to first position and note
      break;
  }
  state4Count++;
  return 1;
}

//Passed to assembly
/*
void state_advance()	
{
  char changed = 0;

  if (state == 1) {
    changed = new_first_state();
  }
  if (state == 2) {
    changed = second_state();
  }
  if (state == 3) {
    changed = new_third_state();
  }
  if (state == 4) {
    changed = new_fourth_state();
  }

  led_changed = changed;
  led_update();
}
*/
