//-----------------------------------------------------------------------
void Step_Select()
{
  switch ( Step_Select_Button1 )
  {
    case 0: //   Select_Green
      s = 0x01;  // GPA0(21) Controls Selection Green led
      if (Step_Multi_Function_Button1 == 0)
      {
        b = 0x00; // Hardware control of I.F. filter shape
        Selected_BW = Wide_BW;  // GPA7(28)LOW_GPA6(27)LOW wide
      }
      else if (Step_Multi_Function_Button1 == 1)
      {
        Frequency_Step = 100;   //  Can change this whatever step size one wants
        Selected_Step = Step_100_Hz;
      }
      else if (Step_Multi_Function_Button1 == 2)
      {
        bsm = 0;
        Change_Band();
        Encoder();
        Selected_Other = Other_1_user;
        // Other_1();
      }
      for (int i = 0; i <= 255; i++); // short delay
      break;

    case 1: //   Select_Yellow
      s = 0x02;    //  GPA1(22) Controls Selection Green led
      if (Step_Multi_Function_Button1 == 0)
      {
        b = 0x40; // Hardware control of I.F. filter shape
        Selected_BW = Medium_BW;  //  GPA7(28)LOW_GPA6(27)HIGH medium
      }
      else if (Step_Multi_Function_Button1 == 1)
      {
        Frequency_Step = 1e3;   //  Can change this whatever step size one wants
        Selected_Step = Step_1000_hz;
      }
      else if (Step_Multi_Function_Button1 == 2)
      {
        bsm = 1;
        Change_Band();
        Encoder();
        Selected_Other = Other_2_user;

        //   Other_2();
      }
      for (int i = 0; i <= 255; i++); // short delay
      break;

    case 2: //   Select_Red
      s = 0x04;    //  GPA2(23) Controls Selection Green led
      if (Step_Multi_Function_Button1 == 0)
      {
        b = 0x80; // Hardware control of I.F. filter shape
        Selected_BW = Narrow_BW;   //  GPA7(28)HIGH_GPA6(27)LOW narrow
      }
      else if (Step_Multi_Function_Button1 == 1)
      {
        Frequency_Step = 10e3;    //  Can change this whatever step size one wants
        Selected_Step = Step_10000_hz;
      }
      else if (Step_Multi_Function_Button1 == 2)
      {
        Selected_Other = Other_3_user;

        //       Other_3();
      }
      for (int i = 0; i <= 255; i++); // short delay
      break;
  }
  Select_Multi_BW_Ored();
  Splash_Step_Size();
  Splash_BW();
}  // end Step_Select()
