//-------------------------------------------------------
void Change_Band()
{
  if ( bsm == 1 )                            //  select 40 or 20 meters 1 for 20 0 for 40
  {
    digitalWrite(Band_Select, HIGH);
    Band_Set_40_20M();
  }
  else
  {
    digitalWrite(Band_Select, LOW);
    Band_Set_40_20M();
    IF *= -1;                               //  HI side injection
  }
}
