# IMTA-PS5-EssaimRobots
IMT Atlantique 3rd year project - Localization system for a swarm of mobile robots

## Repository arborescence

```
│
└─── Arduino 
│   │__ Hedgehog_Zumo32U4_TXonly
│   │__ Hedgehog_MEGA_TXonly
│   │__ EssaimRobots
│
└─── ModemAPI
```

* `Arduino` : Arduino // C++ code 
	- `Hedgehog_MEGA_TXonly` : Unit Test - UART reception on Arduino MEGA 2560 from Marvelmind Hedgehog
	- `Hedgehog_Zumo32U4_TXonly` : Unit Test - UART reception on Pololu Zumo 32U4 from Marvelmind Hedgehog
	- `EssaimRobots` : 
* `ModemAPI` : API implementation 

## Communication chain 

In order to send instructions to the robots evolving in a swarm, we use the communication chain depicted in the following figure. 
![Alt text](img/schema_communications)

- Communication between the Hedgehog and the Pololu robot is assured by the UART protocol. Only reception of and response to requests from the point of view of the Pololu robot was implemented. 
- Communication between the Modem and the Hedgehog is assured by Marvelmind's propietary communication protocol, via radio.
- Communication between the Central System (Core) and the Modem was implemented by us (`ModemAPI` folder). 

## References

The implementation of the communication was done following [this guide](https://marvelmind.com/pics/marvelmind_interfaces.pdf).