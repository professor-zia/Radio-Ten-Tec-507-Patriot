//==================================================================
//==================================================================
void Step_Function()
{
  switch ( Step_Multi_Function_Button1 )
  {
    case 0:
      m = 0x08;   // GPA3(24) Controls Function Green led
      Select_Multi_BW_Ored();
      Step_Select_Button1 = Selected_BW; //
      Step_Select(); //
      Selection();
      for (int i = 0; i <= 255; i++); // short delay
      break;   //

    case 1:
      m = 0x10;   // GPA4(25) Controls Function Yellow led
      Select_Multi_BW_Ored();
      Step_Select_Button1 = Selected_Step; //
      Step_Select(); //
      Selection();
      for (int i = 0; i <= 255; i++); // short delay
      break;   //

    case 2:
      m = 0x20;   // GPA5(26) Controls Function Red led
      Select_Multi_BW_Ored();
      Step_Select_Button1 = Selected_Other; //
      Step_Select(); //
      Selection();
      for (int i = 0; i <= 255; i++); // short delay
      break;   //
  }
}  // end Step_Function()
