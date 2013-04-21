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

#include <tlc5940-raspberry/tlc-controller.h>
#include <tlc5940-raspberry/raspberry-gpio.h>

#include <wiringPi.h>
#include <iostream>
#include <thread>
#include <chrono>

uint16_t bitpattern;

void update_thread()
{
	RaspberryGPIOPin tlc_sin(1);
	RaspberryGPIOPin tlc_sclk(14);
	RaspberryGPIOPin tlc_blank(4);
	RaspberryGPIOPin tlc_dcprg(5);
	RaspberryGPIOPin tlc_vprg(6); // Not used in this example
	RaspberryGPIOPin tlc_xlat(10);
	RaspberryGPIOPin tlc_gsclk(11);
	
	tlc_sin.setOutput();
	tlc_sclk.setOutput();
	tlc_blank.setOutput();
	tlc_dcprg.setOutput();
	tlc_vprg.setOutput();
	tlc_xlat.setOutput();
	tlc_gsclk.setOutput();
	
	SingleTLCController tlc_controller(&tlc_sin, &tlc_sclk, &tlc_blank, &tlc_dcprg, &tlc_vprg, &tlc_xlat, &tlc_gsclk);

	while(true)
	{
		// This thread only reads the bit pattern so no lock is required
		for(int i = 0; i < 16; i++)
		{
			tlc_controller.setChannel(i, (bitpattern & (1 << i)) ? 0xFF : 0);
		}

		tlc_controller.update();
	}
}

void pattern_thread()
{
	bool reverse = false;
	bitpattern = 1;
	while(true)
	{
		if(!reverse)
		{
			bitpattern << 1;
		}
		else
		{
			bitpattern >> 1;
		}

		if(bitpattern == 1)
		{
			reverse = false;
		}
		else if((bitpattern & (1 << 15)) != 0)
		{
			reverse = true;
		}

		std::chrono::milliseconds duration(1500);
		std::this_thread::sleep_for(duration);
	}
}

int main()
{
	// Initialize GPIO Pins
	if(wiringPiSetup() == -1)
	{
		throw std::runtime_error("Could not setup wiringPi, running as root?");
	}

	bitpattern = 0;
	
	std::thread thread1(update_thread);
	std::thread thread2(pattern_thread);

	thread1.join();
	thread2.join();
}

