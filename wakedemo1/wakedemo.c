#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
void wdt_c_handler()

{
  static int secCount = 0;
  secCount ++;
  if( secCount ==  250){
    secCount =0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }

  if(secCount == 250 && switch_state_changed ==0){
    switch_state();
     redrawScreen = 0;
     secCount ==0;
     
}
if(secCount == 250  && switch_state_changed ==1){
    switch_state();
    secCount =0;
     redrawScreen = 0;
    
}

if(secCount !=250 && switch_state_changed ==2){
    switch_state();
    secCount =0;
     redrawScreen = 0;
    
}
 if(secCount != 250 && switch_state_changed ==3){
    switch_state();
    secCount =0;
    redrawScreen = 0;
 }

}
 

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  led_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  static char state =0;
   while (1) {			/* forever */
   if (redrawScreen) {
      drawString11x16(20,20, "hello", fontFgColor, COLOR_BLUE);
     
      switch(state){
      case 0:
	diamondState();
	state =1;
	break;
      case 1:
	diamondState();
	state =2;
	break;
      case 2:
	diamondState();
	state =3;
	break;
      case 3:
	diamondState();
	state =0;
      default:
	state =0;
	break;
      }
   
      redrawScreen = 0;
   }
   
  
   P1OUT &= ~LED_GREEN;/* green off */
   or_sr(0x10);/**< CPU OFF */
   P1OUT |= LED_GREEN;/* green on */
   }
}



    
    



