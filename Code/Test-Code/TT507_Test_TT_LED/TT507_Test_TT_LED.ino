// TT507_Test_TT_LED.ino
// F_Zia, K2FXZ, 2025_0111
// Dependencies:
// Arduino IDE version 1.8.13
// Install chipKit Uno32 core for Arduino IDE
// https://chipkit.net/wiki/index.php/How-To_Install_chipKIT_Core
// Install LiquidCrystal_I2C library (included in TT507*.zip file)

// MCU:    PIC32 MX320 F128H (80MHz MIPS 32-bits, 128k Flash, 16k SRAM)
// Board:  Digilent chipKIT UNO-32
// Shield: TT-507 Patriot Transceiver Board
// Display: I2C LCD 2004

// F_Zia, K2FZZ, 2021_0525, Added LCD I2C 20x4
// LCD I2C Address: 0x3F, Size: 20x4 (cols x rows)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 20, 4);

#define TT_LED 24 // TenTec LED is connected to UNO32 Pin 24

void setup()
{
  Serial.begin(115200);
  Serial.println("Patriot Ready:");

  lcd.init();
  lcd.backlight(); // turn on LCD backlight, F_Zia 2021_0525

  // display power-on message on LCD, F_Zia 2021_0619
  lcd.setCursor(0, 0);
  lcd.print("TT-507 Patriot Ready");
  lcd.setCursor(0, 1);
  lcd.print("--Test: TenTec LED--");

  pinMode(TT_LED, OUTPUT);

} // end setup()

void loop()
{
  digitalWrite(TT_LED, HIGH);   // turn LED on
  delay(100);                   // wait
  digitalWrite(TT_LED, LOW);    // turn LED off
  delay(100);                   // wait
  digitalWrite(TT_LED, HIGH);   // turn LED on
  delay(100);                   // wait
  digitalWrite(TT_LED, LOW);    // turn LED off
  delay(700);                   // wait

} // end loop()
