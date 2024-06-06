#pragma once

/**
 * Generator entropii.
 */
struct Entropy {
	/**
	 * Inicjalizacja generatora.
	 */
	void initialize() const;

	/**
	 * Generuje entropię.
	 */
	void make() const;
};

extern const Entropy entropy; ///< Globalna instancja generatora entropii.
