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
	DDRB = 0b00000011;
	double angle = PIND1;     // #TODO POTENCIOMETR FOR *ANGLE*
	double sparkDelay = angle;
	timer1_init();
	double forDelay;
	
	while (1) {
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
			continue;
		}
	
		if (forDelay < 0x0775) {sparkDelay = angle+ 0x22; break; };
		if (forDelay < 0x0598) {sparkDelay = angle+ 0x14; break; };
		if (forDelay < 0x0459) {sparkDelay = angle+ 0x0E; break; };
		if (forDelay < 0x03BA) {sparkDelay = angle+ 0x0A; break; };
		if (forDelay < 0x0332) {sparkDelay = angle+ 0x08; break; };
		if (forDelay < 0x02CC) {sparkDelay = angle+ 0x05; break; };
		if (forDelay < 0x027C) {sparkDelay = angle+ 0x04; break; };
		if (forDelay < 0x023C) {sparkDelay = angle+ 0x04; break; };	
		if (forDelay < 0x0208) {sparkDelay = angle+ 0x03; break; };	
		if (forDelay < 0x01DD) {sparkDelay = angle+ 0x02; break; };
		if (forDelay < 0x01B8) {sparkDelay = angle+ 0x03; break; };
		if (forDelay < 0x0199) {sparkDelay = angle+ 0x01; break; };
		if (forDelay < 0x017D) {sparkDelay = angle+ 0x02; break; };
		if (forDelay < 0x0165) {sparkDelay = angle+ 0x01; break; };
		if (forDelay < 0x0150) {sparkDelay = angle+ 0x02; break; };
		if (forDelay < 0x013E) {sparkDelay = angle+ 0x01; break; };
		if (forDelay < 0x012D) {sparkDelay = angle+ 0x01; break; };
		if (forDelay < 0x011E) {sparkDelay = angle; break; };
	
		sparkDelay = angle; //default value
	}                                                  /* End event loop */
	
	return 0;
}
