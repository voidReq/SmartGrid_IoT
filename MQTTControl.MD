//See House1MQTTControl, House2MQTTControl, GenControl, Relay Wiring.png
These scripts open an MQTT connection, on their respective topics that they listen to. Upon recieving "0", "1", "2", or "3", the NodeMCU's digitalWrite to a relay and enable/disable a fan or a light.

All of the code we used for this (House1MQTTControl, House2MQTTControl, GenControl) is basically the same code but the MQTT topics were changed to send data to
different parts of the software teams website.

The code starts by defining the SSID and password of the wifi network you are using, then it connects to the mqtt broker you connected(for this project we used 
broker.emqx.io, and of course port 1883) then it has a function that handles connecting and reconecting to wifi. Then it listens to a topic for signals to turn
on and off the devices that are connected to it.
