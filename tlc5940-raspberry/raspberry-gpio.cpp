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
 
#include "raspberry-gpio.h"
#include <stdexcept>
#include <iostream>

RaspberryGPIOPin::RaspberryGPIOPin(int pin_num)
{
	this->pinnum = pin_num;
}

RaspberryGPIOPin::~RaspberryGPIOPin() throw()
{
}

void RaspberryGPIOPin::setPinMode(int pinmode)
{
	// Call wiringPi function
	pinMode(this->pinnum, pinmode);
	this->pinmode = pinmode;
}

void RaspberryGPIOPin::open()
{
}

void RaspberryGPIOPin::close()
{
	// Can't do anything here
}

bool RaspberryGPIOPin::is_open()
{
	return true;
}

void RaspberryGPIOPin::setValue(PinValue value)
{
	switch(value)
	{
		case PinValue::LOW:
			digitalWrite(this->pinnum, 0);
			//std::cout << "Pin " << this->pinnum << " low." << std::endl;
		break;
		case PinValue::HIGH:
			digitalWrite(this->pinnum, 1);
			//std::cout << "Pin " << this->pinnum << " high." << std::endl;
		break;
	}
}

PinValue RaspberryGPIOPin::getValue()
{
	int value = digitalRead(this->pinnum);
	
	return value == 1 ? PinValue::HIGH : PinValue::LOW;
}

void RaspberryGPIOPin::setDirection(PinDirection direction)
{
	switch(direction)
	{
		case PinDirection::IN:
			this->setPinMode(INPUT);
		break;
		case PinDirection::OUT:
			this->setPinMode(OUTPUT);
		break;
	}
}

PinDirection RaspberryGPIOPin::getDirection()
{
	switch(this->pinmode)
	{
		case INPUT:
			return PinDirection::IN;
		
		case OUTPUT:
			return PinDirection::OUT;
			
		default:
			throw std::runtime_error("Unknown pindirection");
	}
}
