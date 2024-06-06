#include "entropy.hpp"

#include "lcdDisplay.hpp"
#include "splash.hpp"

#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>

const Entropy entropy;

void Entropy::initialize() const
{
	ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	while (bit_is_set(ADCSRA, ADSC)) ;
	_delay_ms(10);
}

void Entropy::make() const
{
	lcdDisplay.goTo(0, 0);
	lcdDisplay.write("Getting entropy");
	lcdDisplay.goTo(0, 15);
	lcdDisplay.write(DISPLAY_CODE_ELLIPSIS);

	uint8_t iterations{0};
	uint16_t lastAdc{0};
	uint16_t seed = lastAdc;
	while (true) {
		ADCSRA |= _BV(ADSC);
		while (bit_is_set(ADCSRA, ADSC)) ;
		seed += ADC;
		if (ADC != lastAdc) {
			lastAdc = ADC;
			if (++iterations >= 255) {
				break;
			}
		}
	}

	seed &= 0xffff;
	srand(seed);
}
