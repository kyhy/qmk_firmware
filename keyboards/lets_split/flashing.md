# Flashing a Pro Micro

## OSX, Linux

### Build Keymap (QMK)

From the [lets_split directory](https://github.com/qmk/qmk_firmware/tree/master/keyboards/lets_split):

```
make rev2-YOUR_KEYMAP_NAME-build
```

Don't forget to replace `YOUR_KEYMAP_NAME` with the actual name of your keymap.

You'll now have a .hex file that we can use to flash.

### Enter Bootloader

Connect RST and GND. If you're using an official Sparkfun Pro Micro (the red one) you need to short this twice quickly.

You will only have about 8 seconds to find the serial port and run the flash command before it continues on to the sketch.

> Tip: If this is the first time the Pro Micro has been flashed it should go directly to the bootloader on start.

### Find Your Serial Port

Unfortunately, this serial port is not plug-n-play so the kernel does not know which device was plugged in. We'll have to find it manually.

Before resetting look at the existing serial ports:

```
ls /dev/tty* | grep usb
```

Then reset and run the command again. You should see a new one show up. That's the serial port you'll need to specify when running `avrdude`, but there's a catch: this port may change on every reset so you'll have to go real quick (see **Easier, Alternative Flashing** for a way around this).

### Flash Using `avrdude`

Install `avrdude` if you haven't already: `brew install avrdude`.

Set your serial port and run `avrdude` to flash the Pro Micro. You may need to adjust the build path.

```
avrdude \
-p atmega32u4 \
-c avr109 \
-P YOUR_SERIAL_PORT \
-U flash:w:./build/lets_split_rev2_YOUR_KEYMAP_NAME.hex
```

### Easier, Alternative Flashing

You might have heard of this little thing called "computers". They're good at doing things that humans aren't. We can eliminate the race to find the serial port using a little bash.

Save this as `flash.sh` then `chmod +x flash.sh`:

```bash
#!/bin/bash

# Usage
# ./flash.sh path/to/your.hex

TARGET=$1

ls /dev/tty* > /tmp/1

echo "Reset your Pro Micro now"

while [[ -z $USB ]]; do
  sleep 1
  ls /dev/tty* > /tmp/2
  USB=`diff /tmp/1 /tmp/2 | grep -o '/dev/tty.*'`
done

avrdude -p atmega32u4 -c avr109 -P $USB -U flash:w:$TARGET
```

Let's run it (from the lets_split directory):

```bash
$ ./flash.sh ../../.build/lets_split_rev2_YOUR_KEYMAP_NAME.hex
Reset your Pro Micro now

Connecting to programmer: .
Found programmer: Id = "CATERIN"; type = S
    Software Version = 1.0; No Hardware Version given.
Programmer supports auto addr increment.
Programmer supports buffered memory access with buffersize=128 bytes.

[snip]

avrdude: verifying ...
avrdude: 22286 bytes of flash verified

avrdude: safemode: Fuses OK (E:CB, H:D8, L:FF)

avrdude done.  Thank you.
```

## Common Issues

### Programmer not responding

The controller isn't in bootloader mode. You may have missed the 8 second window to flash.

### Can't open device

The serial port you specified isn't the one the controller is using. 