#include "spi.hpp"

#include "gpio.hpp"

#include <avr/io.h>
#include <util/delay.h>

#define SOLUTION

const Spi spi;

void Spi::initialize() const
{
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(CPOL) | _BV(CPHA);
}

uint8_t Spi::transfer(uint8_t byte=0) const
{
	SPDR = byte;
	while (bit_is_clear(SPSR, SPIF)) ;
	return SPDR;
}

uint8_t Spi::readRegister(uint8_t address) const
{
	gpio.chipSelect(true);

	transfer(address | _BV(7));
	uint8_t value{transfer()};

	gpio.chipSelect(false);

	return value;
}

int16_t Spi::readRegisterWord(uint8_t address) const
{
	gpio.chipSelect(true);

	transfer(address | _BV(7));
	int16_t value = transfer() << 8;
	value |= transfer();

	gpio.chipSelect(false);

	return value;
}

void Spi::writeRegister(uint8_t address, uint8_t value) const
{
	gpio.chipSelect(true);

	transfer(address);
	transfer(value);

	gpio.chipSelect(false);
}
