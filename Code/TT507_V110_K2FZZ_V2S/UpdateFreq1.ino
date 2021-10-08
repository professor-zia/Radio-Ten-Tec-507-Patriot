//--------------------------------------------------------------
void UpdateFreq1(long frequency_TX)
{
  if (LastFreqWriteTime != 0)
  {
    if ((millis() - LastFreqWriteTime) < 100) return;
  }
  LastFreqWriteTime = millis();
  if (frequency_TX == frequency_old_TX) return;
  program_freq1( frequency_TX );
  frequency_old_TX = frequency_TX;
}
//------------------------------------------------------------------
