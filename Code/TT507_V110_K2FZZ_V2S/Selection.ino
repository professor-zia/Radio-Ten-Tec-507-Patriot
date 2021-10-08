//===================================================================
void  Selection()
{
  Step_Select_Button = digitalRead(Select_Button);
  if (Step_Select_Button == HIGH)
  {
    while ( digitalRead(Select_Button) == HIGH ) {
    }  // added for testing
    for (int i = 0; i <= 150e3; i++); // short delay

    Step_Select_Button1 = Step_Select_Button1 + 1;
    if (Step_Select_Button1 > 2 )
    {
      Step_Select_Button1 = 0;
    }
  }
  Step_Select();
}  // end Selection()
//===================================================================
