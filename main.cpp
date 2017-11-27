#include <avr/io.h>
#include <util/delay.h>


int main(void) {
  // -------- Inits --------- //
  PORTD |= (1 << PD3)|(1 << PD2);  /* initialize pullup resistor on our input pin */
  DDRB = 0xff;                           /* set up all LEDs for output */
  ?? sparkDelay;  // TYPE "??"

  while (1) {
    PORTB = 0b00000011;
    if (bit_is_clear(PIND, PD2)) {            
      //#Timer ON
       _delay_ms(sparkDelay);  
		PORTB = 0b00000010;	   
         while (bit_is_clear(PIND, PD2)) {
            }
      //#Timer Off
      continue;
    }
	
    if (bit_is_clear(PIND, PD3)) {            
      //#Timer ON
       _delay_ms(sparkDelay);      
	   PORTB = 0b00000001;
         while (bit_is_clear(PIND, PD3)) {
            }
      //#Timer Off
      continue;
		 }
	while (true){
	if (timer_Timer < ??) {sparkDelay = ??; break; };
	if (timer_Timer < ??) {sparkDelay = ??; break; };
	if (timer_Timer < ??) {sparkDelay = ??; break; };
	if (timer_Timer < ??) {sparkDelay = ??; break; };
//default value 
	sparkDelay = ??;
	}
  }                                                  /* End event loop */
  return 0;
}
