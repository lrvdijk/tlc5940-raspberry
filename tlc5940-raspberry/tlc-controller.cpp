/**
 * Helios 3D LED Cube Client
 * -------------------------
 *
 * This program should run on the embedded processor of the LED Cube, which
 * controls the LED's.
 */

#include <array>

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
	
	int channel_counter = 0;
	int gsclk_counter = 0;
	bool pulse_gsclk = true;
	
	while(gsclk_counter < 4096)
	{
		if(channel_counter < NUM * 16)
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

			channel_counter++;
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

