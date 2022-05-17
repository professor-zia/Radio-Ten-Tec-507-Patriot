//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// set LCD I2C address to 0x27 
// for a 16 chars and 2 line display

// set LCD I2C address to 0x3F 
// for a 20 chars and 4 line display

LiquidCrystal_I2C lcd(0x3F,20,4);  

void setup()
{
  // initialize LCD
  lcd.init();
  // set backlight ON
  lcd.backlight();
  // print a message to LCD
  lcd.setCursor(0,0);
  lcd.print("Hello,   World!");
  lcd.setCursor(0,1);
  lcd.print("Hello, Arduino!");
  lcd.setCursor(0,2);
  lcd.print("World + Arduino");
  lcd.setCursor(0,3);
  lcd.print("Happy Together!");
}

void loop()
{
}
