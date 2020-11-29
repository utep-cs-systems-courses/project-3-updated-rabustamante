#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcddraw.h"
#include "lcdtypes.h"

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
  toggle_red();
}


void buzzer_advance()

{

  char buzzer_state;

  /* frequency we want*/
  static int x  = 500; 

  if(buzzer_state){

    x+=225;

  }

  else{

    x -= 400;

  }

  /* coverts for buzzer set period*/
  short cycle = 2000000/x;

  buzzer_set_period( cycle);

}
void go_up()

{

  int sb = 1;

  toggle_green();

}

void go_down()

{

  int sb = 0;
  toggle_red();
}

void main_state_advance()

{
  
  static char  state =0;
  switch(state){
  case 0:
  case 1:
    go_up();
    state++;
    break;
    
  case 2:
    go_down();
    state =0;

  default:
    break;

  }
}
void drawDiamond()
{
  static char diaState =0;
  switch(diaState){
  case 0:
    diamondShape(50,50,COLOR_BLUE);
      diaState++;
      break;
  case 1:
    diamondShape(50,50,COLOR_DARK_VIOLE);
    diaState++;
    break;
   case 2:
    diamondShape(50,50,COLOR_FIREBRICK);
    diaState++;
    break;
  case 3:
    diamondShape(50,50,COLOR_CHOCOLATE);
    diaState =0;;
    break;
  default:
    diaState =0;
    break;
  }
}