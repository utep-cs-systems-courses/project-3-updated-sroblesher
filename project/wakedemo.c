#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "stateMachines.h"

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
static int screen1Count = -1;
static int screen2Count = 0;
static int screen3Count = -1;
static int screen4Count = -1;
static int lastState = -1;

//Draws a shape of a spaceship with parameters as the center of the shape
void drawSpaceship(u_char initialCol, u_char initialRow)
{
  //Draw Triangle
  for (u_char row = 0; row < 11; row++)
    for (u_char col = 0;  col <= row; col++){  //left to right
      //drawPixel(initialCol+col, row + initialRow, fontFgColor);
      //drawPixel(initialCol-col, row + initialRow, fontFgColor);
      drawPixelAssembly(col, initialCol, row+initialRow, fontFgColor);
    }  
  //Draw rectangle 1
  for (u_char row = 0; row < 9; row++)
    for (u_char col = 0; col < 4; col++)
      drawPixel(col + initialCol - 7, row + initialRow - 1, fontFgColor);
  //Draw rectangle 2
  for (u_char row = 0; row < 9; row++)
    for (u_char col = 0; col < 4; col++)
      drawPixel(col + initialCol + 4, row + initialRow - 1, fontFgColor);
  //Draw rectangle 3
  for (u_char row = 0; row < 3; row++)
    for (u_char col = 0; col < 7; col++)
      drawPixel(col + initialCol - 3, row + initialRow + 11, fontFgColor);
}

//Erase pixels of spaceship with parameters as center
void eraseSpaceship(u_char initialCol, u_char initialRow)
{
  //Erase rectangle covering the spaceship
  if (centerValid(initialCol, initialRow)){
  for (u_char row = initialRow-2; row < initialRow + 25; row++)
    for (u_char col = initialCol - 15; col < initialCol + 15; col++)
      drawPixel(col, row, COLOR_BLUE);
  }
}

//Erase pixels of a string displayed
void eraseString()
{
  //Erase rectangle covering a specific string
  for (u_char row = 20; row < 100; row++)
    for (u_char col = 100; col < 120; col++)
      drawPixel(col, row, COLOR_BLUE);
}

//Display on Scree depending on the button pressed

//Button 1 pressed
//Show how much luminosity on red light
char first_screen()
{
  switch(screen1Count){
  case 0:
    eraseString();
    drawString8x12(20,100, "12.5% dim!", COLOR_BLACK , COLOR_RED);
    break;
  case 1:
    eraseString();
    drawString8x12(20,100, "100% dim!!", COLOR_BLACK , COLOR_RED);
    break;
  case 2:
    eraseString();
    drawString8x12(20,100, "25% dim!!!", COLOR_BLACK , COLOR_RED);
    screen1Count = -1;
    break;
  default:
    eraseString();
    drawString8x12(20,100, "25% dim!!!", COLOR_BLACK , COLOR_RED);
    screen1Count = -1;
    break;
  }
  screen1Count++;
}

//Button 2 pressed
char second_screen()
{
  return 1;
}

//Button 4 pressed
//Spaceship going up and returning
char fourth_screen()
{
  screen4Count++;
 
  switch(screen4Count){
  case 0:
    eraseSpaceship(20,10);
    drawSpaceship(20,110);
    break;
  case 1:
    eraseSpaceship(20,110);
    drawSpaceship(20,70);
    break;
  case 2:
    eraseSpaceship(20,70);
    drawSpaceship(20,40);
    break;
  case 3:
    eraseSpaceship(20,40);
    drawSpaceship(20, 10);
    break;
  default:
    eraseSpaceship(20,10);
    screen4Count = -1;
    break;
  }
}

//Button 3 pressed
//Cool spaceship effect
char third_screen()
{
  screen4Count++;
 
  switch(screen4Count){
  case 3:
    eraseSpaceship(110,10);
    eraseSpaceship(20,10);
    drawSpaceship(20,110);
    drawSpaceship(110,110);
    break;
  case 2:
    eraseSpaceship(110,110);
    eraseSpaceship(20,110);
    drawSpaceship(20,70);
    drawSpaceship(110,70);
    break;
  case 1:
    eraseSpaceship(110,70);
    eraseSpaceship(20,70);
    drawSpaceship(20,40);
    drawSpaceship(110,40);
    break;
  case 0:
    eraseSpaceship(110,40);
    eraseSpaceship(20,40);
    drawSpaceship(20, 10);
    drawSpaceship(110, 10);
    break;
  default:
    //eraseSpaceship(110,10);
    eraseSpaceship(20,10);
    screen4Count = -1;
    break;
  }
}

//Display on screen depending on button pressed
void screen_advance()
{
  char changed = 0;  
  
  if (state == 1) {
    first_screen();
  }
  if (state == 2) {
    second_screen();
  }
  if (state == 3) {
    third_screen();
  }
  if (state == 4) {
    fourth_screen();
  }

  led_changed = changed;
  led_update();
}


//Every 1/250 seconds
void wdt_c_handler()
{
  static int secCountState1 = 0;
  static int secCountState2 = 0;
  static int secCountState3 = 0;
  static int secCountState4 = 0;
  
  if (state == 1) {
    state_advance();
    if (++secCountState1 == 1000) {		/* once/4 secs */
      secCountState1 = 0;
      fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
      redrawScreen = 1;
    }
  }
  else if (state == 2) {
    if (++secCountState2 == 750) {		/* once/3 sec */
      secCountState2 = 0;
      fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
      redrawScreen = 1;
      state_advance();
    }
  }
  else if (state == 3) {
    if (++secCountState3 == 125) {		/* twice/sec */
      secCountState3 = 0;
      fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
      redrawScreen = 1;
      state_advance();
    }
  }
  else if (state == 4) {
    if (++secCountState4 == 125) {		/* twice/sec */
      secCountState4 = 0;
      fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
      redrawScreen = 1;
      state_advance();
    }
  }
  else {
    if (++secCountState4 == 250) {		/* once/sec */
      secCountState4 = 0;
      fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
      redrawScreen = 1;
    }
  }
}
  

void main()
{
  //P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  // P1OUT |= LED_GREEN;
  led_init();
  //P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  //led_init();
  buzzer_init();
  switch_init();
  //green_on ^= 1;
  red_on =1;
  led_update();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(80,140, "Awake", fontFgColor, COLOR_BLUE);
      //If last button pressed is not the same as the current button pressed
      if (lastState != state){ 
	clearScreen(COLOR_BLUE);
	lastState = state;
	buzzer_set_period(0);
      }
      //If button 1
      if (state == 1) {
	drawString8x12(20,40, "Button", COLOR_BLACK , COLOR_RED);
	drawString11x16(40,60, "1", COLOR_BLACK , COLOR_RED);
	drawString8x12(20,80,"Dim light", COLOR_BLACK , COLOR_RED);
	screen_advance();
      }
      //If button 2
      else if (state == 2) {
	drawString8x12(40,60, "Button", COLOR_BLACK , COLOR_RED);
	drawString11x16(60,80, "2", COLOR_BLACK , COLOR_RED);
	drawString8x12(20,60, "Defectuous", COLOR_BLACK , COLOR_RED);
	screen_advance();
      }
      //If button 3
      else if (state == 3) {
	drawString8x12(40,60, "Button", COLOR_BLACK , COLOR_RED);
	drawString11x16(60,90, "3", COLOR_BLACK , COLOR_RED);
	screen_advance();
      }
      //If button 4
      else if (state == 4) {
	drawString8x12(40,60, "Button", COLOR_BLACK , COLOR_RED);
	drawString11x16(60,90, "4", COLOR_BLACK , COLOR_RED);
	screen_advance();
      }
      else {
	drawString8x12(20,40, "Welcome!!!", COLOR_BLACK , COLOR_RED);
	drawString8x12(30,70, "to this", COLOR_BLACK , COLOR_RED);
	drawString8x12(20,100, "ugly Lab :)", COLOR_BLACK , COLOR_RED);
      }
    }
    //  P1OUT &= ~LED_GREEN;	/* green off */
    //green_on = 0;
    red_on = 0;
    led_changed = 1;
    led_update();
    //green_on ^= 1;
    or_sr(0x10);		/**< CPU OFF */
    //P1OUT |= LED_GREEN;		/* green on */
    red_on = 1;
    //   green_on ^= 1;
    led_changed = 1;
    led_update();
  }
}
    



