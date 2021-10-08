//--------------------------------------------------------------------
void Splash_MODE()
{
  if ( old_PTT_SSB_Key != PTT_SSB_Key )
  {
    if ( PTT_SSB_Key == LOW )
    {
      lcd.setCursor(17, 2);
      lcd.print(txt69);     // clear LCD
      lcd.setCursor(17, 2);
      lcd.print(txt135);    // SSB
    }
    else
    {
      lcd.setCursor(17, 2);
      lcd.print(txt69);     // clear LCD
      lcd.setCursor(17, 2);
      lcd.print(txt132);    // CW
    }
  }
  old_PTT_SSB_Key = PTT_SSB_Key;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//stuff above is for testing using the Display Comment out if not needed
//-----------------------------------------------------------------------------
