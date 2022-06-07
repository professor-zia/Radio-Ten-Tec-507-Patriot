//------------------------------------------------------------------------------
void splash_RX_freq()
{
  long RXD_frequency; // ADDED 6-18-14 OK

  if ( old_frequency_tune != frequency_tune )
  {
    if ( bsm == 1 )                      // test for 20M
    {
      RXD_frequency = frequency_tune ;
    }

    else if ( bsm == 0 )                 // test for 40M
    {
      RXD_frequency = frequency_tune ;
    }
    //-------------------------------------------

    if ( RXD_frequency < 5.36e6 )
    {
      RXD_frequency = RXD_frequency + 9e6;
    }

    else if ( RXD_frequency > 15.95e6 )
    {
      RXD_frequency = RXD_frequency - 9e6;
    }
    //--------------------------------------------
    // F_Zia 2021_0525 Right Justify Freq Display
    lcd.setCursor(3, 0);
    lcd.print(txt72);                    // spaces

    if ( bsm == 1 )                      // test for 20M
      lcd.setCursor(3, 0);
    else
      lcd.setCursor(4, 0);
    stringFREQ = String(RXD_frequency, DEC);
    lcd.print(stringFREQ);
  }
  old_frequency_tune = frequency_tune;
}
