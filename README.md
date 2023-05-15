# SmartGrid_IoT
CCI High School Internship @ VMI. Created to simulate smartgrid testbed for cybersecurity.
Models different generators and redistributing reduced voltage to "houses".

//Overall wiring of the project is in "OverallWiring.png"

/*

MQTT is essentially a messaging system that allows data to be sent wirelessly, on different networks, without the need of port forwarding. It uses a "topic" system similar to a file system, that allows organization of values. 

*/

We wired a water generator and a solar panel to a battery, with relays (see RelayWiring.png) connected to MQTT servers (via a NodeMCUesp8266) in the connections allowing us to turn on and off the stream of power. We then used two power regulators to reduce the 12V coming from the battery into a manageable 5V, while keeping up the amperage. In the connections were also voltage readers (SolarPanelVoltageSensor.ino, voltagedetection.md), that sent their readings to mqtt servers "vmi/solar/voltage" and "vmi/water/voltage".

The battery (with a reduced 5V) was then wired to a central power board, where house loads grabbed their power from. Each house had a fan and a light, each individually controllable via a relay (HouseRelayWiring.png). The relays were connected to separate NodeMcu's, which allowed them to be controlled via MQTT. We then used the INA219 module (INA219 diagram.png) to read the power consumption of the houses, and send it over MQTT (HouseXDiagnostics.ino). 


The following shows the topics that we read and wrote on.



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

