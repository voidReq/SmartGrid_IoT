#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define ANALOG_IN_PIN A0
 
// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;
 
// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0; 


 
// Float for Reference Voltage
float ref_voltage = 5.0;
 
// Integer for ADC value
int adc_value = 0;

// Update these with values suitable for your network.


const char* ssid = "YourWiFi";
const char* password = "PutPSWD";
const char* mqtt_server = "ServerIP";


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
float value = 0;


void setup_wifi() {


 delay(10);
 // We start by connecting to a WiFi network
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);


 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);


 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }


 randomSeed(micros());


 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}






void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
   Serial.print("Attempting MQTT connection...");
   // Create a random client ID
   String clientId = "ESP8266Client-";
   clientId += String(random(0xffff), HEX);
   // Attempt to connect
   if (client.connect(clientId.c_str())) {
     Serial.println("connected");
     client.publish("vmi/hsi/testserver", "MQTT Server is Connected");
   } else {
     Serial.print("failed, rc=");
     Serial.print(client.state());
     Serial.println(" try again in 5 seconds");
     delay(5000);
   }
 }
}


void setup() {    // Initialize the BUILTIN_LED pin as an output
 Serial.begin(9600);
 setup_wifi();
 client.setServer(mqtt_server, 1883);

}


void loop() {


 if (!client.connected()) {
   reconnect();
 }
 client.loop();


 unsigned long now = millis();
 if (now - lastMsg > 2000) {
      // Read the Analog Input
   adc_value = analogRead(ANALOG_IN_PIN);

   // Determine voltage at ADC input
   adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
   
   // Calculate voltage at divider input
   in_voltage = adc_voltage / (R2/(R1+R2)) ;

float in_voltage = adc_voltage / 0.32;
   // Print results to Serial Monitor to 2 decimal places
Serial.println(in_voltage, 2);   

  lastMsg = now;
  char bufferTwo[30];
  char* value = dtostrf(in_voltage, 5, 2, bufferTwo);
  snprintf(msg, MSG_BUFFER_SIZE, value);
   Serial.print("Publish message: ");
   Serial.println(msg);
   client.publish("vmi/water/voltage", msg);


 }
 delay(2000);
}