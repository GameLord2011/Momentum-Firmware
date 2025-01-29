# This is a custom flipper zero firmware buitl off of Next-Flip/Momentum-Firmware

----

## Build it yourself

```bash
To download the repository:
$ git clone --recursive --jobs 8 https://github.com/GameLord2011/Momentum-Firmware.git
$ cd Momentum-Improved/

To flash directly to the Flipper (Needs to be connected via USB, qFlipper closed)
$ ./fbt flash_usb_full

To compile a TGZ package
$ ./fbt updater_package

To build and launch a single app:
$ ./fbt launch APPSRC=your_appid
```

