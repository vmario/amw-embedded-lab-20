#pragma once

#include <stdint.h>

constexpr char DISPLAY_CODE_ENEMY{1}; ///< Kod sprite'a wroga.
constexpr char DISPLAY_CODE_PLAYER{2}; ///< Kod sprite'a gracza.
constexpr char DISPLAY_CODE_PLAYER_END{3}; ///< Kod sprite'a martwego gracza.

/**
 * Gra.
 */
struct Game {
	/**
	 * Inicjalizacja gry.
	 */
	void initialize() const;

	/**
	 * Pętla główna.
	 */
	void loop();

	/**
	 * Obsługa ramki.
	 */
	void frame();

	/**
	 * Rozpoczyna rozgrywkę.
	 */
	void start();

	/**
	 * Podlicza i drukuje punkty.
	 */
	void calculateCounts();

	/**
	 * Drukuje gracza.
	 */
	void printPlayer();

	/**
	 * Drukuje wrogów.
	 */
	void printEnemies();
	
	/**
	 * Wykrywa koniec gry.
	 */
	void detectGameOver();

private:
	volatile uint8_t hop; ///< Stan skoku.
	volatile bool stop; ///< Game over?
	volatile uint8_t span; ///< Odstęp między wrogami.
	volatile uint16_t enemies; ///< Wektor wrogów.
	volatile uint16_t counts; ///< Zdobyte punkty.
};

extern Game game; ///< Globalna instancja gry.
