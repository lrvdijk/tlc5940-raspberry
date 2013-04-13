/**
 * Helios 3D LED Cube Client
 * -------------------------
 *
 * This program should run on the embedded processor of the LED Cube, which
 * controls the LED's.
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
