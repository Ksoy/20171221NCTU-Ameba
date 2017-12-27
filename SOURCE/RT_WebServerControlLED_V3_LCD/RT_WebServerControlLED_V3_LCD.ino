#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // 設定 LCD I2C 位址
 
char ssid[] = "KCC-VPN-AP";      //  your network SSID (name)
char pass[] = "22917532";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup();
void loop() ;
void init_lcd();
void  showIP_LCD();
void  showLEDstatus_LCD();
void printWifiStatus();


const int led1=4; 
const int led2=5;
const int led3=6;
const int led4=7;
String readString = String(50);
String LED1status="LED1:OFF";    
String LED2status="LED2:OFF";    
String LED3status="LED3:OFF";    
String LED4status="LED4:OFF";    
long entTime,runTime,duringTime,startTime,rebootTime;
const long oneSecond = 1000; // a second is a thousand milliseconds
const long threeSecond = 1000*3;
const long tenSecond = 1000*10; 
const long f55Second = 1000*55;
const long f50Second = 1000*50;
const long f30Second = 1000*30;
//const long oneMinute = oneSecond * 60;
const long oneMinute = oneSecond * 60;
const long oneHour = oneMinute * 60;
const long oneDay = oneHour * 24;

