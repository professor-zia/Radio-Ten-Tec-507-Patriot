//------------------ Debug data output ------------------------------

void    serialDump()
{
  loopStartTime   = millis();
  loopsPerSecond  = loopCount - lastLoopCount;
  loopSpeed       = (float)1e6 / loopsPerSecond;
  lastLoopCount   = loopCount;

  Serial.print    ( "uptime: " );
  Serial.print    ( ++printCount );
  Serial.println  ( " seconds" );

  Serial.print    ( "loops per second:    " );
  Serial.println  ( loopsPerSecond );
  Serial.print    ( "loop execution time: " );
  Serial.print    ( loopSpeed, 3 );
  Serial.println  ( " uS" );

  Serial.print    ( "Freq Rx: " );
  Serial.print    ( frequency_tune - IF );
  Serial.print    ( " RIT: " );
  Serial.println  (  RitFreqOffset );
  //Serial.println  ( RX_frequency );

  Serial.print    ( "Freq Tx: " );
  Serial.println  ( frequency - IF );
  // Serial.println  ( TX_frequency );

  Serial.print    ( "BW: " );
    if ( b == 0x00 )
    {
      Serial.print(txt140);  // wide
    }
    else if ( b == 0x40 )
    {
      Serial.print(txt150);  // medium
    }
    else {
      Serial.print(txt160);  // narrow
    }
  Serial.println  ( );

  Serial.print    ( "BAND: " );
  Serial.println  ( );
  //    Serial.println  (  RitFreqOffset );

  Serial.print    ( "MODE: " );
  Serial.println  ( );
  //    Serial.println  (  RitFreqOffset );

  Serial.print    ( "STEP: " );
  Serial.println  (  Frequency_Step );

  Serial.println  ();

} // end serialDump()
