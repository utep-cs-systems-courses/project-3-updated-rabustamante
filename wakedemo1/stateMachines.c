#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
static int buzzState;
char toggle_red()/* always toggle! */
{
  red_on = 1;
  led_changed = red_on;

  green_on =0;
  led_update();

}

char toggle_green(){
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

static char dimState =0;
void  onLight75()

{
  switch(dimState){
    case 0:
      toggle_red();
      
    case 1:
    case 2:
    case 3:
      red_on =0;
      
    default:
      dimState =0;
      
    }
    led_update();
}
void  onLight50()
{
  
  switch(dimState){

    case 0:
      
    case 1:
      toggle_red();     
    case 2:
    case 3:
      toggle_red();
      
     
    default:
      dimState =0;
      
    }
    led_update();
}

void  onLight25()
{
  dimState =0;
  switch(dimState){

    case 0:
      toggle_red();
     
    case 1:
    case 2:
    case 3:
      red_on =0;
    default:
    dimState =0;
      
    }
    led_update();
}

void dimLights()
{
  
  switch(dimState){
  case 0:
    toggle_red();
    dimState =1;
  case 1:
    onLight25();
    dimState =2;
  case 2:
    onLight50();
    dimState =3;
   case 3:
    onLight75();
    dimState = 4;
  
  case 4:
    red_on =0;
    dimState=0;
  default:
    dimState =0;
  }
}
void state_advance(){
}
void buzzer_advance()

{
 static  int x  =500;
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
  led_changed = red_on;
  led_update();
 
}

void go_down()

{
  buzzState = 0;
  red_on = 0;
  led_changed = green_on;
  led_update();
  
}

void main_state_advance()

{
 
  switch(buzzState){
  case 0:
    go_down();
    buzzer_advance();
    buzzState =1;
  case 1:
    go_up();
    buzzer_advance();
    buzzState = 0;
    
  }
}
void diamondState()
{
  
  static char diaState = 0;
  switch(diaState){
  case 0:
    diamondShape(100,100,COLOR_BLUE);
    diamondShape(110,110,COLOR_BLUE);
    diamondShape(120,120,COLOR_BLUE);
    switch_interrupt_handler();
    diaState =1;
    break;
  case 1:
     diamondShape(100,100,COLOR_DARK_VIOLE);
     diaState =2;
     break;
   case 2:
     diamondShape(100,100,COLOR_BLUE);
     diamondShape(110,110,COLOR_FIREBRICK);
     diaState =3;
     break;
  case 3:
    diamondShape(100,100,COLOR_BLUE);
    diamondShape(110,110,COLOR_BLUE);
    diamondShape(120,120,COLOR_CHOCOLATE);
    diaState =0;
    break;
  default:
    diaState=0;
    break;
  }
}
void switch_state()
{
  char switch_state_changed =0;
  switch(switch_state_changed){
  case 0:
    switch_interrupt_handler();
    break;
  case 1:
    switch_interrupt_handler();
    break;
  case 2:
    switch_interrupt_handler();
    break;
  case 3:
    switch_interrupt_handler();
    break;

  }

}
