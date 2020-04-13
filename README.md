# uLCD-clib-for-Pi
This is a project that port the uLCD C++ library from mbed to Raspberry Pi (Raspian).

Created by:
<br>Andrew (Andy) Vernetti
<br>Xingyang (Xandy) Liu

Created for:
Georgia Tech ECE4180-A Embedded Systems Design - Final Project

## The Raspberry Pi UARTs (https://www.raspberrypi.org/documentation/configuration/uart.md)

By default, on Raspberry Pis equipped with the wireless/Bluetooth module (Raspberry Pi 3 and Raspberry Pi Zero W), the PL011 UART is connected to the Bluetooth module, while the mini UART is used as the primary UART and will have a Linux console on it. On all other models, the PL011 is used as the primary UART.

In Linux device terms, by default, /dev/ttyS0 refers to the mini UART, and /dev/ttyAMA0 refers to the PL011. The primary UART is the one assigned to the Linux console, which depends on the Raspberry Pi model as described above. There are also symlinks: /dev/serial0, which always refers to the primary UART (if enabled), and /dev/serial1, which similarly always refers to the secondary UART (if enabled).

By default, the UART transmit and receive pins are on GPIO 14 and GPIO 15 respectively, which are pins 8 and 10 on the GPIO header.

Various UART Device Tree Overlay definitions can be found in the kernel github tree. The two most useful overlays are disable-bt and miniuart-bt.

disable-bt disables the Bluetooth device and restores UART0/ttyAMA0 to GPIOs 14 and 15. It is also necessary to disable the system service that initialises the modem so it doesn't use the UART: sudo systemctl disable hciuart.

## PIGPIO Serial Interface (http://abyz.me.uk/rpi/pigpio/cif.html#serOpen)
mbed uLCD_4DGL library      ->      PIGPIO c library
_rst = 1;                   ->      gpioWrite(_rst, 1); 
_cmd.putc(c);               ->      serWriteByte(_cmd, (unsigned) c);
_cmd.getc();                ->      int = serReadByte(_cmd);
wait_ms(5);                 ->      time_sleep(0.005);
wait(3);                    ->      time_sleep(3);
wait_us(500);               ->      time_sleep(0.0005);
_cmd.readable()             ->      serDataAvailable(_cmd) != 0
