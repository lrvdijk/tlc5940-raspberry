#include <tlc5940-raspberry/tlc-controller.h>
#include <tlc5940-raspberry/raspberry-gpio.h>

#include <wiringPi.h>
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	// Initialize GPIO Pins
	if(wiringPiSetup() == -1)
	{
		throw std::runtime_error("Could not setup wiringPi, running as root?");
	}
	
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
	
	int counter = 0;
	while(true)
	{
		tlc_controller.setChannel(0, counter & 0x01 ? 0xFF : 0);
		tlc_controller.setChannel(1, counter & 0x02 ? 0xFF : 0);
		tlc_controller.setChannel(2, counter & 0x04 ? 0xFF : 0);

		counter++;

		std::chrono::milliseconds duration(5000);
		std::this_thread::sleep_for(duration);
	}
}

