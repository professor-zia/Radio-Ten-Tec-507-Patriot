//------------------------------------------------------
void RIT_Read()
{
  int RitReadValueNew = 0 ;
  RitReadValueNew = analogRead(RitReadPin);
  RitReadValue = (RitReadValueNew + (12 * RitReadValue)) / 13;//Lowpass filter possible display role if changed
  if (RitReadValue < 500)
    RitFreqOffset = RitReadValue - 500;
  else if (RitReadValue < 523)
    RitFreqOffset = 0;//Deadband in middle of pot
  else
    RitFreqOffset = RitReadValue - 523;

  splash_RIT();    //   comment out if display is not needed
}
