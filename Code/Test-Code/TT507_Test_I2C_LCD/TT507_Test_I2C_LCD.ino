// TT507_Test_I2C_LCD.ino
// F_Zia, K2FXZ, 2025_0105
// Dependencies:
// Arduino IDE version 1.8.13
// Install chipKit Uno32 core for Arduino IDE
// https://chipkit.net/wiki/index.php/How-To_Install_chipKIT_Core
// Install LiquidCrystal_I2C library (included in TT507*.zip file)

// MCU:    PIC32 MX320 F128H (80MHz MIPS 32-bits, 128k Flash, 16k SRAM)
// Board:  Digilent chipKIT UNO-32
// Shield: TT-507 Patriot Transceiver Board

// F_Zia, K2FZZ, 2021_0525, Added LCD I2C 20x4
// LCD I2C Address: 0x3F, Size: 20x4 (cols x rows)
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup()
{
  Serial.begin(115200);
  Serial.println("Patriot Ready:");

  lcd.init();  
  lcd.backlight(); // turn on LCD backlight, F_Zia 2021_0525

  // display power-on message on LCD, F_Zia 2021_0619
  lcd.setCursor(0, 0);
  lcd.print("TT-507 Patriot Ready");

} // end setup()

void loop()
{

} // end loop()
