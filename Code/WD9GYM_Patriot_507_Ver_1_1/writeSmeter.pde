
#ifdef WD9GYMSMETER
/**************************************************
     WD9GYM modification for S meter on I2C LCD
**************************************************/

// LCD Bars
byte meter_s1[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B11000,
B11000
};
byte meter_s3[8] = {
B00000,
B00000,
B00000,
B00000,
B00000,
B00011,
B11011,
B11011
};
byte meter_s5[8] = {
B00000,
B00000,
B00000,
B00000,
B11000,
B11000,
B11000,
B11000,
};
byte meter_s7[8] = {
B00000,
B00000,
B00000,
B00011,
B11011,
B11011,
B11011,
B11011,
};
byte meter_s9[8] = {
B00000,
B00000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
};
byte meter_s10[8] = {
B00000,
B00011,
B11011,
B11011,
B11011,
B11011,
B11011,
B11011,
};
byte meter_s20[8] = {
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
B11000,
};
byte meter_s30[8] = {
B11011,
B11011,
B11011,
B11011,
B11011,
B11011,
B11011,
B11011,
};

volatile unsigned long smeterTime, smeterLast, smeterInterval;

void writeSmeter()                 // WD9GYM modification
{
int  level;          
  smeterTime = millis(); // grab current time
  smeterInterval = smeterTime - smeterLast; // calculate interval between this and last event

    if (smeterInterval > 200) // ignore checks less than 200mS after initial edge
  {

     SmeterReadValue = analogRead(SmeterReadPin);   // read value of signal 0 - 1023
     level = map(SmeterReadValue, 1023, 0,41,0);    // constrain the value into db 0 - 40
 
  Serial.print("level = "); Serial.print(level);
     lcd.setCursor(12, 3);                      // print the s meter on line 4
     lcd.print("S     ");                       // blank out bars
     
     if (level > 30) level = 40;
     if (level > 20 && level < 31) level = 30;
     if (level > 10 && level < 21) level = 20;
     if (level > 7 && level < 10) level = 9;
     if (level > 5 && level < 8) level = 7;
     if (level > 3 && level < 6) level = 5;
     if (level > 1 && level < 4) level = 3;
     if (level > 0 && level < 2) level = 1;
   Serial.print(" level = "); Serial.println(level);   
     switch( level ){                           // write each bar required
        case 40:                                 // do not put break between case statements
          lcd.createChar(4, meter_s30);         // let the code fall through
          lcd.setCursor(18,3); 
          lcd.write( 4 );
        case 30: 
           lcd.createChar(4, meter_s30);
        case 20: 
           if( level == 20 ) lcd.createChar(4, meter_s20); 
           lcd.setCursor(17,3); 
           lcd.write( 4 );
        case 10: 
           lcd.createChar(3, meter_s10);
        case 9: if( level == 9 ) lcd.createChar(3, meter_s9); 
           lcd.setCursor(16,3); 
           lcd.write( 3 );
        case 7: 
           lcd.createChar(2, meter_s7);
        case 5: 
           if( level == 5 ) lcd.createChar(2, meter_s5); 
           lcd.setCursor(15,3); 
           lcd.write( 2 );
        case 3: 
           lcd.createChar(1, meter_s3);
        case 1: 
           if( level == 1 ) lcd.createChar(1, meter_s1); 
           lcd.setCursor(14,3); 
           lcd.write( 1 );
        case 0:
        default: break;
     }
   smeterLast = smeterTime; // set up for next event
  }

}
#endif  

