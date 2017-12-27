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

// Update these with values suitable for your network.

char ssid[] = "KCC-AP";     // your network SSID (name)
char pass[] = "22917532";  // your network password
int status  = WL_IDLE_STATUS;    // the Wifi radio's status

//char mqttServer[]     = "q.m2m.io";
char mqttServer[]     = "iot.eclipse.org";   // "q.m2m.io"
//char mqttServer[]     = "lora.myqnapcloud.com";
int  mqttport = 1883;
char clientId[]       = "AmebaClient99";
char publishTopic[]   = "USER99/Message";
char publishPayload[] = "Sucessful connect to MQTT Server using Ameba";
char subscribeTopic1[] = "NCTU/USER99/LED";
char subscribeTopic2[] = "NCTU/USER99/RGBLED";
char subscribeTopic3[] = "NCTU/USER99/RGBPWM";
int payloadnum =0;
char publishstr[] = "";
int LEDr,LEDg,LEDb;
long lastReconnectAttempt = 0;


int redPin = 8;
int greenPin = 9;
int bluePin = 11;
//#define COMMON_ANODE
WiFiClient wifiClient;
PubSubClient mqttclient(wifiClient);

// Pin 13 is the LED output pin
int ledPin1 = 4;  // LED1
int ledPin2 = 5;  // LED2
int ledPin3 = 6;  // LED3
int ledPin4 = 7;  // LED4
int RGBledPin= 12;  // RGBLED bright control PWM pin 
int ledpwm=0;
// defines and variable for sensor/control mode
#define MODE_OFF    0  // not sensing light, LED off
#define MODE_ON     1  // not sensing light, LED on
#define MODE_SENSE  2  // sensing light, LED controlled by software
int senseMode = 0;

unsigned long time;

char message_buff[100];

void setup()
{

   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);    
  pinMode(RGBledPin, OUTPUT);
  digitalWrite(ledPin1, LOW);  // Trun off LED
  setColor(0,0,0);   // Trun off RGB LED
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 8 seconds for connection:
    delay(10000);
  }
  mqttclient.setServer(mqttServer, mqttport);   // connect to MQTT server using mqttport
  mqttclient.setClient(wifiClient);
  mqttclient.setCallback(callback);
  delay(2000);
//if (mqttclient.connect(clientId)) {
  // Allow the hardware to sort itself out
  reconnect();
  delay(2000);
 // }
}

void loop()
{
  
 if (!mqttclient.connected()) {
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
    mqttclient.loop();
  }
 }

boolean  reconnect() {
  // Loop until we're reconnected
  while (!mqttclient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
   // delay(1000);
    if (mqttclient.connect(clientId)) {
      Serial.println("connected");
      payloadnum++;
      sprintf(publishstr,"%s - %d",publishPayload,payloadnum);
      Serial.println(publishstr);
      mqttclient.publish(publishTopic, publishstr,true);
      //  resubscribe
        mqttclient.subscribe(subscribeTopic1,1);
        mqttclient.subscribe(subscribeTopic2,1);
        mqttclient.subscribe(subscribeTopic3,1);
      // Once connected, publish an announcement...
     return mqttclient.connected();
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
      }
    }
  }


// handles message arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {
  int i = 0;
  Serial.println("Message arrived:  topic: " + String(topic));
  Serial.println("Length: " + String(length,DEC));
 
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
  String msgString = String(message_buff);
   Serial.println("Payload: " + msgString);
   if (msgString.equals("LED:0")) {
    senseMode = MODE_OFF;
   } else if (msgString.equals("LED:1")) {
    senseMode = MODE_ON;
   } else if (msgString.substring(0,3).equals("rgb")) {
    changeColor(msgString);
   }
   else if (msgString.toInt()>=0) {
    ledpwm = msgString.toInt();
   } 
   
   processCTRL();
}

void processCTRL()
{
   switch (senseMode) {
    case MODE_OFF:
      // light should be off
      digitalWrite(ledPin1, LOW);
      break;
    case MODE_ON:
      // light should be on
      digitalWrite(ledPin1, HIGH);
      break;
  }
  analogWrite(RGBledPin, ledpwm);
  
}

void changeColor(String rgbString)  
{  
      //Parse RGB;  
      int rIndex=rgbString.indexOf(',');  
      int gIndex=rgbString.indexOf(',', rIndex+1);
      int endIndex = rgbString.indexOf(')');  
      int r= rgbString.substring(4,rIndex).toInt();  
      int g= rgbString.substring(rIndex+1,gIndex).toInt();  
      int b= rgbString.substring(gIndex+1,endIndex).toInt();  
      Serial.print(r);
      Serial.print(',');
       Serial.print(g);
      Serial.print(',');
      Serial.print(b);
      Serial.println("===");
      setColor(r,g,b); //light up  
}  

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
red = 255 - red;
green = 255 - green;
blue = 255 - blue;
#endif

analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
}


