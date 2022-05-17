//------------------------------------------------------------------------------
void splash_TX_freq()
{
  long TXD_frequency;  // ADDED 6-18-14 OK

  if ( bsm == 1 )                      // test for 20M
  {
    TXD_frequency = frequency_tune ;
  }

  else if ( bsm == 0 )                  // test for 40M
  {
    TXD_frequency = frequency_tune ;
  }
  //---------------------------------------------------

  if ( TXD_frequency < 5.36e6 )
  {
    TXD_frequency = TXD_frequency + 9e6;
  }

  else if ( TXD_frequency > 15.95e6 )
  {
    TXD_frequency = TXD_frequency - 9e6;
  }
  //--------------------------------------------------
  // F_Zia 2021_0525 Right Justify Freq Display
  lcd.setCursor(3, 1);
  lcd.print(txt72);                       // spaces

  if ( bsm == 1 )               // test for 20M
    lcd.setCursor(3, 1);
  else
    lcd.setCursor(4, 1);
  // stringFREQ = String(TXD_frequency / 10, DEC);
  stringFREQ = String(TXD_frequency, DEC);
  lcd.print(stringFREQ);

}
