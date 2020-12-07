#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"

char dimState = 0;
char buzzState = 0;
char toggle_red()/* always toggle! */
{
  red_on = 1;
  led_changed = red_on;

  green_on =0;
  led_update();

}

char toggle_green()
{
  green_on = 1;
  led_changed = green_on;

  red_on = 0;
  led_update();

}
char toggle_red_green(){

  static char state =0;
  switch(state){

  case 0:
    toggle_green();
    state =1;
    break;

  case 1:
    toggle_red();
    state =0;
    break;

  default:
    state= 0;
    break;
  }

}
void  onLight75()

{
  switch(dimState){
  case 0:
      red_on =1;
      dimState =1;
  case 1:
      red_on =1;
      dimState =2;
  case 2:
      red_on =1;
     dimState =3;
  case 3:
     red_on =1;
     dimState =0;
  default:
      dimState =0;
      
  }
    led_update();
}
void  onLight50()
{
  
  switch(dimState){

    case 0:
      red_on =1;
      dimState =1;
    case 1:
      red_on = 1;
      dimState =2;
    case 2:
      red_on =0;
      dimState =3;
    case 3:
      red_on =0;
      dimState =0;
    default:
      dimState =0;
      
    }
    led_update();
}

void  onLight25()
{
  switch(dimState){

    case 0:
      red_on =0;
      dimState =1;
     
    case 1:
      red_on =0;
      dimState =2;
    case 2:
      red_on = 0;
      dimState =3;
    case 3:
      red_on =0;
      dimState =0;
    default:
    dimState =0;
      
    }
    led_update();
}
static char dim_state =0;
void dimLights()
{
  
  switch(dimState){
  case 0:
    red_on =1;
    dim_state=1;
  case 1:
    onLight25();
    dim_state = 2;
  case 2:
    onLight50();
    dim_state = 3;
   case 3:
    onLight75();
    dim_state = 4;
  
  case 4:
    red_on =0;
    dim_state = 0;
  default:
    dim_state =0 ;
  }
}
void buzzer_advance()

{
 static  int x  =1500;
  if(buzzState){
    x +=225;
    
  }
  else{
    x -=450;
  }
  short cycle = 2000000/x;
  buzzer_set_period(cycle);
}

void go_up()

{
  buzzState =1;
  red_on = 1;
  led_update();
 
}

void go_down()

{
  buzzState = 0;
  red_on= 0;
  led_update();
  
}

void main_state_advance()
{ 
  switch(buzzState){
  case 0:
    go_up();
    buzzer_advance();
    buzzState =1;
  case 1:
    go_down();
    buzzer_advance();
    buzzState = 0;
  }
}

void switches_state()
{
  
  switch(switch_state_changed){
  case 0:
    switch_interrupt_handler();
    buzzState++;
    break;

  case 1:

    switch_interrupt_handler();
    buzzState++;
    break;

  case 2:
    
    switch_interrupt_handler();
    buzzState++;
    break;

  case 3:
    
    switch_interrupt_handler();
    buzzState = 0;
    break;
  default:
    buzzState = 0;
  }
} 
