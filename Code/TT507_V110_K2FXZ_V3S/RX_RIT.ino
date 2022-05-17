//-----------------------------------------------------
void  RX_Rit()
{
  RIT_Read();
  frequency_tune  = frequency + RitFreqOffset; // RitFreqOffset is from Rit_Read();
  UpdateFreq(frequency_tune);
  splash_RX_freq();   // this only needs to be updated when encoder changed.
}
