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

#include <iostream>
#include <array>

#include "gpio.h"

#ifndef TLC_CONTROLLER_H_
#define	TLC_CONTROLLER_H_

typedef uint16_t color_t;

template <unsigned int NUM>
class TLCController
{
	public:
		TLCController(BaseGPIOPin*, BaseGPIOPin*, BaseGPIOPin*, BaseGPIOPin*, BaseGPIOPin*, BaseGPIOPin*, BaseGPIOPin*);
		virtual ~TLCController() throw();

		virtual void setChannel(unsigned int channel, color_t value);
		virtual void setAll(color_t value);
		virtual void clear();

		virtual void update();

	protected:
		virtual void updateInit();
		virtual void updatePost();
		virtual PinValue getPinValueForChannel(unsigned int channel, unsigned int bit);
		
		BaseGPIOPin* sin_pin;
		BaseGPIOPin* sclk_pin;
		BaseGPIOPin* blank_pin;
		BaseGPIOPin* dcprg_pin;
		BaseGPIOPin* vprg_pin;
		BaseGPIOPin* xlat_pin;
		BaseGPIOPin* gsclk_pin;

		bool first_cycle;

		std::array<color_t, NUM*16> colors;		
};

template<unsigned int NUM>
TLCController<NUM>::TLCController(BaseGPIOPin* sin_pin, BaseGPIOPin* sclk_pin, BaseGPIOPin* blank_pin,
	BaseGPIOPin* dcprg_pin,	BaseGPIOPin* vprg_pin, BaseGPIOPin* xlat_pin, BaseGPIOPin* gsclk_pin) :
	sin_pin(sin_pin), sclk_pin(sclk_pin), blank_pin(blank_pin), dcprg_pin(dcprg_pin), vprg_pin(vprg_pin), 
	xlat_pin(xlat_pin), gsclk_pin(gsclk_pin)
{
	sin_pin->open();
	sin_pin->setLow();

	sclk_pin->open();
	sclk_pin->setLow();

	blank_pin->open();
	blank_pin->setHigh();

	dcprg_pin->open();
	dcprg_pin->setLow();

	vprg_pin->open();
	vprg_pin->setHigh();

	xlat_pin->open();
	xlat_pin->setLow();

	gsclk_pin->open();
	gsclk_pin->setLow();

	this->colors.fill(0);
	this->first_cycle = true;
}

template<unsigned int NUM>
void TLCController<NUM>::setChannel(unsigned int channel, color_t value)
{
	this->colors.at(channel) = value;
}

template<unsigned int NUM>
void TLCController<NUM>::setAll(color_t value)
{
	this->colors.fill(value);
}

template<unsigned int NUM>
void TLCController<NUM>::clear()
{
	this->colors.fill(0);
}

template<unsigned int NUM>
TLCController<NUM>::~TLCController() throw()
{
	sin_pin->close();
	sclk_pin->close();
	blank_pin->close();
	dcprg_pin->close();
	vprg_pin->close();
	xlat_pin->close();
	gsclk_pin->close();
}

template<unsigned int NUM>
void TLCController<NUM>::update()
{
	this->updateInit();
	
	// Start with the highest channel
	int channel_counter = (NUM * 16) - 1;
	int gsclk_counter = 0;
	bool pulse_gsclk = true;
	
	while(gsclk_counter < 4096)
	{
		if(channel_counter >= 0)
		{						
			// Send the first 12 bits of the color to the TLC, MSB first
			for(int i = 11; i >= 0; i--)
			{				
				PinValue value = this->getPinValueForChannel(channel_counter, i);

				sin_pin->setValue(value);				
				sclk_pin->pulse();
				
				gsclk_pin->pulse();
				gsclk_counter++;
			}

			channel_counter--;
		}
		else
		{
			sin_pin->setLow();			

			gsclk_pin->pulse();
			gsclk_counter++;
		}		
	}
	
	// If we reach here all color data has been sent to the TLC
	// And the full PWM cycle has been completed
	// Send a blank signal (so the internal GSCLK counter of the TLC is reset to zero)
	// and pulse the XLAT signal, so all data is latched in
	this->updatePost();
}

template<unsigned int NUM>
void TLCController<NUM>::updateInit()
{
	if(this->first_cycle)
	{
		vprg_pin->setLow();
	}
	
	blank_pin->setLow();
}

template<unsigned int NUM>
void TLCController<NUM>::updatePost()
{
	blank_pin->setHigh();
	xlat_pin->pulse();
	
	if(this->first_cycle)
	{
		sclk_pin->pulse();
		this->first_cycle = false;
	}
}

template<unsigned int NUM>
PinValue TLCController<NUM>::getPinValueForChannel(unsigned int channel, unsigned int bit)
{
	return static_cast<PinValue>((this->colors.at(channel) & (1 << bit)) >> bit);
}

typedef TLCController<1> SingleTLCController;

#endif	/* TLC_CONTROLLER_H */

