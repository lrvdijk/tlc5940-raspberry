/**
 * Helios 3D LED Cube Client
 * -------------------------
 *
 * This program should run on the embedded processor of the LED Cube, which
 * controls the LED's.
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

#include "tlc-controller.cpp"

typedef TLCController<1> SingleTLCController;

#endif	/* TLC_CONTROLLER_H */

