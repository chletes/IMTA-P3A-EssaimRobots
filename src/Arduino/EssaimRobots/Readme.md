## How communication between Marvelmind Hedgehog and Pololu Zumo works (to be written)

![your-UML-diagram-name](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/chletes/IMTA-PS5-EssaimRobots/main/src/Arduino/EssaimRobots/sequence_diagram.iuml)

## How to test with Marvelmind's Dashboard

0. We assume there's already a setup built (beacons installed and charged, hedgehog and Arduino Mega connexions done, modem connected, etc). 
1. Open Marvlemind's Dashboard and localize desired hedgehog in the lower pannel. Right-click and select "Set up mouvement path" and a new windows arises. 

![](/img/setup_mouvement_path.png)

2. Define desired path by shift-clicking on the map. Coordinates will appear in the new window. At that point, you can edit those coordinates but format should be maintained (`Wvv(xxx,yyy,zzz)` where `vv` should start on 1 and increment by 1 each time and `xxx`, `yyy` and `zzz` represent coordinates).
3. Click on "Write path" on the new window. 

![](/img/define_path.png)

4. You can check the reception of the data by opening the serial monitor window on Arduino IDE. 

![](/img/arduino_ide.png)
