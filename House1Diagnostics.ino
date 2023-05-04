#include <Adafruit_INA219.h>
#include <Wire.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
//
Adafruit_INA219 ina219;


///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "";        // your network SSID (name)
char pass[] = "";    // your network password (use for WPA, or use as key for WEP)
int analogPin = A0; // Current sensor output


const int averageValue = 500;
long int sensorValue = 0;  // variable to store the sensor value read


float voltage = 0;
float current = 0;


WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);


const char broker[] = "";
int        port     = 1883;
const char topic[]  = "vmi/house1/current_mA";
const char topic2[]  = "vmi/house1/wattage_mW";
const char topic3[]  = "vmi/house1/voltage";
//set interval for sending messages (milliseconds)
const long interval = 1000;
unsigned long previousMillis = 0;


int count = 0;


void setup(void) {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Hello!");


  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }




  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }


  Serial.println("You're connected to the network");
  Serial.println();


  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);


  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());


    while (1);
  }


  Serial.println("You're connected to the MQTT broker!");
  Serial.println("Measuring voltage and current with INA219 ...");
  Serial.println();
}






void loop(void) {


  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;


  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
 




  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");




  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();


  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;


    mqttClient.beginMessage(topic);
    mqttClient.print(current);
    mqttClient.endMessage();
    delay(500);
    mqttClient.beginMessage(topic2);
    mqttClient.print(power_mW);
    mqttClient.endMessage();
    delay(500);
    mqttClient.beginMessage(topic3);
    mqttClient.print(busvoltage);
    mqttClient.endMessage();
    delay(500);
  }
  delay(1000);
}
