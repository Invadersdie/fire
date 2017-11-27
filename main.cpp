#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void timer1_init()
{
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	// enable overflow interrupt
	TIMSK1 |= (1 << TOIE1);
}

int main(void) {

	PORTD |= (1 << 3)|(1 << 2);
	DDRB = 0xff;
	double angle = 0;     // #TODO POTENCIOMETR FOR *ANGLE*
	double sparkDelay = angle;
	timer1_init();
	double forDelay;
	
	while (1) {
		PORTB = 0b00000011;
		if (PIND2) {
			TCNT1 = 0;   //#Timer ON
			_delay_ms(sparkDelay);
			PORTB = 0b00000010;
			while (PIND2) {
			}
			forDelay = TCNT1;
			continue;
		}
		
		if (PIND3) {
			TCNT1 = 0; //#Timer ON
			_delay_ms(sparkDelay);
			PORTB = 0b00000001;
			while (PIND3) {
			}
			forDelay = TCNT1;
			//#Timer Off
			continue;
		}
		
		if (forDelay < 5) {sparkDelay = angle+ 1; break; };
		if (forDelay < 4) {sparkDelay = angle+ 2; break; };
		if (forDelay < 3) {sparkDelay = angle+ 3; break; };
		if (forDelay < 2) {sparkDelay = angle+ 4; break; };
		sparkDelay = angle; //default value
	}                                                  /* End event loop */
	
	return 0;
}
