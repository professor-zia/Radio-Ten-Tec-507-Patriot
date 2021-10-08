//===================================================================
void Multi_Function() //  pushbutton for BW, Step, Other
{
  // look into a skip routine for this
  Step_Multi_Function_Button = digitalRead(Multi_Function_Button);
  if (Step_Multi_Function_Button == HIGH)
  {
    while ( digitalRead(Multi_Function_Button) == HIGH ) {
    }  // added for testing
    for (int i = 0; i <= 150e3; i++); // short delay

    Step_Multi_Function_Button1 = Step_Multi_Function_Button1 + 1;
    if (Step_Multi_Function_Button1 > 2 )
    {
      Step_Multi_Function_Button1 = 0;
    }
  }
  Step_Function();
}  // end Multi_Function()
//===================================================================
