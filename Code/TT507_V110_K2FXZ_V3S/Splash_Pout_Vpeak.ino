// Splash_Pout_Vpeak()
// F_Zia 2021_0620
void Splash_Pout_Vpeak()
{
  lcd.setCursor(17, 3);
  lcd.print(txt69);     // clear LCD
  lcd.setCursor(17, 3);
  PowerOutReadValue = analogRead(PowerOutReadPin);
  lcd.print(PowerOutReadValue);

  //  stringFREQ = String(TXD_frequency / 10, DEC);
  //  lcd.print(stringFREQ);
}
