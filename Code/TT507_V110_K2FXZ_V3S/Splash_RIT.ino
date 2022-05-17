//------------------------Display Stuff below-----------------------------------

// All the code for display below seems to work well. 6-18-14

//------------------- Splash RIT -----------------------------------------------
void Splash_RIT()      // not used
{
  if ( old_RitFreqOffset != RitFreqOffset) // only if RIT changes
  {
    lcd.setCursor(16, 0);
    lcd.print(txt70);                       // spaces

    lcd.setCursor(16, 0);
    stringRIT = String( RitFreqOffset, DEC);

    lcd.print(stringRIT);
  }
  old_RitFreqOffset = RitFreqOffset;      // test for Rit change
}
