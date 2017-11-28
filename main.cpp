#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h> 

void timer_init() {
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	// enable overflow interrupt
	// TIMSK1 |= (1 << TOIE1);
	TCCR2A = 0;     // set entire TCCR1A register to 0
	TCCR2B = 0;     // same for TCCR1B
	TCCR2B |= (1 << CS10);
	TCCR2B |= (1 << CS12);
	TCNT2 = 0;
}
void adc0_init() {
	// http://samou4ka.net/page/analogo-cifrovoj-preobrazovatel-mk-atmega8
	ADMUX=0; //#PORT
	ADCSRA=0x86; //0b10000110

}
int newAngle() {
	ADCSRA |= 0x40;
	int data = (int)(ADCW/4);
	return data;
}
void _delay_us_my (int delay) {
	for (int i = 0; i<delay; i++){
		_delay_us(1);
	}
}
void count(){
	int freqEng = TCNT2;
	TCNT2 = 0;
}


int main(void) {
	
	bool temp;
	int forDelay;
	int loops=0;
	
	PORTD |= (1 << 3)|(1 << 2);
	DDRB = 0b00000011;
	
	timer_init();
	adc0_init();
	int angle = newAngle();     // #TODO POTENCIOMETR FOR *ANGLE*
	int sparkDelay = 0;
	
	while (1) {
		
		if (PIND2) {
			loops++;
			temp = false;
			TCNT1 = 0;   //#Timer ON
			_delay_us_my(angle);
			_delay_us_my(sparkDelay);
			PORTB = 0b00000010;
			while (PIND2) {
				if(!temp){
					angle = newAngle();
					if (loops == 10) {
						count();
						loops = 0;
						};
					temp=true;
				};
			}
			forDelay = TCNT1;
		}
		
		if (PIND3) {
			temp = false;
			TCNT1 = 0; //#Timer ON
			_delay_us_my(angle);
			_delay_us_my(sparkDelay);
			PORTB = 0b00000001;
			while (PIND3) {
				if(!temp){angle = newAngle();temp=true;};
			}
			forDelay = TCNT1;
		}
		
		if			(forDelay > 0x0775) {sparkDelay = 204;}
		else if (forDelay > 0x0598) {sparkDelay = 120;}
		else if (forDelay > 0x0459) {sparkDelay = 84;}
		else if (forDelay > 0x03BA) {sparkDelay = 60;}
		else if (forDelay > 0x0332) {sparkDelay = 48;}
		else if (forDelay > 0x02CC) {sparkDelay = 30;}
		else if (forDelay > 0x027C) {sparkDelay = 24;}
		else if (forDelay > 0x023C) {sparkDelay = 24;}
		else if (forDelay > 0x0208) {sparkDelay = 18;}
		else if (forDelay > 0x01DD) {sparkDelay = 12;}
		else if (forDelay > 0x01B8) {sparkDelay = 11;}
		else if (forDelay > 0x0199) {sparkDelay = 10;}
		else if (forDelay > 0x017D) {sparkDelay = 8;}
		else if (forDelay > 0x0165) {sparkDelay = 6;}
		else if (forDelay > 0x0150) {sparkDelay = 4;}
		else if (forDelay > 0x013E) {sparkDelay = 2;}
		else if (forDelay > 0x012D) {sparkDelay = 1;}
		else if (forDelay > 0x011E) {sparkDelay = 0;}
		else sparkDelay = 0; //default value
		
		}                                                  /* End event loop */
		return 0;
	}
