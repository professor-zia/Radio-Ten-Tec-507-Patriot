//-----------------------------------------------------
void UpdateFreq(long freq)
{
  if (LastFreqWriteTime != 0)
  {
    if ((millis() - LastFreqWriteTime) < 100) return;
  }
  LastFreqWriteTime = millis();
  if (freq == frequency_old) return;
  program_freq0( freq );
  frequency_old = freq;
}
