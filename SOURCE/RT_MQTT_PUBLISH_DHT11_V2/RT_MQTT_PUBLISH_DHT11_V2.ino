/*
 Basic MQTT example

 This sketch demonstrates the basic capabilities of the library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

// Update these with values suitable for your network.

char ssid[] = "KCC-AP";     // your network SSID (name)
char pass[] = "22917532";  // your network password
int status  = WL_IDLE_STATUS;    // the Wifi radio's status

char mqttServer[]     = "iot.eclipse.org";
char clientId[]       = "AmebaClient199";
char publishTopic1[]   = "NCTU/USER99/Temp";
char publishTopic2[]   = "NCTU/USER99/Humi";
char publishPayload[] = "Hello World";
char subscribeTopic[] = "USER99/LED";
DHT dht(DHTPIN, DHTTYPE);
char publishstr1[] = "";
char publishstr2[] = "";
char message_buff[100];
int  mqttport = 1883;
long lastReconnectAttempt = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
   }
  Serial.println();
}

WiFiClient wifiClient;
PubSubClient client(wifiClient);

boolean reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientId)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
     // getDHT();
      client.publish(publishTopic1, publishstr1,true); //retained
      client.publish(publishTopic2, publishstr2,true);
      // ... and resubscribe
      client.subscribe(subscribeTopic,1);
      return client.connected();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(8000);
  }

  client.setServer(mqttServer, 1883);
  client.setClient(wifiClient);
  client.setCallback(callback);

 if (client.connect(clientId)) {
  // Allow the hardware to sort itself out
  delay(5000);
  }
}

void loop()
{
  getDHT();
  
 if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // MQTT Client connected
    //MQTT client loop processing
    client.loop();
  }
 
  delay(5000); // delay 1 minute for next measurement
}

void getDHT()
{
  delay(2000);
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 sprintf(publishstr1,"%3.0f",t);
 sprintf(publishstr2,"%3.0f",h);
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}

