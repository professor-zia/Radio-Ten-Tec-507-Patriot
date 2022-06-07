//-----------------------------------------------------------------------------
// ****************  Dont bother the code below  ******************************
// \/  \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/
//-----------------------------------------------------------------------------
void program_freq0(long frequency)
{
  AD9834_reset_high();
  int flow, fhigh;
  fcalc = frequency * (268.435456e6 / Reference );  // 2^28 =
  flow = fcalc & 0x3fff;            //  49.99975mhz
  fhigh = (fcalc >> 14) & 0x3fff;
  digitalWrite(FSYNC_BIT, LOW);  //
  clock_data_to_ad9834(flow | AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(fhigh | AD9834_FREQ0_REGISTER_SELECT_BIT);
  digitalWrite(FSYNC_BIT, HIGH);
  AD9834_reset_low();
}    // end   program_freq0

//------------------------------------------------------------------------------

void program_freq1(long frequency_TX)
{
  AD9834_reset_high();
  int flow, fhigh;
  fcalc = frequency * (268.435456e6 / Reference );  // 2^28 =
  flow = fcalc & 0x3fff;            //  use for 49.99975mhz
  fhigh = (fcalc >> 14) & 0x3fff;
  digitalWrite(FSYNC_BIT, LOW);
  clock_data_to_ad9834(flow | AD9834_FREQ1_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(fhigh | AD9834_FREQ1_REGISTER_SELECT_BIT);
  digitalWrite(FSYNC_BIT, HIGH);
  AD9834_reset_low();
}

//------------------------------------------------------------------------------
void clock_data_to_ad9834(unsigned int data_word)
{
  char bcount;
  unsigned int iData;
  iData = data_word;
  digitalWrite(SCLK_BIT, HIGH);  //portb.SCLK_BIT = 1;
  // make sure clock high - only chnage data when high
  for (bcount = 0; bcount < 16; bcount++)
  {
    if ((iData & 0x8000)) digitalWrite(SDATA_BIT, HIGH); //portb.SDATA_BIT = 1;
    // test and set data bits
    else  digitalWrite(SDATA_BIT, LOW);
    digitalWrite(SCLK_BIT, LOW);
    digitalWrite(SCLK_BIT, HIGH);
    // set clock high - only change data when high
    iData = iData << 1; // shift the word 1 bit to the left
  }  // end for
}      // end  clock_data_to_ad9834

//-----------------------------------------------------------------------------
void AD9834_init()      // set up registers
{
  AD9834_reset_high();
  digitalWrite(FSYNC_BIT, LOW);
  clock_data_to_ad9834(0x2300);  // Reset goes high to 0 the registers and enable the output to mid scale.
  clock_data_to_ad9834((FREQ0_INIT_VALUE & 0x3fff) | AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(((FREQ0_INIT_VALUE >> 14) & 0x3fff) | AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(0x2200); // reset goes low to enable the output.
  AD9834_reset_low();
  digitalWrite(FSYNC_BIT, HIGH);
}  //  end   AD9834_init()

//----------------------------------------------------------------------------
void AD9834_reset()
{
  digitalWrite(RESET_BIT, HIGH);  // hardware connection
  for (int i = 0; i <= 2048; i++); // small delay

  digitalWrite(RESET_BIT, LOW);   // hardware connection
}  // end AD9834_reset()

//-----------------------------------------------------------------------------
void AD9834_reset_low()
{
  digitalWrite(RESET_BIT, LOW);
}  // end AD9834_reset_low()

//..............................................................................
void AD9834_reset_high()
{
  digitalWrite(RESET_BIT, HIGH);
}  // end  AD9834_reset_high()

//^^^^^^^^^^^^^^^^^^^^^^^^^  DON'T BOTHER CODE ABOVE  ^^^^^^^^^^^^^^^^^^^^^^^^^
//=============================================================================
