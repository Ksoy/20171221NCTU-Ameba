
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
   delay(5000);
 //  lcd.clear();
  
}


void  showIP_LCD()
{
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SSID:");
  lcd.print(WiFi.SSID());
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.print(WiFi.localIP());
}

