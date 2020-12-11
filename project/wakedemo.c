#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "led.h"
//#include "switches.h"
//#include "stateMachines.h"
#include "p2switches.h"

#define LED_GREEN BIT0             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;
  secCount++;
  // secCount ++;
  // if (secCount == 250) {		/* once/sec */
  //secCount = 0;
  //fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
  //redrawScreen = 1;
  //}

    if (secCount == 500 && button_pressed == 1){
       clearScreen(COLOR_BLUE);
       drawString5x7(20,40, "First button!!!", fontFgColor, COLOR_BLUE);
       secCount = 0;
       redrawScreen = 1;
       //state_advance();
  }
    else if (secCount == 500 && button_pressed == 2){
       clearScreen(COLOR_BLUE);
       drawString5x7(20,40, "Second button!!!", fontFgColor, COLOR_BLUE);
       secCount = 0;
       redrawScreen = 1;
       //state_advance();
  }
    else if (secCount == 500 && button_pressed == 3){
       clearScreen(COLOR_BLUE);
       drawString5x7(20,40, "Third button!!!", fontFgColor, COLOR_BLUE);
       secCount = 0;
       redrawScreen = 1;
       //state_advance();
  }
    else if (secCount == 500 && button_pressed == 4){
       clearScreen(COLOR_BLUE);
       drawString5x7(20,40, "Fourth button!!!", fontFgColor, COLOR_BLUE);
       secCount = 0;
       redrawScreen = 1;
       //state_advance();
  }
    else if (secCount == 500 && button_pressed == 0) {
      clearScreen(COLOR_BLUE);
      drawString8x12(20,40, "PROBLEM!!!", fontFgColor, COLOR_BLUE);
      secCount = 0;
      redrawScreen = 1;
    }
}
  

void main()
{
  led_init();
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  //  switch_init(); //added
  buzzer_init(); //added
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  //drawString5x7(60,40, "Entered Main?", fontFgColor, COLOR_BLUE);

  while (1) {			/* forever */
  if (redrawScreen) {
    redrawScreen = 0;
    drawString5x7(20,40, "MAIN", fontFgColor, COLOR_BLUE);
    if (button_pressed == 1)
    drawString5x7(20,40, "First!!!", fontFgColor, COLOR_BLUE);
    else if (button_pressed == 2)
    drawString5x7(20,40, "Second!!!", fontFgColor, COLOR_BLUE);
    else if (button_pressed == 3)
    drawString5x7(20,40, "Third!!!", fontFgColor, COLOR_BLUE);
    else if (button_pressed == 4)
    drawString5x7(20,40, "Fourth!!!", fontFgColor, COLOR_BLUE);
    else if (button_pressed == 0)
    drawString5x7(40,60, "HMMMMM", fontFgColor, COLOR_BLUE);
    }
  P1OUT &= ~LED_GREEN;/* green off */

  or_sr(0x10);/**< CPU OFF */

  P1OUT |= LED_GREEN;/* green on */
  }
}
  
