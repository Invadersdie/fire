/*
   Demo of the simplest on/off button code
   Button connected to PD2
   LEDs connected to PB0..PB7
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#define SPARKDELAY 500
#define SPARKTIME 500
int main(void) {
  // -------- Inits --------- //
  PORTD |= (1 << PD3)|(1 << PD2);  /* initialize pullup resistor on our input pin */
  DDRB = 0xff;                           /* set up all LEDs for output */
  bool sparkA=false;
  bool sparkB=false;
  // ------ Event loop ------ //
  while (1) {
    PORTB = 0b00000000;
    if (bit_is_clear(PIND, PD2)) {            /* look for button press */
      //Timer ON
       _delay_ms(SPARKDELAY);      
         while {bit_is_clear(PIND, PD2) {
            PORTB = 0b00000001;
            }
      continue;
    }
    if(bit_is_clear(PIND, PD3)&&(!sparkB)){
      sparkB=!sparkB;
      _delay_ms(SPARKDELAY);
      PORTB = 0b00000010;
      _delay_ms(SPARKTIME);
      continue;
    }
   //After all shit check timer and set SPARKDELAY
    sparkA=false;
    sparkB=false;
  }                                                  /* End event loop */
  return 0;
}
