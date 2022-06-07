//----------------------------------------------------------------------------------
void Select_Multi_BW_Ored()
{
  t = s | m | b ;    // or'ed bits

  Wire.beginTransmission(0x20);
  Wire.send(0x12); // GPIOA
  Wire.send(t); // port A  result of s, m, b
  Wire.endTransmission();

}  // end  Select_Multi_BW_Ored()
