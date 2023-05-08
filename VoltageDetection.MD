these intructions apply for HydroPlantVoltagrDetector.ino and SolarPanelVoltageSensor.ino

the code is mostly the same from the MQTTControl scripts except inestead of the script listening for instructions to control loads, it sends data to the website.
Data is sent with the Publish command instead of the subscribe command. (Note: the publish command cannot publish floats so you need to convert floats into strings and
then publish them.)
