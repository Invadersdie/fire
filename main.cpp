/*
   Demo of the simplest on/off button code
   Button connected to PD2
   LEDs connected to PB0..PB7
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#define DELAYTIME 500
int main(void) {
  // -------- Inits --------- //
  PORTD |= (1 << PD3)||(1 << PD2);  /* initialize pullup resistor on our input pin */
  DDRB = 0xff;                           /* set up all LEDs for output */
  bool stA=false,stB=false;
  // ------ Event loop ------ //
  while (1) {
    if (bit_is_clear(PIND, PD2)&&(!stA)) {            /* look for button press */
      stA=!stA;
      PORTB = 0b00000001;
      _delay_ms(DELAYTIME);
      continue;
    }
    if(bit_is_clear(PIND, PD2)&&(!stB)){
      stB=!stB;
      PORTB = 0b00000010;
      _delay_ms(DELAYTIME);
      continue;
    }
    stA=!stA;
    stB=!stB;
  }                                                  /* End event loop */
  return 0;
}
