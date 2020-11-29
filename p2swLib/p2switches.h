#ifndef switches_included
#define switches_included

#include "msp430.h"

unsigned int p2sw_read();
void p2sw_init(unsigned char mask);

#define SW1 BIT0 /* S1 is p2.0 */
#define SW2 BIT1 /* S2 is p2.1 */
#define SW3 BIT2 /* s3 is p2.2 */
#define SW4 BIT3 /* S4 is p2.3 */

#define SWITCHES (SW1 | SW2 | SW3 | SW4) /* only 4 switch on green board */
void switch_init();

void switch_interrupt_handler();
extern char switch_state_down1,switch_state_down2,switch_state_down3,switch_state_down4, switch_state_changed; /* effectively boolean */
#endif // included
