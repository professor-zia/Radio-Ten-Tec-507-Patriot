//-----------------------------------------------------
void  Band_40_Limit()
{
  if ( frequency >= 16.3e6 )
  {
    frequency = 16.3e6;
    stop_led_on();
  }
  else if ( frequency <= 16.0e6 )
  {
    frequency = 16.0e6;
    stop_led_on();
  }
  else {
    stop_led_off();
  }
}
