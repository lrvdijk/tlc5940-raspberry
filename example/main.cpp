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

