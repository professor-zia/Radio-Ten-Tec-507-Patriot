//------------------ Band Select ------------------------------------
void Band_Set_40_20M()
{
  if ( old_bsm != bsm)                          //  this helps 5/13/14
  {
    if ( bsm == 1 )                             //  select 40 or 20 meters 1 for 20 0 for 40
    {
      frequency_default = meter_20;
      Splash_Band();
    }
    else
    {
      frequency_default = meter_40;
      Splash_Band();
      IF *= -1;                               //  HI side injection
    }
    Default_frequency();
  }
  old_bsm = bsm;                              //  this helps 5/13/14
}
