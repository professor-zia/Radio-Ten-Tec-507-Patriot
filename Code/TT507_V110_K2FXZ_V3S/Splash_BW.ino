//--------------------------------------------------------------------
//--------------------------------------------------------------------
void Splash_BW()
{
  if ( old_b != b )
  {
    if ( b == 0x00 )
    {
      lcd.setCursor(3, 3);
      lcd.print(txt170);
      lcd.setCursor(3, 3);
      lcd.print(txt140);  // wide
    }
    else if ( b == 0x40 )
    {
      lcd.setCursor(3, 3);
      lcd.print(txt170);
      lcd.setCursor(3, 3);
      lcd.print(txt150);  // medium
    }
    else {
      lcd.setCursor(3, 3);
      lcd.print(txt170);
      lcd.setCursor(3, 3);
      lcd.print(txt160);  // narrow
    }
  }
  old_b = b ;
}
