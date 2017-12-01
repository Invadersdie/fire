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
}
void adc0_init() {
	// http://samou4ka.net/page/analogo-cifrovoj-preobrazovatel-mk-atmega8
	ADMUX=0;        //#PORT
	ADCSRA=0x86;    //0b10000110

}
int newAngle() {
	ADCSRA |= 0x40;
	return (int)(ADCW/4);
}
void _delay_ms_my (int delay) {
	for (int i = 0; i<delay; i++){
		_delay_ms(1);
	}
}
void _delay_us_my (int delay) {
    for (int i = 0; i<delay; i++){
		_delay_us(1);
	}
}

int countFreq(int timer){
	int freqEng = timer*8;
	TCNT1 = 0;
    return freqEng;
}
int newChargeDelay(int curFreq){
    if      (curFreq>6000)  {return 0;}
    else if (curFreq>5000)  {return 1;}
    else if (curFreq>4000)  {return 2;}
    else if (curFreq>3000)  {return 5;}
    else if (curFreq>2000)  {return 10;}
    else if (curFreq>1000)  {return 25;}
    else if (curFreq>500)   {return 55;}
    else if (curFreq>400)   {return 70;}
    else if (curFreq>300)   {return 95;}
}

int main(void) {
	
	bool temp;
	PORTD |= (1 << 3)|(1 << 2);
	DDRB = 0b00000011;
	
	timer_init();
	adc0_init();
	int angle = newAngle();     
	int sparkDelay = 0;
	
	while (1) {
		
        if (PIND2) {
            TCNT2=0;
            temp = true;
            freq = countFreq(TCNT1);                    //Frequency;
            _delay_ms_my(angle);                        //Ugol FIX;
            _delay_us_my(sparkDelay);                   //FUOZ;
            PORTB = 0b00000000;                         //SPARK! 
			
            while (PIND2) {
                if(temp){
                    angle = newAngle(); 
                    chargeDelay=newChargeDelay(freq); 
                    temp=false;
                };
			};
            _delay_ms_my(chargeDelay);
            PORTB = 0b00000010;  
            
        }
		if (PIND3) {
            TCNT2=0;
            temp = true;
            freq = countFreq(TCNT1);                    //Frequency;
            _delay_ms_my(angle);                        //Ugol FIX;
            _delay_us_my(sparkDelay);                   //FUOZ;
            PORTB = 0b00000000;                         //SPARK! 
			
            while (PIND3) {
                if(temp){
                    angle = newAngle(); 
                    chargeDelay=newChargeDelay(freq); 
                    temp=false;
                    };
			};
            _delay_ms_my(chargeDelay);                  //DelayCharge
            PORTB = 0b00000001;  
        }
		if (TCNT2>927С) {PORTB = 0b00000000};
	}                                                  /* End event loop */
return 0;
}
