#include "splash.hpp"

#include "lcdDisplay.hpp"

#include <util/delay.h>

Splash splash;

void Splash::initialize() const
{
	lcdDisplay.clear();
	lcdDisplay.goTo(0, 0);
	lcdDisplay.write(" Initializing   ");
	lcdDisplay.goTo(0, 13);
	lcdDisplay.write(DISPLAY_CODE_ELLIPSIS);
	showProgress();
	lcdDisplay.clear();
}

void Splash::showProgress() const
{
	lcdDisplay.goTo(1, 0);
	for (int i{0}; i < DISPLAY_LENGTH; ++i) {
		lcdDisplay.write('\xff');
		_delay_ms(40);
	}
}
