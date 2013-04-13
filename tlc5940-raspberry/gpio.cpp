/**
 * Helios 3D LED Cube Client
 * -------------------------
 *
 * This program should run on the embedded processor of the LED Cube, which
 * controls the LED's.
 */
 
#include "gpio.h"

void BaseGPIOPin::setOutput()
{
	this->setDirection(PinDirection::OUT);
}

void BaseGPIOPin::setInput()
{
	this->setDirection(PinDirection::IN);
}

void BaseGPIOPin::setHigh()
{
	this->setValue(PinValue::HIGH);
}

void BaseGPIOPin::setLow()
{
	this->setValue(PinValue::LOW);
}
