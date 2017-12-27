#include <WiFi.h>

char ssid[] = "KCC-AP";      //  your network SSID (name)
char pass[] = "22917532";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

const int led1=4; 
const int led2=5;
const int led3=6;
const int led4=7;
String readString = String(50);

void setup() {
  Serial.begin(9600);      // initialize serial communication
     pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
    pinMode(led4,OUTPUT);         // set the LED pin mode
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);  
        
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }
  
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
    if (client) 
    { 
      Serial.println("new client");           // print a message out the serial port
      String currentLine = "";   
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println();  
       
      client.print("<html>");
      client.print("<head>"); 
      client.print("<meta http-equiv=content-type content=text/html; charset=UTF-8>");     
      client.print("<meta http-equiv=\"Content-Language\" content=\"zh-tw\" />");  
      client.print("<style>"); 
      client.print("body,input{font-family: verdana, Times New Roman,微軟正黑體,新細明體;}");     
      client.print("p{text-align:center;font-size:60px;}");
      client.print("table{text-align:center;border-collapse:collapse}");        
      client.print("th,td,input{align:center;margin:2px;padding:10px;font-size:40px}");     
      client.print("th{color:white;}");        
      client.print("</style>");      
      client.print("</head>");        
      client.print("<body>");    
      client.print("<p>WiFi WebServer智慧控制居家 LDE燈</p>");   
      client.print("<table border=1 align=center width=75% height=50%>");       
      client.print("<tr>");  
      client.print("<th colspan=2 bgcolor=red>客廳大燈</th>");         
      client.print("</tr>"); 
      client.print("<tr>"); 
      client.print("<td>");       
      client.print("<form method=get>");      
      client.print("<input type=hidden name=L1 value=1>");   
      client.print("<input type=submit value=開-ON>");            
      client.print("</form>");
      client.print("</td>");       
      client.print("<td>");    
      client.print("<form method=get>");
      client.print("<input type=hidden name=L1 value=0>");   
      client.print("<input type=submit value=關-OFF>");            
      client.print("</form>");     
      client.print("</td>"); 
      client.print("</tr>");         

      client.print("<tr>");  
      client.print("<th colspan=2 bgcolor=orange>門口玄關</th>");         
      client.print("</tr>"); 
      client.print("<tr>"); 
      client.print("<td>");       
      client.print("<form method=get>");      
      client.print("<input type=hidden name=L2 value=1>");   
      client.print("<input type=submit value=開-ON>");            
      client.print("</form>");
      client.print("</td>");       
      client.print("<td>");    
      client.print("<form method=get>");
      client.print("<input type=hidden name=L2 value=0>");   
      client.print("<input type=submit value=關-OFF>");            
      client.print("</form>");     
      client.print("</td>"); 
      client.print("</tr>");             
     
      client.print("<tr>");  
      client.print("<th colspan=2 bgcolor=brown>主臥室</th>");         
      client.print("</tr>"); 
      client.print("<tr>"); 
      client.print("<td>");       
      client.print("<form method=get>");      
      client.print("<input type=hidden name=L3 value=1>");   
      client.print("<input type=submit value=開-ON>");            
      client.print("</form>");
      client.print("</td>");       
      client.print("<td>");    
      client.print("<form method=get>");
      client.print("<input type=hidden name=L3 value=0>");   
      client.print("<input type=submit value=關-OFF>");            
      client.print("</form>");     
      client.print("</td>"); 
      client.print("</tr>");             
      
      client.print("<tr>");  
      client.print("<th colspan=2 bgcolor=green>書房</th>");         
      client.print("</tr>"); 
      client.print("<tr>"); 
      client.print("<td>");       
      client.print("<form method=get>");      
      client.print("<input type=hidden name=L4 value=1>");   
      client.print("<input type=submit value=開-ON>");            
      client.print("</form>");
      client.print("</td>");       
      client.print("<td>");    
      client.print("<form method=get>");
      client.print("<input type=hidden name=L4 value=0>");   
      client.print("<input type=submit value=關-OFF>");            
      client.print("</form>");     
      client.print("</td>"); 
      client.print("</tr>");             
      
      client.print("</table>");
      client.print("</body></html>"); 

           client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        
            if (currentLine.endsWith("L1=1")) {
               digitalWrite(led1,HIGH);         
             }                  
            else if (currentLine.endsWith("L1=0")) { 
                   digitalWrite(led1,LOW);
            }
            else if (currentLine.endsWith("L2=1")) {
               digitalWrite(led2,HIGH);           
             }                  
            else if (currentLine.endsWith("L2=0")) { 
                   digitalWrite(led2,LOW);
            }
            else if (currentLine.endsWith("L3=1")) {
               digitalWrite(led3,HIGH);          
             }                  
            else if (currentLine.endsWith("L3=0")) { 
                   digitalWrite(led3,LOW);
            }
            else if (currentLine.endsWith("L4=1")) {
               digitalWrite(led4,HIGH);            
             }                  
            else if (currentLine.endsWith("L4=0")) { 
                   digitalWrite(led4,LOW);
            }            
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");      
   } // End if (client)
} // End loop

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
