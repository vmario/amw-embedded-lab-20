#pragma once

#include <stdint.h>

/**
 * Sterownik akcelerometru/żyroskopu MPU-6500.
 */
struct Gyroscope {
	/**
	 * Inicjalizuje żyroskop i szynę danych.
	 */
	void initialize() const;

	/**
	 * Odczytuje identyfikator układu scalonego.
	 *
	 * @return Identyfikator.
	 */
	uint8_t whoAmI() const;

	/**
	 * Odczytuje pomiar.
	 *
	 * @return Wynik pomiaru.
	 */
	int16_t measure() const;
};

/**
 * Instancja sterownika żyroskopu.
 */
extern const Gyroscope gyroscope;
