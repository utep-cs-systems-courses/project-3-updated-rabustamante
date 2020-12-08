#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"



static char diaState = 0;
void diamondState()
{
  
  switch(diaState){
  case 0:
    diamondShape(100,100,COLOR_BLUE);
    diamondShape(110,110,COLOR_BLUE);
    diamondShape(120,120,COLOR_BLUE);
    diaState=1;
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


