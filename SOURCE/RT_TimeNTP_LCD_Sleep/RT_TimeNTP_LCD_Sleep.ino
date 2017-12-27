/*
 * Time_NTP.pde
 * Example showing time sync to NTP time source
 *
 * 2014/04/25 refined by RTK
 */
#include <WiFi.h>
#include <TimeLib.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // 設定 LCD I2C 位址
#include <PowerManagement.h>
 
int status = WL_IDLE_STATUS;
char ssid[] = "KCC-AP";      //  your network SSID (name)
char pass[] = "22917532";   // your network password

// NTP Servers:
IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov

const int timeZone = 8;     // Beijing Time, Taipei Time
//const int timeZone = 1;   // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
unsigned int localPort = 2390;  // local port to listen for UDP packets

void setup() 
{
  init_lcd();
  Serial.println("TimeNTP Example");
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    if (status == WL_CONNECTED) break;
    // wait 1 seconds for retry
    delay(1000);
  }

  Udp.begin(localPort);
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  
}

time_t prevDisplay = 0; // when the digital clock was displayed

void loop()
{  
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();  
    }
  }
  if ( second() == 0 ){lcd.backlight();} // 開啟背光
  showDateTime_LCD();
  PowerManagement.sleep();
  if ( second() > 3 ){lcd.noBacklight();} // 關閉背光
  delay(1000);
  PowerManagement.active(); 
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  Serial.println("Transmit NTP Request");
  Udp.setRecvTimeout(1500);
  sendNTPpacket(timeServer);
  if ( Udp.read(packetBuffer, NTP_PACKET_SIZE) > 0 ) {
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
  } else {
    Serial.println("No NTP Response :-(");
    return 0; // return 0 if unable to get the time
  }
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}


void init_lcd()
{
 lcd.begin(16, 2); // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光

   // 閃爍三次
   for(int i = 0; i < 3; i++) {
     lcd.backlight(); // 開啟背光
     delay(250);
     lcd.noBacklight(); // 關閉背光
     delay(250);
   }

   lcd.backlight();

   // 輸出初始化文字
   lcd.setCursor(0, 0); // 設定游標位置在第一行行首
   lcd.print("Hello, Ameba!");
   delay(1000);
   lcd.setCursor(0, 1); // 設定游標位置在第二行行首
   lcd.print("MAKERPRO");
 //  delay(5000);
 //  lcd.clear();
  
}


void  showDateTime_LCD()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Date:");
  lcd.print(year()); 
  lcd.print("/");
  lcd.print(month());
  lcd.print("/");
  lcd.print(day());
  
  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.print(hour());
  LCDprintDigits(minute());
  LCDprintDigits(second());
 }

void LCDprintDigits(int digits){
  // utility for digital clock display: prints preceding colon and leading 0
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

