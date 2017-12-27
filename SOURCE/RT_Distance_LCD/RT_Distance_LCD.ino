/*
 * Demonstrates use of HC-SR04 ultrasonic range module
 *
 * This sketch sends a 10us pulse HIGH at trigger pin of HC-SR04.
 * HC-SR04 return a pulse HIGH at echo pin which corresponds the distance.
 *     Time = Width of Echo pulse, in us (micro second)
 *     Distance in centimeters = Time / 58
 *
 * HC-SR04 works at 5V domain.
 * It means the echo pin needs level shift from 5V to 3.3V.
 * We can either use a level converter or use resister to devide the level.
 *
 **/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCM1602 I2C LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int trigger_pin = 12;
const int echo_pin    = 13;

void setup() {
    Serial.begin(9600);
    Serial.print("setup");
    pinMode(trigger_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
   
    lcd.begin(16,2);               // initialize the lcd 
    lcd.backlight();
    lcd.setCursor ( 0, 0 );        // go to home
    lcd.print("Hello Ameba!");  
    lcd.setCursor ( 0, 1 );        // go to home
    lcd.print("DistancDetector");  
    delay ( 5000 );  // Delay 8 seconds
    lcd.clear();
}

void loop() {
    float duration, distance;

    // trigger a 10us HIGH pulse at trigger pin
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);

    // measure time cost of pulse HIGH at echo pin
    duration = pulseIn (echo_pin, HIGH);

    // calculate the distance from duration
    distance = duration / 58;
    if (distance > 450) return ; 
    Serial.print(distance);
    Serial.println(" cm");
    lcd.clear();
    lcd.setCursor ( 0, 0 );        // go to home
    lcd.print("Dist:"); 
    lcd.print(distance);
    lcd.print("cm");

    // wait for next calculation
    delay(1000);
}
