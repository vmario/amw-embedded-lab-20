#include "game.hpp"

#include "lcdDisplay.hpp"
#include "splash.hpp"
#include "gyroscope.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include <stdio.h>
#include <stdlib.h>

Game game;

enum {
	HOP_DOWN = 2, ///< Przy tej wartości gracz spada na dół.
	HOP_UP = 6, ///< Wysokość skoku.
};

ISR(TIMER1_OVF_vect)
{
	game.frame();
}

void Game::frame()
{
	if (stop) {
		return;
	}

	calculateCounts();
	printEnemies();
	printPlayer();
	detectGameOver();
}

void Game::start()
{
	enemies = 0;
	span = 0;
	counts = 0;
	lcdDisplay.clear();
	stop = false;
}

void Game::loop()
{
}

void Game::initialize() const
{
	TCCR1B = _BV(CS11) | _BV(CS10);
	TIMSK1 = _BV(TOIE1);
}

void Game::calculateCounts()
{
	char buf[DISPLAY_LENGTH + 1];

	lcdDisplay.goTo(0, 11);
	snprintf(buf, sizeof(buf), "%05u", counts);
	lcdDisplay.write(buf);
	counts++;

	if (counts == UINT16_MAX) {
		stop = true;
		lcdDisplay.goTo(0, 0);
		lcdDisplay.write("THE END");
		return;
	}
}

void Game::printPlayer()
{
	if (hop > 0) {
		hop--;
	}

	if (hop > HOP_DOWN) {
		lcdDisplay.goTo(0, 0);
		lcdDisplay.write(DISPLAY_CODE_PLAYER);
	} else {
		lcdDisplay.goTo(0, 0);
		lcdDisplay.write(' ');
		lcdDisplay.goTo(1, 0);
		lcdDisplay.write(DISPLAY_CODE_PLAYER);
	}
}

void Game::printEnemies()
{
	int16_t probability{5000};
	uint8_t density{5};

	if (counts > 100) {
		probability = 10000;
	}

	if (counts > 200) {
		probability = 15000;
	}

	if (counts > 300) {
		density = 4;
	}

	enemies <<= 1;
	if (span == 0) {
		if (rand() < probability) {
			enemies |= 1;
			span = density;
		}
	} else {
		span--;
	}

	lcdDisplay.goTo(1, 0);
	for (uint8_t i{0}; i < 16; ++i) {
		if (enemies & (1 << (15 - i))) {
			lcdDisplay.write(DISPLAY_CODE_ENEMY);
		} else {
			lcdDisplay.write(' ');
		}
	}
}

void Game::detectGameOver()
{
	if (hop < HOP_DOWN && enemies & 0x8000) {
		lcdDisplay.goTo(0, 0);
		lcdDisplay.write(' ');
		lcdDisplay.goTo(1, 0);
		lcdDisplay.write(DISPLAY_CODE_PLAYER_END);
		stop = 1;

		lcdDisplay.goTo(0, 0);
		lcdDisplay.write("GAME OVER");
	}
}
