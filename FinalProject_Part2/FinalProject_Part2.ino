//Serly Teymoorian 
//Final Project - Part 2 
// Blinking LEDs shaped in "COOL" word format 

#define LED_BUILTIN 2
#define LED_BUILTIN_TWO 4

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "MyCharterWiFifd-2G"; // Enter your WiFi name
const char *password = "rusticmango074";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "192.168.1.2";
const char *topic = "esp32/test1";
const char *topic2 = "pub/message";
const char *mqtt_username = "emqx";
const char *mqtt_password = "Vellavaroosh2000*";
const int mqtt_port = 1883;
bool x = false; 
int stateTest = 0; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup() 
{
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(4, OUTPUT);
   // Set software serial baud to 115200;
   Serial.begin(115200);
   // connecting to a WiFi network
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
       delay(500);
       Serial.println("Connecting to WiFi..");
   }
   Serial.println("Connected to the WiFi network\n\n");
   
   //connecting to a mqtt broker
   client.setServer(mqtt_broker, mqtt_port);
   client.setCallback(callback);
   
   while (!client.connected()) 
   {
       String client_id = "esp32-client-";
       client_id += String(WiFi.macAddress());
       Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
       
       if (client.connect(client_id.c_str())) 
       {
           Serial.println("Public emqx mqtt broker connected");
           stateTest = true; 
       } 
       else 
       {
           Serial.print("failed with state ");
           Serial.print(client.state());
           delay(2000);
       }
   }
  

 // publish and subscribe
   client.publish(topic, "Part2_Blinking_COOL");
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
       if((char) payload[i] == '1' || (char) payload[i] == '2' || (char) payload[i] == '3')
       {
        rx_byte = (char) payload[i];  
        if(rx_byte == '1')
        {
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(100); 
          Serial.print("LED Greenis ON\n"); 
          x = 1; 
        }
        else if(rx_byte == '2')
        {
          digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
          delay(100);  
          digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(100);  
          Serial.print("RED on Green off\n");
          x = 2; 
       }
       else if(rx_byte == '3')
       {
          digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
          delay(100); 
          digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
          delay(100); 
          Serial.print("Both are off\n"); 
       }
       else if(rx_byte == '4')
       {
         digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
         delay(5);
         digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
         delay(10); 
       }
     }
   }
 
   Serial.println();
   Serial.println("-----------------------"); 
}

void loop() 
{ 
  client.loop();
  if(x == 1)
  {
    client.publish(topic2, "Last Lights on were GREEN");
  }
  else if(x == 2)
  {
    client.publish(topic2, "Last Lights on were RED");
  }

}
