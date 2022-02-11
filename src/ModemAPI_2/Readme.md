# Modem API 

This API is sourced from the original Marvelmind's API example (which can be found downloading the software pack - SW). There is a copy of Marvelmind's original API version in this path: `/ressources/marvelmind_SW_2021_09_29/API`). Refer to [this document](/ressources/marvelmind_SW_2021_09_29/API/readme.md) to build that API. 

## Building the API

For our API, the DLL and `.so` files for a Windows 64-bit and a Linux 64-bit machine respectively are already copied in this folder. 

To build the API just execute `make` in a terminal. 

## Using the API

The current version of the API works the same way the original does. The only difference is sending a command is implemented: 

```
Raw distance: 72 ==> 22  : 2,652 
Raw distance: 72 ==> 25  : 3,425 
 Enter command: command 72 6 1 1 1
Command sent
Raw distance: 72 ==> 22  : 2,654
```

The next screenshot shows the received packet: 

![](/assets/img/api_command_example/arduino_ide_serial_monitor.png)