#pragma once

#include <stdint.h>

constexpr uint8_t DISPLAY_LENGTH{16}; ///< Szerokość wyświetlacza.
constexpr char DISPLAY_CODE_ELLIPSIS{0}; ///< Kod wielokropka.

/**
 * Splash.
 */
struct Splash {
	/**
	 * Inicjalizacja splasha.
	 */
	void initialize() const;

	/**
	 * Pasek postępu.
	 */
	void showProgress() const;
};

extern Splash splash; ///< Globalna instancja splasha.
