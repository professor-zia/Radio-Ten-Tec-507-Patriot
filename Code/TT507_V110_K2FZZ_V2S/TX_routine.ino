//##################################################################
//---------------------  TX Routine  -------------------------------
void TX_routine()

{ //------------------  SSB Portion  ----------------------------

  PTT_SSB_Key = digitalRead( PTT_SSB );               // check to see if PTT is pressed,
  if   ( PTT_SSB_Key == LOW  )                       // if pressed do the following
  {
    do
    {
      TX_Frequency = frequency;
      frequency_tune  = TX_Frequency;             // RitFreqOffset is from Rit_Read();
      digitalWrite ( FREQ_REGISTER_BIT,   HIGH);      //
      UpdateFreq1(frequency_tune);

      Splash_MODE();
      Splash_TX_freq();

      old_b = b;                                 // save original b into old_b
      b = 0x00;                                // b is now set to wide filter setting
      Select_Multi_BW_Ored();                       // b is sent to port expander ic

      digitalWrite ( MIC_LINE_MUTE, HIGH);        // turns Q35, Q16 off, unmutes mic/line
      digitalWrite (SSB_CW, HIGH);              // this causes the ALC line to connect
      digitalWrite(TX_OUT, HIGH);             // Truns on Q199 (pwr cntrl)(switched lo/dds)
      // mutes audio to lm386
      PTT_SSB_Key = digitalRead(PTT_SSB);           // check to see if PTT is pressed
    }
    while (PTT_SSB_Key == LOW);

    b = old_b;                                    // original b is now restored
    Select_Multi_BW_Ored();                      // original b is sent to port expander

    digitalWrite(TX_OUT, LOW);                  // turn off TX stuff
    digitalWrite ( FREQ_REGISTER_BIT,   LOW); // added 6/23/14
    digitalWrite ( MIC_LINE_MUTE, LOW);     // turns Q36, Q16 on, mutes mic/line
  }  // End of SSB TX routine
  //---------------  CW Portion  --------------------------------
  TX_key = digitalRead(TX_Dit);                      //  Maybe put these on an interrupt!
  if ( TX_key == LOW)                               // was high
  {
    do
    {

      TX_Frequency = frequency;
      frequency_tune  = TX_Frequency;          // RitFreqOffset is from Rit_Read();
      digitalWrite ( FREQ_REGISTER_BIT,   HIGH);      //
      UpdateFreq1(frequency_tune);

      Splash_MODE();
      Splash_TX_freq();

      old_b = b;
      b = 0x00;                                  // b is now set to wide filter setting
      Select_Multi_BW_Ored();                  // b is sent to port expander ic


      digitalWrite(TX_OUT, HIGH);                    // turns tx circuit on
      digitalWrite (SSB_CW, LOW);                  // enables the cw pull down circuit
      digitalWrite(Side_Tone, HIGH);             // enables side-tone source
      TX_key = digitalRead(TX_Dit);            // reads dit key line
    }
    while (TX_key == LOW);                       // key still down
    b = old_b;                                    // original b is now restored
    Select_Multi_BW_Ored();
    for (int i = 0; i <= 10e2; i++);          // delay
    digitalWrite(TX_OUT, LOW);               // trun off TX cw key is now high
    digitalWrite ( FREQ_REGISTER_BIT,   LOW);    // return to DDS register 0  not in other

    digitalWrite(Side_Tone, LOW);                   // side-tone off
  }
}                                                      // end  TX_routine()

//------------------------------------------------------------------------
