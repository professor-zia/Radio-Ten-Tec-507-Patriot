//------------------------CAT Routine based on Elecraft K3 -------------------------------
//   some general routines for serial printing

int un_stage() {             // send a char on serial
  char c;
  if ( stg_in == stg_out ) return 0;
  c = stg_buf[stg_out++];
  stg_out &= ( STQUESIZE - 1);
  Serial.write(c);
  return 1;
}
void stage( unsigned char c ) {
  stg_buf[stg_in++] = c;
  stg_in &= ( STQUESIZE - 1 );
}
void stage_str( String st ) {
  int i;
  char c;
  for ( i = 0; i < st.length(); ++i ) {
    c = st.charAt( i );
    stage(c);
  }
}
void stage_num( int val ) {  // send number in ascii
  char buf[12];
  char c;
  int i;
  itoa( val, buf, 10 );
  i = 0;
  while ( c = buf[i++] ) stage(c);
}

void Poll_Cat() {
  static String command = "";
  String lcommand;
  char c;
  int rit;

  if (Serial.available() == 0) return;

  while ( Serial.available() ) {
    c = Serial.read();
    command += c;
    if ( c == ';' ) break;
  }

  if ( c != ';' ) {
    terminal = 0;  // command not complete yet but need to switch of terminal
    return;
  }

  lcommand = command.substring(0, 2);

  if ( command.substring(2, 3) == ";" || command.substring(2, 4) == "$;" || command.substring(0, 2) == "RV" ) { /* it is a get command */
    stage_str(lcommand);    // echo the command
    if ( command.substring(2, 3) == "$") stage('$');

    if (lcommand == "IF") {
      RX_frequency = frequency_tune - IF;
      stage_str("000");
      if ( RX_frequency < 10000000 ) stage('0');
      stage_num(RX_frequency);
      stage_str("     ");
      rit = RitFreqOffset;
      if ( rit >= 0 ) stage_str("+0");
      else {
        stage_str("-0");
        rit = - rit;
      }
      if ( rit < 100 ) stage('0');
      if ( rit < 10 ) stage('0');                                 // IF[f]*****+yyyyrx*00tmvspbd1*;
      stage_num(rit);
      stage_str("10 0003000001");                                 // rit,xit,xmit,cw mode fixed filed
    }
    else if (lcommand == "FA") {                                  // VFO A
      stage_str("000");
      if ( frequency_tune - IF < 10000000 ) stage('0');
      stage_num(frequency_tune - IF);
    }
    else if (lcommand == "KS") stage_num(CWSpeed);               // KEYER SPEED
    else if (lcommand == "FW") stage_str("0000") , stage_num(Selected_BW + 1);
    else if (lcommand == "MD") {
      if (mode == 0 && bsm == 0) stage('1');  // Mode
      if (mode == 0 && bsm == 1) stage('2');
      if (mode == 1) stage ('3');
    }
    else if (lcommand == "RV" && command.substring(2, 3) == "F") { // battery voltage in Front field
      stage(command.charAt(2));
      double value = analogRead(BatteryReadPin) * BatteryVconvert;
      int left_part, right_part;
      char buffer[50];
      sprintf(buffer, "%lf", value);
      sscanf(buffer, "%d.%1d", &left_part, &right_part);
      stage(' ');
      stage_num(left_part);
      stage('.');
      stage_num(right_part);
      stage(' ');
    }
    else if (lcommand == "RV" && command.substring(2, 3) == "A") { // Rebel Alliance Mod version in Aux: field
      stage(command.charAt(2));
      stage_str(txt0);
    }
    else if (lcommand == "RV" && command.substring(2, 3) == "D") { // Rebel Alliance Mod in DSP: field
      stage(command.charAt(2));
      stage_str(txt2);
    }
    else if (lcommand == "RV" && command.substring(2, 3) == "M") { // Keyer Speed in MCU: field
      stage(command.charAt(2));
      stage_num(CWSpeed);
    }
    else if (lcommand == "RV" && command.substring(2, 3) == "R") { // Keyer Speed in MCU: field
      stage(command.charAt(2));
      stage_str(steptext[Selected_Step]);
    }
    else if (lcommand == "SM") {
      stage_str("00");
      SmeterReadValue = analogRead(SmeterReadPin);
      SmeterReadValue = map(SmeterReadValue, 0, 1023, 0, 21);
      if ( SmeterReadValue < 10 ) stage('0');
      stage_num(SmeterReadValue);
    }
    else {
      stage('0');   // send back nill command not know / used
    }
    stage(';');       // response terminator
  }

  else  {} set_cat(lcommand, command);   // else it's a set command

  command = "";   // clear for next command
}

void set_cat(String lcom, String com ) {
  long value;
  int split = 0 ;

  if ( lcom == "FA" ) {  // set vfo freq
    value = com.substring(2, 13).toInt();
    if ( (value > Band_bsm0_Low && value < Band_bsm0_High) || (value > Band_bsm1_Low && value < Band_bsm1_High)  ) {
      // valid frequnecy according band configuration?
      if ( (value > Band_bsm0_Low && value < Band_bsm0_High) && bsm == 1) {
        // need to change band?
        bsm = 0;
        Change_Band();
      }
      if ( (value > Band_bsm1_Low && value < Band_bsm1_High) && bsm == 0) {
        // need to change band?
        bsm = 1;
        Change_Band();
      }
      if ( lcom == "FA" && ( value > 1800000 && value < 30000000) ) frequency = value + IF;
    }
  }
  else if ( lcom == "FW" ) {           // xtal filter select
    value = com.charAt(6) - '0';
    if ( value < 4 && value != 0 ) {
      if ( value == 1) {
        b = 0x00; // Hardware control of I.F. filter shape
        Selected_BW = Wide_BW;  // GPA7(28)LOW_GPA6(27)LOW wide
      }
      if ( value == 2) {
        b = 0x40; // Hardware control of I.F. filter shape
        Selected_BW = Medium_BW;  //  GPA7(28)LOW_GPA6(27)HIGH medium
      }
      if ( value == 3) {
        b = 0x80; // Hardware control of I.F. filter shape
        Selected_BW = Narrow_BW;   //  GPA7(28)HIGH_GPA6(27)LOW narrow
      }
      Select_Multi_BW_Ored();                     // original b is sent to port expander
    }
  }
  else if ( lcom == "MD" ) {
    value = com.charAt(2) - '0';
    if ( value == 1 || value == 2) {
      mode = 0;
      frequency_old = 0;
      UpdateFreq(frequency_tune);
      Splash_MODE();
    }
    if ( value == 3) {
      mode = 1;
      frequency_old = 0;
      UpdateFreq(frequency_tune);
      Splash_MODE();
    }
  }
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
