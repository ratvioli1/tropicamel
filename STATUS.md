# Status

I have my screen working in a nice state. My screen has its own ESP32-S3 to do the actual display stuff and my board can interact with it over USB serial.

`screen/crowpanel/read-serial`: Screen demo that reads strings sent through serial and prints them to the screen. It works with strings sent from both my desktop and my dev board.

`screen/crowpanel/touchscreen`: Screen demo that reads the touch controller and prints the X and Y coordinates of where you touch the screen.

I also started typing out code for the game itself, though it doesn't do anything except loop right now. I also spent some time to clean up the repo structure.

My desk was extremely messy when I took photos and I refuse to poison the water by uploading them here. If you want proof of the screen or anything working then ask me and I can provide images or show you.

## Ownership

Oz64: The main core owns the game loop and the tiny core will own everything interfacing with GPIO pins. Main core code is in `game/` and builds to an executable.

The CrowPanel's ESP32-S3: Owns the interface it displays, and the Oz64 main core will send the game state to it. I don't have anything planned where the touchscreen can update the game itself, but it is possible. Screen code goes in `screen/crowpanel/`.

Turn button: Connected to an ESP32-C3 and will connect to the board over WiFi. If I can't broadcast a network on the Oz64, somehow get BLE working.

## Code

My screen demos are in `screen/crowpanel/`. I'm using PlatformIO, which plays nicer with VSCode compared to any sort of Arduino IDE integration.

For my own reference, in a folder with `platformio.ini`, these commands are useful:

```
pio run                 # build
pio run -t upload       # build and flash, can also specify port like --upload-port /dev/ttyUSB0
pio device monitor      # open the serial monitor
pio run -t clean        # remove build outputs
```

## Controlling the screen through USB

The Oz64 has a USB-A host port and the CrowPanel has a USB-C port.

My dev board can supply power over its USB port, and that's controlled by GPIO `XGPIOB[5]`. The original image sets its function to GPIO, but nothing was turning it on. Manually setting it high made my powered USB hub and CrowPanel show up.

```
> cat /proc/cviusb/otg_role
    host

> lsusb
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

# GPIO bank B starts at GPIO number 448, B5 = 453.
# run these as root or sudo them
> cat /sys/class/gpio/gpiochip448/label
> cat /sys/class/gpio/gpiochip448/base
    3021000.gpio
    448

> echo 453 > /sys/class/gpio/export
> echo high > /sys/class/gpio/gpio453/direction

> cat /sys/kernel/debug/gpio
    gpio-453 (                    |sysfs               ) out hi
    gpio-454 (                    |cviusb-otg          ) in  hi IRQ

> lsusb
> ls -l /dev/ttyUSB0
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    Bus 001 Device 002: ID 05e3:0610 Genesys Logic, Inc. Hub
    Bus 001 Device 003: ID 0b95:1790 ASIX Electronics Corp. AX88179 Gigabit Ethernet
    Bus 001 Device 004: ID 1a86:7523 QinHeng Electronics CH340 serial converter
    crw-rw---- 1 root dialout 188, 0 Nov  6 15:21 /dev/ttyUSB0
```

Flashing the CrowPanel:

```
> ls -l /dev/serial/by-id/
lrwxrwxrwx 1 root root 13 Nov  6 18:34 usb-1a86_USB_Serial-if00-port0 -> ../../ttyUSB0

# I didn't originally have permissions and had to run
> sudo chmod a+rw /dev/ttyUSB0

> pio run -t upload --upload-port /dev/ttyUSB0
```

Reading serial from it:

```
pio device monitor -p /dev/ttyUSB0 -b 115200
```
