#ifndef buzzer_included
#define buzzer_included

extern short x;

extern int buzzer_state;



void buzzer_init();

void buzzer_set_period(short cycles);

void buzzer_advance();

#endif // included
