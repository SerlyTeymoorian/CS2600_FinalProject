// Serly Teymoorian 
// Final Project - Part 1 
// Press 1 -> turn the LED on 
// Press 2 -> turn the LED off

#define LED_BUILTIN 2
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "MyCharterWiFifd-2G"; // Enter your WiFi name
const char *password = "rusticmango074";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "db90e0f1-internet-facing-dfb836982de732d6.elb.us-east-1.amazonaws.com";
const char *topic = "esp32/test";
const char *mqtt_username = "Serly_test";
const char *mqtt_password = "Vellavaroosh2000*";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) 
 {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
  
 while (!client.connected()) 
 {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) 
     {
         Serial.println("Public emqx mqtt broker connected");
     } 
     else 
     {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 
 // publish and subscribe
 client.publish(topic, "Part1_Turn LED ON and OFF");
 client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) 
{
   char rx_byte;
   Serial.print("Message arrived from topic: ");
   Serial.println(topic);
   Serial.print("Message:");
   
   for (int i = 0; i < length; i++) 
   {
      // Serial.print((char) payload[i]);
       if((char) payload[i] == '1' || (char) payload[i] == '2' )
       {
        rx_byte = (char) payload[i];  
        if(rx_byte == '1')
        {
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(1000); 
          Serial.print("LED is ON\n");   
        }
        else if(rx_byte == '2')
        {
          digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
          delay(1000);  
          Serial.print("LED is OFF\n");   
       }
     }
   }
   Serial.println();
   Serial.println("-----------------------");
}

void loop() 
{
  client.loop();
}
