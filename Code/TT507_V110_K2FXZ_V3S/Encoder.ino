//--------------------------- Encoder Routine ---------------------

void Encoder()
{
  n = digitalRead(encoder0PinA);
  if ( encoder0PinALast != n)
  {
    if ((encoder0PinALast == LOW) && (n == HIGH))
    {
      if (digitalRead(encoder0PinB) == LOW) //  Frequency_down
      { //encoder0Pos--;
        frequency = frequency - Frequency_Step;
        Step_Flash();
        if ( bsm == 1 ) {
          Band_20_Limit();
        }
        else if ( bsm == 0 ) {
          Band_40_Limit();
        }
      }
      else                                  //  Frequency_up
      { //encoder0Pos++;
        frequency = frequency + Frequency_Step;
        Step_Flash();
        if ( bsm == 1 ) {
          Band_20_Limit();
        }
        else if ( bsm == 0 ) {
          Band_40_Limit();
        }
      }
    }
    encoder0PinALast = n;
  }
}

//-------------------------------------------------------
