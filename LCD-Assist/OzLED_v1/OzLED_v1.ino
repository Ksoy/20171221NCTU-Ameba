#include <Wire.h>
#include <OzOLED.h>

static const unsigned char PROGMEM OscarLogo[]  ={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0,
0xF0, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0x78, 0x38,
0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xE0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xE0, 0xFE, 0x7F, 0x07, 0x07, 0xFF, 0xFE, 0xC0, 0x00, 0x00, 0x00, 0x03, 0x0F,
0x1F, 0x38, 0x70, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1F, 0x3E, 0x78,
0x70, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x80, 0x81, 0x83, 0xC4, 0xC8, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xCF,
0x83, 0x80, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x70, 0x38, 0x1C, 0x1C, 0x0E, 0x06, 0x03, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xC0, 0xFC, 0xFF, 0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0F, 0xFF, 0xFC, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0xFE, 0xFC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x03, 0x0F, 0xFE, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x44, 0x46,
0xA2, 0x19, 0x11, 0x11, 0xA9, 0x48, 0x48, 0x90, 0x24, 0x24, 0x48, 0x50, 0x99, 0x39, 0x61, 0x53,
0xE3, 0x07, 0x8F, 0x0F, 0x1E, 0x3C, 0xF8, 0xF0, 0xE0, 0x80, 0x00, 0x00, 0x10, 0x18, 0x18, 0x1C,
0x0C, 0x0C, 0x0C, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x5F, 0x5F, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x40, 0x40,
0x48, 0x4F, 0x4F, 0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 0x4F, 0x4F, 0x48, 0x4C, 0x4C,
0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x4C, 0x4E, 0x4F, 0x43, 0x40, 0x40, 0x40, 0x4C, 0x4C, 0x5C, 0x5C,
0x5C, 0x5C, 0x5C, 0x4E, 0x4E, 0x47, 0x43, 0x00, 0x00, 0x00, 0x00, 0x40, 0x23, 0x14, 0x08, 0x14,
0x24, 0x42, 0x81, 0x82, 0x44, 0x68, 0x38, 0x18, 0x2D, 0x47, 0x42, 0x85, 0x04, 0x89, 0x71, 0x1E,
0x25, 0x40, 0x49, 0xF2, 0x06, 0x38, 0x40, 0x03, 0x0F, 0xFF, 0xFE, 0xE0, 0x00, 0x00, 0x08, 0x18,
0x10, 0x30, 0x60, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9F, 0x90, 0x90, 0x80, 0x1C, 0x14, 0x14, 0x08, 0x1C, 0x14,
0x10, 0x10, 0x1A, 0x1C, 0x18, 0x86, 0x1E, 0x00, 0x1D, 0x08, 0x14, 0x00, 0x1C, 0x00, 0x1C, 0x00,
0x9C, 0x80, 0x80, 0x18, 0x0E, 0x0B, 0x18, 0x04, 0x18, 0x0C, 0x1C, 0x18, 0x00, 0x18, 0x08, 0x1C,
0x00, 0x1C, 0x00, 0x1C, 0x0A, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x10, 0x0C, 0x02, 0x01, 0x01, 0x02, 0x04, 0x0C, 0x08, 0x90, 0x70, 0x38, 0x2D, 0x43, 0x42, 0x82,
0x84, 0x80, 0x78, 0x0F, 0x01, 0x79, 0x02, 0x00, 0xC0, 0xFF, 0x1F, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x0A, 0x0A, 0x04, 0x06, 0x0B, 0x0B, 0x00, 0x0F, 0x01,
0x0F, 0x00, 0x0B, 0x0D, 0x00, 0x0F, 0x00, 0x0F, 0x01, 0x0F, 0x00, 0x2F, 0x29, 0x1F, 0x00, 0x00,
0x09, 0x0A, 0x0A, 0x07, 0x2E, 0x1C, 0x03, 0x0A, 0x09, 0x0D, 0x01, 0x0B, 0x00, 0x0E, 0x09, 0x0B,
0x00, 0x0F, 0x01, 0x0F, 0x01, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0C, 0x03, 0x01, 0x01, 0x00, 0x00, 0x0C, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

static const unsigned char PROGMEM Temp [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00 
};
void setup(){

	OzOled.init();  //initialze Oscar OLED display

	OzOled.clearDisplay();               // clear the screen and set start position to top left corner
	OzOled.setPageMode();                // Set display addressing to page mode. (has to use this, can't use horizontal mode)
	OzOled.drawBitmap(OscarLogo, 0, 0, 16, 8);
	OzOled.setActivateScroll(Scroll_Left, 0, 7,Scroll_5Frames);  //Set the properties of Horizontal Scrool
	delay(2000);
}

void loop(){

}

