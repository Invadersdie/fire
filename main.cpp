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
	// TIMSK1 |= (1 << TOIE1);
}
void adc0_init()
{
	// http://samou4ka.net/page/analogo-cifrovoj-preobrazovatel-mk-atmega8
	ADMUX=0; //#PORT
	ADCSRA=0x86; //0b10000110
}
double newAngle()
{
	ADCSRA |= 0x40;
	data = ADCW;
	return //#TODO
}

int main(void) {
	
	bool temp;
	double angle1;
	double forDelay;
	
	PORTD |= (1 << 3)|(1 << 2);
	DDRB = 0b00000011;
	
	timer1_init();
	adc0_init();
	double angle = newAngle();     // #TODO POTENCIOMETR FOR *ANGLE*
	double sparkDelay = angle;
	
	while (1) {
		
		if (PIND2) {
			temp = false;
			TCNT1 = 0;   //#Timer ON
			_delay_ms(sparkDelay);
			PORTB = 0b00000010;
			while (PIND2) {
				if(!temp){angle1 = newAngle();temp=true;};
			}
			forDelay = TCNT1-angle;
			continue;
		}
		if (PIND3) {
			temp = false;
			TCNT1 = 0; //#Timer ON
			_delay_ms(sparkDelay);
			PORTB = 0b00000001;
			while (PIND3) {
				if(!temp){angle1 = newAngle();temp=true;};
			}
			forDelay = TCNT1-angle;
			continue;
		}
		
		if      (forDelay > 0x0775) {sparkDelay = angle + 0x22;};
		else if (forDelay > 0x0598) {sparkDelay = angle + 0x14;};
		else if (forDelay > 0x0459) {sparkDelay = angle + 0x0E;};
		else if (forDelay > 0x03BA) {sparkDelay = angle + 0x0A;};
		else if (forDelay > 0x0332) {sparkDelay = angle + 0x08;};
		else if (forDelay > 0x02CC) {sparkDelay = angle + 0x05;};
		else if (forDelay > 0x027C) {sparkDelay = angle + 0x04;};
		else if (forDelay > 0x023C) {sparkDelay = angle + 0x04;};
		else if (forDelay > 0x0208) {sparkDelay = angle + 0x03;};
		else if (forDelay > 0x01DD) {sparkDelay = angle + 0x02;};
		else if (forDelay > 0x01B8) {sparkDelay = angle + 0x03;};
		else if (forDelay > 0x0199) {sparkDelay = angle + 0x01;};
		else if (forDelay > 0x017D) {sparkDelay = angle + 0x02;};
		else if (forDelay > 0x0165) {sparkDelay = angle + 0x01;};
		else if (forDelay > 0x0150) {sparkDelay = angle + 0x02;};
		else if (forDelay > 0x013E) {sparkDelay = angle + 0x01;};
		else if (forDelay > 0x012D) {sparkDelay = angle + 0x01;};
		else if (forDelay > 0x011E) {sparkDelay = angle;};
		
		sparkDelay = angle; //default value
		angle = angle1;
		}                                                  /* End event loop */
		
		return 0;
	}
