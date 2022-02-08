## How communication between Marvelmind Hedgehog and Pololu Zumo works

### Marvel protocol for streaming
![dashboard_command_example](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/chletes/IMTA-PS5-EssaimRobots/main/assets/diagrams/dashboard_command_example.iuml)

All the streaming packets have the same general structure and are transmitted every time new coordinates are measured (that's why the name 'stream'). The diagram above shows the exchange. 

Let's take for example the packet with cm resolution coordinates. This packet is sent from the Hedgehog to the Zumo robot. 

| Offset | Size (bytes) | Description | Value |
|:-:|:-:|:-:|:-:|
| 0 | 1 | Modem adress | `0xff` |
| 1 | 1 | Packet type | `0x47` |
| 2 | 2 | Packet ID (code) | `0x0001` |
| 4 | 1 | Data size  | `0x10` |
| 5 | 4 | Timestamp | - |
| 9 | 2 | X coordinate (in cm)  | - |
| 11 | 2 | Y coordinate (in cm)  | - |
| 13 | 2 | Z coordinate (in cm) | - |
| 15 | 1 | Flags  | Bit 0:1 - Coordinates unavailable (rest not used)|
| 16 | 1 | Hedgehog adress | - |
| 17 | 2 | Paired heading  | - |
| 19 | 2 | Time passed (not used) | - |
| 21 | 2 | Checksum  | - |

After this packet, a reply should be sent from the Zumo robot indicating that he's ready to receive a "write" packet.

| Offset | Size (bytes) | Description | Value |
|:-:|:-:|:-:|:-:|
| 0 | 1 | Hedgehog adress | (obtained from frame before) |
| 1 | 1 | Packet type | `0x48` (although the protocol says 0x49) |
| 2 | 2 | Packet ID (code) | `0x0100` |
| 4 | 1 | Data size  | `0x04` |
| 5 | 2 | Checksum  | - |

After this, the next packet is sent from the Modem (via Hedgehog) to the Zumo robot with the data itself (commands). The next example frame is the request of writing the movement path (packet ID (code) equals 0x0201), but other frames can be made using packet IDs going from 0x0203 to 0x02ff. 

| Offset | Size (bytes) | Description | Value |
|:-:|:-:|:-:|:-:|
| 0 | 1 | Modem adress | `0xff` |
| 1 | 1 | Packet type | `0x4a` |
| 2 | 2 | Packet ID (code) | `0x0201` |
| 4 | 1 | Data size  | `0x0c` |
| 5 | 12 (0x0c) | Payload data | - |
| 17 | 2 | Checksum  | - |

And to finish with the exchange, the Zumo robot acknowledges the "write" packet. If the Zumo robot successfully processed the request, it should send a response in the following format:

| Offset | Size (bytes) | Description | Value |
|:-:|:-:|:-:|:-:|
| 0 | 1 | Hedgehog adress | (obtained from the first frame) |
| 1 | 1 | Packet type | `0x4a` |
| 2 | 2 | Packet ID (code) | `0x0201` |
| 4 | 2 | Checksum  | - |

If the Zumo robot failed to process the request, it sends a response in the following format (to be implemented): 

| Offset | Size (bytes) | Description | Value |
|:-:|:-:|:-:|:-:|
| 0 | 1 | Hedgehog adress | (obtained from the first frame) |
| 1 | 1 | Packet type | `0xca` |
| 2 | 2 | Packet ID (code) | `0x0201` |
| 4 | 1 | Error code | `1` for unknown packet type, `2` for unknown packet ID, `3` for incorrect payload data and `6` for device is busy and cannot retrieve the requested data now |
| 5 | 2 | Checksum  | - |

## How to test sending command with Marvelmind's Dashboard

0. We assume there's already a setup built (beacons installed and charged, hedgehog and Arduino Mega connexions done, modem connected, etc). 
1. Open Marvlemind's Dashboard and localize desired hedgehog in the lower pannel. Right-click and select "Set up mouvement path" and a new windows arises. 

![setup_mouvement_path](/assets/img/dashboard_command_example/setup_mouvement_path.png)

2. Define desired path by shift-clicking on the map. Coordinates will appear in the new window. At that point, you can edit those coordinates but format should be maintained (`Wvv(xxx,yyy,zzz)` where `vv` should start on 1 and increment by 1 each time and `xxx`, `yyy` and `zzz` represent coordinates).
3. Click on "Write path" on the new window. 

![define_path](/assets/img/dashboard_command_example/define_path.png)

4. You can check the reception of the data by opening the serial monitor window on Arduino IDE. 

![arduino_ide_serial_monitor](/assets/img/dashboard_command_example/arduino_ide_serial_monitor.png)
