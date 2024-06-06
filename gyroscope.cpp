#include "gyroscope.hpp"

#include "lcdDisplay.hpp"
#include "gpio.hpp"
#include "spi.hpp"

#include <avr/io.h>
#include <util/delay.h>

const Gyroscope gyroscope;

/**
 * Adresy rejestrów żyroskopu.
 */
enum REGISTER {
	REGISTER_SMPLRT_DIV = 25,
	REGISTER_CONFIGURATION = 26,
	REGISTER_ACCEL_CONFIG_2 = 29,
	REGISTER_ACCEL_XOUT_H = 59,
	REGISTER_GYRO_XOUT_H = 67,
	REGISTER_GYRO_YOUT_H = 69,
	REGISTER_GYRO_ZOUT_H = 71,
	REGISTER_SIGNAL_PATH_RESET = 104,
	REGISTER_USER_CTRL = 106,
	REGISTER_POWER_MGMT_1 = 107,
	REGISTER_WHO_AM_I = 117,
};

/**
 * Wybrane nastawy czujnika.
 */
enum {
	DEVICE_RESET = _BV(7) | _BV(0),
	SIGNAL_RESET = _BV(2) | _BV(1) | _BV(0),
};

void Gyroscope::initialize() const
{
	gpio.initialize();
	spi.initialize();

	spi.writeRegister(REGISTER_POWER_MGMT_1, DEVICE_RESET);
	_delay_ms(100);

	spi.writeRegister(REGISTER_SIGNAL_PATH_RESET, SIGNAL_RESET);
	_delay_ms(100);

	if (whoAmI() != 0x70) {
		lcdDisplay.goTo(0, 3);
		lcdDisplay.write("Incorrect");
		lcdDisplay.goTo(1, 3);
		lcdDisplay.write("sensor ID");
		while (true) ;
	}

	spi.writeRegister(REGISTER_CONFIGURATION, 6);
	spi.writeRegister(REGISTER_ACCEL_CONFIG_2, 6);
#if 0
	spi.writeRegister(REGISTER_SMPLRT_DIV, 255);
#endif
}

uint8_t Gyroscope::whoAmI() const
{
	return spi.readRegister(REGISTER_WHO_AM_I);
}

int16_t Gyroscope::measure() const
{
	return spi.readRegisterWord(REGISTER_GYRO_ZOUT_H);
}
