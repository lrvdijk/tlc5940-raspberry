/**
 * Helios 3D LED Cube Client
 * -------------------------
 *
 * This program should run on the embedded processor of the LED Cube, which
 * controls the LED's.
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>

enum class PinDirection : std::uint8_t
{
	IN = 0,
	OUT
};

enum class PinValue : std::uint8_t
{
	LOW = 0,
	HIGH
};

/**
 * This is an abstract base class for GPIO pins.
 * 
 * Subclasses should allow control of a specific GPIO pin, suitable
 * for the used processor.
 */
class BaseGPIOPin
{
	public:
		virtual void open() = 0;
		virtual void close() = 0;
		virtual bool is_open() = 0;
		
		virtual void setDirection(PinDirection direction) = 0;
		virtual PinDirection getDirection() = 0;

		// Some shortcuts
		virtual void setOutput();
		virtual void setInput();

		virtual void setValue(PinValue value) = 0;
		virtual PinValue getValue() = 0;

		// For the value also some shortcuts
		virtual void setHigh();
		virtual void setLow();
		
		virtual inline void pulse() 
		{
			this->setHigh();
			this->setLow();
		}
};

#endif
