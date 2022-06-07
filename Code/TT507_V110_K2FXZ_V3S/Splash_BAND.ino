//-----------------------------------------------------------------
void Splash_Band()
{
  if ( bsm == 1 )            // test for 20M
  {
    lcd.setCursor(17, 1);
    lcd.print(txt66);        // 20 meters
  }
  else
  {
    lcd.setCursor(17, 1);
    lcd.print(txt67);        // 40 meters
  }
}
