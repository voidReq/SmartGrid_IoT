//See house 1 diagnostics, INA219 Diagram, and house 2 diagnostics

These scripts were uploaded to a NodeMCU, which was wired to an INA 219, which eventually led to the relays powering the loads (a light and fan)
They measure current, wattage, and voltage, and send them through their respective topics. The wiring diagram can be seen in INA219 Diagram.png, but it simply 
takes two analog pins to the NodeMCU, and pushes power from the central power board to the load, while having a common ground with the NodeMCU. The INA219 modules
does not reduce power in any way, simply pushing it through while taking readings and sending those readings to the NodeMCU, which publishes them to MQTT, where 
the readings are read, stored in a database, and published on the website.
