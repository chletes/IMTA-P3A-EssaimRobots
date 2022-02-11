# Original Marvelmind's API example

This API version is downloaded from Marvelmind's official site web. 

## Building the API

To build the original API, first thing to do is copy the corresponding Dynamic-Link Library (DLL) file for your Windows machine (32 or 64 bits) or the corresponding shared library (`.so`) file for your Linux machine (32 or 64 bits) in `/ressources/marvelmind_SW_2021_09_29/API/example_source` and then execute `make` on a terminal.

## Using the API

Execute `./mm_api_example`. 

The program will open the port and try to connect to modem. This is the standard (no errors) output:

```
Waiting for port...
Trying connect to device...
Device is connected via USB.
Version: 7.000.24   CPU ID=13243f
Device is modem 
Device 5 updated
Device 5 is sleeping
Device added: 5
```

The program will output the different active beacons: 
```
Device 22 updated
Version: 7.000.30   CPU ID=133329
Device is beacon 
Device added: 22
...
```
From this point, the program will output: 
1. Stationary beacons position,
2. Raw distances between the hedgehog(s) and the stationary beacons (in loop), and
3. Hedgehog(s) position (in loop).

This is an example: 

```
Raw distance: 72 ==> 22  : 2,651 
Raw distance: 72 ==> 25  : 3,420 
Hedge  72 location: X=2,035, Y=1,718, Z=0,000, no angle, quality= 87 %
Beacon 22 location: X=0,010, Y=0,010, Z=0,000 
Beacon 25 location: X=1,012, Y=-1,545, Z=0,000 
Hedge  72 location: X=2,035, Y=1,717, Z=0,000, no angle, quality= 89 %
```

To interact with the program, press the space bar and enter your desired command, as in this example[^1]: 

```
Raw distance: 72 ==> 22  : 2,652 
Raw distance: 72 ==> 25  : 3,425 
 Enter command: cmd 72 6 1 1 1
Command sent
Raw distance: 72 ==> 22  : 2,654
```

The next screenshot shows the received packet: 

![](/assets/img/api_command_example/arduino_ide_serial_monitor.png)


[^1]: The command 'cmd' is not implemented in original's MarvelMind's API. We implemented `marvelmindCheckSetRobotCommand()` and `mmSetRobotCommand()` to be able to send a `0x201` packet, because we have just implemented the reception of those packets in the Arduino. 