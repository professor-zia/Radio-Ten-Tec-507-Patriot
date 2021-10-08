//-----------------------------------------------------
void  Band_20_Limit()
{
  if ( frequency >= 5.35e6 )
  {
    frequency = 5.35e6;
    stop_led_on();
  }
  else if ( frequency <= 5.0e6 )
  {
    frequency = 5.0e6;
    stop_led_on();
  }
  else {
    stop_led_off();
  }
}
