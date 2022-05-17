//===================================================================
void Display_Setup()
{
  // RX
  lcd.setCursor(0, 0);
  lcd.print(txt62);      // RX

  // RIT
  lcd.setCursor(12, 0);
  lcd.print(txt64);      // RIT

  // TX
  lcd.setCursor(0, 1);
  lcd.print(txt63);      // TX

  // BAND
  lcd.setCursor(12, 1);
  lcd.print(txt65);      // BAND
  // default band
  lcd.setCursor(17, 1);
  lcd.print(txt67);      // 40M   change this to txt66 for display of 20M

  // STEP
  lcd.setCursor(0, 2);
  lcd.print(txt90);      // STEP

  // MODE
  lcd.setCursor(12, 2);
  lcd.print(txt130);     // MODE
  // default MODE
  lcd.setCursor(17, 2);
  lcd.print(txt69);
  lcd.setCursor(17, 2);
  lcd.print(txt135);     // SSB
  
  // BW
  lcd.setCursor(0, 3);
  lcd.print(txt120);     // BW
  // default BW
  lcd.setCursor(3, 3);
  lcd.print(txt140);     // WIDE

  // BATT // replaced with
  // VOPK // K2FXZ, 2022_0514
  lcd.setCursor(12, 3);
  lcd.print(txt110);     // VOPK

}      // end of Display_Setup
