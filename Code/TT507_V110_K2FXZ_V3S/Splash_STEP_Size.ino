//---------------------------------------------------------------------------------

void Splash_Step_Size()
{
  if ( old_Frequency_Step != Frequency_Step ) //
  {
    lcd.setCursor(5, 2);
    lcd.print(txt71);                       // spaces

    if (Frequency_Step == 10000)
      lcd.setCursor(6, 2);
    else if (Frequency_Step == 1000)
      lcd.setCursor(7, 2);
    else if (Frequency_Step == 100)
      lcd.setCursor(8, 2);

    string_Frequency_Step = String(Frequency_Step, DEC);
    lcd.print(string_Frequency_Step);
  }
  old_Frequency_Step = Frequency_Step;      // test for Rit change
}
