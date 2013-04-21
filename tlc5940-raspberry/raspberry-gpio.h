/**
 * TLC5940 controller library for the Raspberry Pi
 * ===============================================
 *
 * With this library it is possible to control your TLC5940 LED driver
 * from your Raspberry Pi. It is a pure software based solution,
 * and does not require any kernel modifcations or whatsoever.
 *
 * Copyright (c) 2013 Lucas van Dijk <info@return1.net>
 * http://return1.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software 
 * is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
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
