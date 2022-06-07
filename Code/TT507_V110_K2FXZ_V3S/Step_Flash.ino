//-----------------------------------------------------
void Step_Flash()
{
  stop_led_on();
  for (int i = 0; i <= 25e3; i++); // short delay
  stop_led_off();
}
