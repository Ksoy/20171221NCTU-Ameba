int redPin = 8;
int greenPin = 9;
int bluePin = 11;
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE

int fade_pin = 12;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void setup()
{
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
pinMode(fade_pin, OUTPUT);
}

void loop()
{
setColor(255, 0, 0); // red
RGB_Fade();
delay(1000);
setColor(0, 255, 0); // green
RGB_Fade();
delay(1000);
setColor(0, 0, 255); // blue
RGB_Fade();
delay(1000);
setColor(255, 255, 0); // yellow
RGB_Fade();
delay(1000);
setColor(80, 0, 80); // purple
RGB_Fade();
delay(1000);
setColor(0, 255, 255); // aqua
RGB_Fade();
delay(1000);
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

void RGB_Fade()
{
  for (brightness=0;brightness<=255;brightness = brightness + fadeAmount) {
   analogWrite(fade_pin, brightness);
   delay(50);
  }

}

