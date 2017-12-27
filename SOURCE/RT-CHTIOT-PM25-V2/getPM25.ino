void getPM25() {
int count = 0;
unsigned char c;
unsigned char high;
while (mySerial.available()) {
c = mySerial.read();
if((count==0 && c!=0x42) || (count==1 && c!=0x4d)){
Serial.println("check failed");
break;
}
if(count > 15){
Serial.println("complete");
break;
}
else if(count == 4 || count == 6 || count == 8 || count == 10 || count == 12 || count == 14) high = c;
else if(count == 5){
pmcf10 = 256*high + c;
//Serial.print("CF=1, PM1.0=");
//Serial.print(pmcf10);
//Serial.println(" ug/m3");
}
else if(count == 7){
pmcf25 = 256*high + c;
//Serial.print("CF=1, PM2.5=");
//Serial.print(pmcf25);
//Serial.println(" ug/m3");
}
else if(count == 9){
pmcf100 = 256*high + c;
//Serial.print("CF=1, PM10=");
//Serial.print(pmcf100);
//Serial.println(" ug/m3");
}
else if(count == 11){
pm10 = 256*high + c;
Serial.print("PM1.0=");
Serial.print(pm10);
Serial.println(" ug/m3");
}
else if(count == 13){
pm25 = 256*high + c;
Serial.print("PM2.5=");
Serial.print(pm25);
Serial.println(" ug/m3");
}
else if(count == 15){
pm100 = 256*high + c;
Serial.print("PM10=");
Serial.print(pm100);
Serial.println(" ug/m3");
}
count++;
}

while(mySerial.available()) mySerial.read();
Serial.println();
delay(1000);
  
}

