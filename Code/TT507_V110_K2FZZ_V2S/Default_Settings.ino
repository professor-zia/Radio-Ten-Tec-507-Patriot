//===================================================================

void Default_Settings()
{
  m = 0x08;                 //

  s = 0x01;                 //

//bsm = 0;                  //  bsm = 0 is 40 meters bsm = 1 is 20 meters
// F_Zia, changed default startup band to 20m
  bsm = 1;                  //  bsm = 0 is 40 meters bsm = 1 is 20 meters
  frequency_default = meter_20; // change this to meter_20 for 20 meter default
  Default_frequency();
  b = 0x00; // Hardware control of I.F. filter shape wide setting
  Selected_BW = Wide_BW;

  digitalWrite (TX_OUT,               LOW);
  digitalWrite (Band_End_Flash_led,   LOW);
  digitalWrite (Side_Tone,            LOW);
  digitalWrite ( FREQ_REGISTER_BIT,   LOW);
  digitalWrite ( SSB_CW,              LOW);
  digitalWrite ( Band_Select,         LOW);
  digitalWrite ( MUTE,                HIGH);
  digitalWrite ( MIC_LINE_MUTE,       LOW);    //  receive mode
}
