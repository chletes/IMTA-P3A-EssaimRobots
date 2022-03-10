# IMTA-P3A-EssaimRobots
IMT Atlantique 3rd year project - Localization system for a swarm of mobile robots

## Repository arborescence

```
│
└─── src
│	│
│	└─── Arduino 
│	│	│
│	│   └── Hedgehog_Zumo32U4_TXonly/
│	│   └── Hedgehog_MEGA_TXonly/
│	│   └── EssaimRobots/
│	│
│	└─── ModemAPI_v1/
│	└─── ModemAPI_v2/
│
└─── ressources
│	│
│	└─── marvelmind_interfaces_10_02_2022.pdf
│	│
│	└─── marvelmind_SW_2021_09_29
│		│
│		└── ModemAPI_v1/
│		└── ModemAPI_v2/ 
│
└─── assets
│	│
│	└─── img/
│	└─── diagrams/
│
└─── doc

```

- `src` : Folder containing our code
	- `Arduino` : Folder containing Arduino // C++ code 
		- `Hedgehog_MEGA_TXonly` : Unit Test - UART reception on Arduino MEGA 2560 from Marvelmind Hedgehog
		- `Hedgehog_Zumo32U4_TXonly` : Unit Test - UART reception on Pololu Zumo 32U4 from Marvelmind Hedgehog
		- `EssaimRobots` : Main program
	- `ModemAPI` : Folder containing the API implementation 
		- `ModemAPI_v1` : :warning: deprecated API
		- `ModemAPI_v2` : newer API that uses a library
- `ressources` : Folder containing some ressources used in our implementation
	- `marvelmind_interfaces_10_02_2022.pdf` : Main guide in the communication chain
	- `marvelmind_SW_2021_09_29` : Original APIs (from MarvelMind's official site)
- `assets` : Folder containing images and diagrams used in readmes. 
- `doc` : Folder containing LaTeX files used to write project reports. It is synchronized with Overleaf in order to edit and compile the pdf file. See readme in folder to export diagrams. 

## Communication chain 

In order to send instructions to the robots evolving in a swarm, we use the communication chain depicted in the following figure. 

![Alt text](assets/img/schema_communications.png)

- Communication between the Hedgehog and the Pololu robot is assured by the UART protocol. Only reception of and response to requests from the point of view of the Pololu robot was implemented, following [this guide](/ressources/marvelmind_interfaces_10_02_2022.pdf).
- Communication between the Modem and the Hedgehog is assured by Marvelmind's propietary communication protocol, via radio.
- Communication between the Central System (Core) and the Modem was implemented by us (`ModemAPI` folder), following [this guide](ressources/marvelmind_interfaces_10_02_2022.pdf).
