# SmartGrid_IoT
CCI High School Internship @ VMI. Created to simulate smartgrid testbed for cybersecurity.
Models different generators and redistributing reduced voltage to "houses".

//Overall wiring of the project is in "OverallWiring.png"

Using NodeMCu ESP8266 boards, we set up a controllable (see RelayWiring.png) solar panel and water generator, read their voltage with a voltage sensor, and reduced it to 5V. We then, via a central power breadboard, redistributed the power to "houses", each with a controllable (see HouseRelayWiring.png) fan and light, and monitored their power usage with the INA219 module. All readings were then sent to a database through MQTT, which allowed the data to be stored and displayed on a webpage. MQTT is essentially a messaging system that allows data to be sent wirelessly, on different networks, without the need of port forwarding. It uses a "topic" system similar to a file system, that allows organization of values. The following shows the topics that we read and wrote on.

**READING VALUES**

House diagnostics:

vmi/house1/current_mA //sends current of first house
vmi/house1/wattage_mW //sends wattage of first house
vmi/house1/voltage //sends voltage of first house
vmi/house2/current_mA //sends current of second house
vmi/house2/wattage_mW //sends wattage of second house
vmi/house2/voltage //sends voltage of second house

Generator diagnostics:

vmi/solar/voltage
vmi/water/voltage


**PUBLISHING VALUES**

//The following use 0 for off, 1 for on

vmi/house1/light 
vmi/house1/fan
vmi/house2/light 
vmi/house2/fan

//To toggle the water generator send a 0 or 1, to toggle the solar generator use the same topic (vmi/water/toggle) but send a 2 for off and a 3 for on.

vmi/water/toggle

