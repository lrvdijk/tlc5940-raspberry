/**
 * Helios 3D LED Cube Client
 * -------------------------
 *
 * This program should run on the embedded processor of the LED Cube, which
 * controls the LED's.
 */

#ifndef RASPBERRY_GPIO_H_
#define RASPBERRY_GPIO_H_

#include "gpio.h"
#include <wiringPi.h>

// Some wiringPi constants we don't need
#undef LOW
#undef HIGH

/**
 * This class is based upon the wiringPi library, and therefore uses
 * the functions of that library to control the GPIO pins.
 * 
 * The wiring Pi library accesses the memory directly, and needs root 
 * to do that.
 * 
 * @see https://projects.drogon.net/raspberry-pi/wiringpi/
 */
class RaspberryGPIOPin : public BaseGPIOPin
{
	public:
		/**
		 * This creates a new pin, based on the given pin number.
		 * See the wiringPi website which number is actually which pin
		 */
		explicit RaspberryGPIOPin(int pin_num);
		virtual ~RaspberryGPIOPin() throw();

		void setPinMode(int pinmode);

		virtual void open();
		virtual void close();
		virtual bool is_open();

		virtual void setDirection(PinDirection direction);
		virtual PinDirection getDirection();

		virtual void setValue(PinValue value);
		virtual PinValue getValue();
		virtual inline void pulse()
		{
			this->setHigh();
			this->setLow();
		}
	
	private:
		int pinmode;
		int pinnum;
};

#endif
