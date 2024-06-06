#include "lcdDisplay.hpp"
#include "entropy.hpp"
#include "game.hpp"
#include "splash.hpp"
#include "gyroscope.hpp"

#include <avr/interrupt.h>

/**
 * Funkcja główna.
 */
int main()
{
	constexpr uint8_t ELLIPSIS[] = {
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00010101,
		0b00000000,
	};

	constexpr uint8_t ENEMY[] = {
		0b00000000,
		0b00011111,
		0b00011011,
		0b00010101,
		0b00011011,
		0b00011111,
		0b00000000,
		0b00000000,
	};

	constexpr uint8_t PLAYER[] = {
		0b00000000,
		0b00001100,
		0b00011010,
		0b00001001,
		0b00011010,
		0b00001100,
		0b00000000,
		0b00000000,
	};

	constexpr uint8_t PLAYER_END[] = {
		0b00000000,
		0b00010001,
		0b00001010,
		0b00000100,
		0b00001010,
		0b00010001,
		0b00000000,
		0b00000000,
	};

	lcdDisplay.initialize();
	lcdDisplay.addSymbol(ELLIPSIS, DISPLAY_CODE_ELLIPSIS);
	lcdDisplay.addSymbol(ENEMY, 1);
	lcdDisplay.addSymbol(PLAYER, 2);
	lcdDisplay.addSymbol(PLAYER_END, 3);

	splash.initialize();
	gyroscope.initialize();
	entropy.initialize();
	entropy.make();
	game.initialize();

	sei();

	game.start();

	while (true) {
		game.loop();
	}
}
