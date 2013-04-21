TLC5940 Raspberry Pi Library
============================

This is a library which allows programs running in the userspace
to control the TLC5940 LED driver with a Raspberry Pi. The user
can specify the PWM value for each output channel of the TLC5940,
and it also supports multiple cascaded TLC5940's. 

The TLC5940
===========

The [TLC5940][tlc] is a versatile LED driver from Texas Instruments. It has
16 output channels, and they can be cascaded to easily support more
output channels. The TLC5940 has a 12 bit register for each output channel.
The value in each register determines the time a certain channel is enabled.
This allows pulse width modulation for all of the 16 channels.

To drive the outputs, the user of the chip should provide a clock signal on
the `GSCLK` pin of the TLC5940. On each pulse, an internal counter is incremented,
and the value in each register of the output channels is compared to the value
of the internal counter. If the value in the register is equal to the value of 
the counter, then the channel will be disabled for the rest of the cycle. If the 
counter reaches the maximum value of an unsigned 12 bit integer (4095), the
user needs to send a pulse on the `blank` pin to reset the counter. 

The important thing to note here, is that the TLC5940 constantly needs a clock
signal on `GSCLK`, without a signal, it won't update the output channels. A stable
and fast clock will result in a stable and clear PWM signal. This is a little 
inconvenient for us. Because most people have Linux on their Raspberry Pi, and
because Linux is a General Purpose operating system, providing a stable clock
from pure software is hard.

The program driving the TLC5940 is not the only process running on the Raspberry 
Pi. Each running program needs to share the ARM processor with the others. Because
of that, sometimes the execution of the program driving the TLC5940 gets paused,
to give an other process the processor. And with our process paused, the `GSCLK`
signal generation gets also paused, resulting is a less stable PWM signal.

This is a bit hard to fix, because you need to keep track of the pulse count,
to send a pulse to the `blank` pin on the right moment. Any suggestions for
solutions are always welcome.

Installation
============

Download the latest version on your Raspberry Pi, and extract its contents.
Navigate to the right folder, and execute the following commands:

    ./configure --prefix=/usr
    make
    sudo make install

It's better to install the library in /usr instead of the default /usr/local,
because by default `pkg-config` doesn't check the /usr/local folders for
package config files.

Library usage
=============

Because the TLC5940 constantly needs a stable clock, multithreading is a must 
in your program. You need one thread which determines which outputs
need what value, and stores that in a buffer. The other thread constantly
reads that buffer and sends the data to the TLC5940. Please view the provided
sample program for a simple example. Luckily, multithreading isn't that hard
anymore with C++11. For a simple introduction, check [this tutorial][tutorial].

Tutorial
--------

First you need to decide which pins you're going to use on the Raspberry Pi. 
Please take a look at the [wiringPi site][pinno] with all the pin numbers. To
control your TLC5940, you'll need 7 GPIO pins. If you're not going to use the 
"Dot Correction" feature of the TLC5940, you'll need 5. Dot correction is also 
not supported in this library for now, but it will probably in the future.
Below is the list of the pins on the TLC5940 which need to be controlled by the 
Raspberry Pi.

* SIN
* SCLK
* BLANK
* XLAT
* GSPRG
* DCPRG (connect to ground if not using Dot Correction)
* VPRG (connect to ground if not using Dot Correction)

You're free to choose any pin on the Raspberry Pi, but keep the [special pin functions][special]
in mind. Define the pins in your code using multiple instances of the class
`RaspberryGPIOPin`:

    RaspberryGPIOPin tlc_sin(1);
    RaspberryGPIOPin tlc_sclk(14);
    RaspberryGPIOPin tlc_blank(4);
    RaspberryGPIOPin tlc_dcprg(5);
    RaspberryGPIOPin tlc_vprg(6); 
    RaspberryGPIOPin tlc_xlat(10);
    RaspberryGPIOPin tlc_gsclk(11);
    
    tlc_sin.setOutput();
    tlc_sclk.setOutput();
    tlc_blank.setOutput();
    tlc_dcprg.setOutput();
    tlc_vprg.setOutput();
    tlc_xlat.setOutput();
    tlc_gsclk.setOutput();

The number given with the `RaspberryGPIOPin` constructor represents the **wiringPi
pin number**, not the BCM GPIO number. See the wiringPi site for the numbers.

Controlling the TLC5940 starts with an instance of the class TLCController. This
class needs a template parameter, containing the number of cascaded TLC5940 chips.
The class also needs to know which pins you're going to use, so the GPIO pin instances
created above are passed along.

    TLCController<2> tlc_controller(&tlc_sin, &tlc_sclk, &tlc_blank, &tlc_dcprg, &tlc_vprg, &tlc_xlat, &tlc_gsclk);

If you have just a single TLC5940, you can use the SingleTLCController class.

To enable an output, you use the `setChannel` method. `setall` sets the specified value
for all channels.

    tlc_controller.setChannel(0, 2048); // Set channel 0 to half of the brightness
    tlc_controller.setChannel(1, 4095); // Set channel 1 to full brightness

Using the `update` method, the data is sent to the TLC5940. Remember, this function
needs to be called continuously, even if you don't changed any output values.

    tlc_controller.update();

Linking
-------

This library provides a `pkg-config` configuration file, so you can use pkg-config
to retrieve the required compiler and linker flags. 

    CFLAGS += `pkg-config --cflags tlc5940-raspberry-1.0`
    LDFLAGS += `pkg-config --libs tlc5940-raspberry-1.0`

And if you use autotools as build system you can use the `PKG_CHECK_MODULES` macro,
see [this][autoconf] site for more info.

[tlc]: http://ti.com/product/tlc5940
[tutorial]: http://return1.net/blog/2012/May/3/introduction-to-threads-with-c11
[pinno]: https://projects.drogon.net/raspberry-pi/wiringpi/pins/
[special]: https://projects.drogon.net/raspberry-pi/wiringpi/special-pin-functions/
[autoconf]: http://www.flameeyes.eu/autotools-mythbuster/pkgconfig/pkg_check_modules.html
