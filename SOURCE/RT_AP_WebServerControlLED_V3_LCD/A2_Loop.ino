
void loop() {
  // LCD Power saving control
  runTime = millis();
  duringTime = runTime - entTime;
  if (duringTime > tenSecond) {
     lcd.noBacklight(); // 關閉背光
     }
   
   //
       
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
       // entTime = millis(); 
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
               LED1status="LED1:ON"; 
              }                  
            else if (currentLine.endsWith("L1=0")) { 
                   digitalWrite(led1,LOW);
                   LED1status="LED1:OFF";
              }
            else if (currentLine.endsWith("L2=1")) {
               digitalWrite(led2,HIGH);
               LED2status="LED2:ON";    
              }                  
            else if (currentLine.endsWith("L2=0")) { 
                   digitalWrite(led2,LOW);
                   LED2status="LED2:OFF";  
              }
            else if (currentLine.endsWith("L3=1")) {
               digitalWrite(led3,HIGH); 
               LED3status="LED3:ON";  
              }                  
            else if (currentLine.endsWith("L3=0")) { 
                   digitalWrite(led3,LOW);
                   LED3status="LED3:OFF";  
              }
            else if (currentLine.endsWith("L4=1")) {
               digitalWrite(led4,HIGH);
               LED4status="LED4:ON";    
              }                  
            else if (currentLine.endsWith("L4=0")) { 
                   digitalWrite(led4,LOW);
                   LED4status="LED4:OFF";  
              } 
                       
      }  // if 
    }  // while  
    // close the connection:
    client.stop();
    entTime = millis();
    Serial.println("client disonnected");
    showLEDstatus_LCD();
   } // End if (client)
} // End loop

