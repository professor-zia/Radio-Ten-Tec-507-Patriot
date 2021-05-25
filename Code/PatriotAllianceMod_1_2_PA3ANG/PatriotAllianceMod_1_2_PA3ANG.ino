/* PatriotAllianceMod   version 1.2

  Based on the original Ten-Tec sketch and the RebelAllianceMod Version. 
  This beta version includes:
  1. IAMBIC keyer with A/B, reverse lever option, speed control front pot, Straight Keyer detection
  2. CW mode activates by pushing key or lever and shifts RX 700Hz up, SSB 0Hz shifts at pushing mike PTT  CW_offset_value
  3. Pressing SELECT >.5 seconds is frequency announce
  4. Parameter to correct DDS offset (varies per Patriot)  DDS_offset_value
  5. 20 x 4 line LCD display with CW speed, S-meter and all functions information minimalised!
  6. CAT based on K3 protocol (Frequency, Band control, Bandwidth and Mode)
  7. Faster encoder (abt 3,5 times faster)
  8. Pressing FUNCTION >.5 seconds will put TRX in TUNE (carrier) mode.
  9. Function BND will toggle between 40M-20M (U3 switched off)
  10. OLED display 128 x 32 pixels I2C added.
  11. Display will only update when information is changed.
  12. Step changed to 10Hz, 100Hz, 1kHz.
  13. LCD selectable (in the code) for 4Bit of I2C.
  14. Start band and mode selectable (in the code) as wel as the default frequencies.
  
  The PatriotAllianceMod is a sketch based on the RebelAllianceMod (the 1st Ten-Tec open source product) and the sketch has been
  tested by beta testers. The code captured in the Sketch is coming from multiple sources brought to you by 
  PA3ANG, W8CQD, HB9MTN, KD0UTH, K2NG, K6HX, WD9GYM, W8TEE, WA4CDM, NA8E, K4JK, AE6RQ, K1EL and W2ROW
    
  
*/  
  
/*  Code for Production 3_2_15
 <Patriot_507_Alpha_Rev01, Basic Software to operate a 2 band SSB/CW QRP Transceiver.
 See PROJECT PATRIOT SSB/CW QRP below>
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
//  https://groups.yahoo.com/neo/groups/TenTec507Patriot/info/
// !! Disclaimer !!  !! Disclaimer !!  !! Disclaimer !!  !! Disclaimer !!  !! Disclaimer !!
//  Attention ****  Ten-Tec Inc. is not responsile for any modification of Code 
//  below. If code modification is made, make a backup of the original code. 
//  If your new code does not work properly reload the factory code to start over again.
//  You are responsible for the code modifications you make yourself. And Ten-Tec Inc.
//  Assumes NO libility for code modification. Ten-Tec Inc. also cannot help you with any 
//  of your new code. There are several forums online to help with coding for the ChipKit UNO32.
//  If you have unexpected results after writing and programming of your modified code. 
//  Reload the factory code to see if the issues are still present. Before contacting Ten_Tec Inc.
//  Again Ten-Tec Inc. NOT RESPONSIBLE for modified code and cannot help with the rewriting of the 
//  factory code!
/*

/*********  PROJECT PATRIOT SSB/CW QRP  *****************************
 * Program for the ChipKit Uno32
 * This is a simple program to demonstrate a 2 band QRP Amateur Radio Transceiver
 * Amateur Programmer Bill Curb (WA4CDM).
 * This program will need to be cleaned up a bit and no doubt be made more efficient!
 * Compiled using the MPIDE for the ChipKit Uno32.
 * 
 * Prog for ad9834
 * Serial timming setup for AD9834 DDS
 * start > Fsync is high (1), Sclk taken high (1), Data is stable (0, or 1),
 * Fsync is taken low (0), Sclk is taken low (0), then high (1), data changes
 * Sclk starts again.
 * Control Register D15, D14 = 00, D13(B28) = 1, D12(HLB) = X,
 * Reset goes high to set the internal reg to 0 and sets the output to midscale.
 * Reset is then taken low to enable output. 
 ***************************************************   
 * Current supported display 4 bit LCD 40 x 2 characters 
 *****************************************************************
 * The pinout for the LCD is as follows: Also the LCD is setup up for 4 lines 20 charactors.
 * LCD RS pin to digital pin 26
 * LCD Enable pin to digital pin 27
 * LCD D4 pin to digital pin 28
 * LCD D5 pin to digital pin 29
 * LCD D6 pin to digital pin 30
 * LCD D7 pin to digital pin 31
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)    
 *****************************************************************
 * SELECT button steps are defined as: 
 * BW ( <Wide, green>, <Medium, yellow>, <Narrow, red> ).
 * STEP ( <100 hz, green, <1Khz, yellow>, 10Khz, red> ).
 * BND ( < 40M >, < 20M >, < , > ) OTHER has yet to be defined
 * 
 * Default Band_width will be wide ( Green led lite ).
 * When pressing the function button one of three leds will lite. 
 * as explained above the select button will choose which setting will be used. 
 * The Orange led in the Ten-Tec logo will flash to each step the STEP is set 
 * too when tuning.  As it will also turn on when at the BAND edges.
 * The TT logo led will also flash to indicate ALC. Input levels should be kept low enough
 * to only flash this led on Peaks.  
 * Default frequency on power up will be the calling frequency of the 
 * 40 meter band. 
 * I.F. Frequency used is 9.0 mhz.
 * DDS Range is: 
 * 40 meters will use HI side injection.
 * 9(I.F.) + 7(40m) = 16mhz.  9(I.F.) + 7.30 = 16.3 mhz.
 * 20 meters will use LO side injection.
 * 14(20m) - 9(I.F.) = 5mhz.  14.350(20m) - 9(I.F.) = 5.35 mhz.
 * 
 * The Headphone jack can supply a headphone or speaker. The header pins(2) 
 * if shorted will drive a speaker.
 * Unshorted inserts 100 ohm resistors in series with the headphone to limit 
 * the level to the headphones.
 * 
 * The RIT knob will be at 0 offset in the Top Dead Center position. And will 
 * go about -500 hz to +500 hz when turned to either extreme. Total range 
 * about +/- 500 hz. This may change!
 * 
 **************************************************************************************  
 * 
 * Added an MCP23017 16-bit I/O Expander with Serial Interface to free up
 * some I/O pins on the ChipKit Uno32 board.
 * The parts of the 507 being controlled by this ic will be the Multi-purpose
 * leds, the Select leds and the Wide/medium/Narrow control.
 * 5/1/2014 added a couple of routines to keep the filter wide on TX of SSB or CW
 * Port B can be used by the user for external control.
 * 
 * GPAO (21) Select Green led
 * GPA1 (22) Select Yellow led
 * GPA2 (23) Select Red led
 * GPA3 (24) MP_A Green led
 * GPA4 (25) MP_B Yellow led
 * GPA5 (26) MP_C Red led
 * GPA6 (27) Medium A8 BW_control
 * GPA7 (28) Narrow A9 BW_control
 * 
 * A mask function will be used to combine the various bits together.
 */


// various defines
#define SDATA_BIT                           11          // 
#define SCLK_BIT                            12          //  
#define FSYNC_BIT                           13          //  
#define RESET_BIT                           10          //  
#define FREQ_REGISTER_BIT                   9           //  
#define PHASE_REGISTER_BIT                  8
#define AD9834_FREQ0_REGISTER_SELECT_BIT    0x4000      //  
#define AD9834_FREQ1_REGISTER_SELECT_BIT    0x8000      //  
#define FREQ0_INIT_VALUE                    0x00000000  // 0x01320000
#define MUTE                                4
#define MIC_LINE_MUTE                       34
#define Side_Tone                           3           // 
#define PTT_SSB                             22          // ptt input pulled high 
#define SSB_CW                              42          // control line for /SSB_CW switches output
							// high for cw , low for ssb
#define TX_Dah                              33          // 
#define TX_Dit                              32          //  
#define TX_OUT                              38          //  
#define Band_End_Flash_led                  24          // 
#define Band_Select                         41          // output for band select
#define Multi_Function_Button               5           //
#define Select_Button                       2           // 

#define Wide_BW                             0           // 
#define Medium_BW                           1           // 
#define Narrow_BW                           2           // 
#define Step_10_Hz                          0
#define Step_100_Hz                         1
#define Step_1000_Hz                        2
#define Other_1_user                        0           // 40 meters
#define Other_2_user                        1           // 20 meters
#define Other_3_user                        2           // anything you desire!

/**************************************************
 * WD9GYM modification for S meter on I2C LCD
 * Modified for base LCD code by W8CQD
 **************************************************/
// LCD Bars
byte meter_s1[8]  = {  B00000,  B00000,  B00000,  B00000,  B00000,  B00000,  B11000,  B11000, };
byte meter_s3[8]  = {  B00000,  B00000,  B00000,  B00000,  B00000,  B00011,  B11011,  B11011, };
byte meter_s5[8]  = {  B00000,  B00000,  B00000,  B00000,  B11000,  B11000,  B11000,  B11000, };
byte meter_s7[8]  = {  B00000,  B00000,  B00000,  B00011,  B11011,  B11011,  B11011,  B11011, };
byte meter_s9[8]  = {  B00000,  B00000,  B11000,  B11000,  B11000,  B11000,  B11000,  B11000, };
byte meter_s10[8] = {  B00000,  B00011,  B11011,  B11011,  B11011,  B11011,  B11011,  B11011, };
byte meter_s20[8] = {  B11000,  B11000,  B11000,  B11000,  B11000,  B11000,  B11000,  B11000, };
byte meter_s30[8] = {  B11011,  B11011,  B11011,  B11011,  B11011,  B11011,  B11011,  B11011, };
  int  level;          

volatile unsigned long smeterTime, smeterLast, smeterInterval;

const int RitReadPin        = A0;  		// pin that the sensor is attached to used for a rit routine later.
int RitReadValue            = 0;
int RitFreqOffset           = 0;
int old_RitFreqOffset       = 0;

const int SmeterReadPin     = A1;  		// To give a realitive signal strength based on AGC voltage.
int SmeterReadValue         = 0;

const int BatteryReadPin    = A2;  		// Reads 1/5 th or 0.20 of supply voltage.
int BatteryReadValue        = 0;
float BatteryVconvert       = 0.01707; 	// calibration value

const int PowerOutReadPin   = A3;  		// Reads RF out voltage at Antenna.
int PowerOutReadValue       = 0;

const int CodeReadPin       = A6;  		// Can be used to decode CW. 
int CodeReadValue           = 0;

const int CWSpeedReadPin    = A7;  		// To adjust CW speed for user written keyer.
int CWSpeedReadValue        = 0;    


//-------------------------------  SET OPTONAL FEATURES HERE  ----------------------------------------------
int ST_key = 0;                    		// Set this to 1 is you want to disable the keyer completely

// included in this sketch is a Simple Arduino CW text Keyer 
// doing a frequency announce by pressing the SELECT > 0.5 seconds.
// Written by Mark VandeWettering K6HX
// Morse table
#define     N_MORSE  (sizeof(morsetab)/sizeof(morsetab[0]))    // Morse Table
struct t_mtab { char c, pat; } ;
struct t_mtab morsetab[] = {
    {'.', 106}, {',', 115}, {'?', 76}, {'/', 41}, {'A', 6},  {'B', 17}, {'C', 21}, {'D', 9}, 
    {'E', 2},   {'F', 20},  {'G', 11}, {'H', 16}, {'I', 4},  {'J', 30}, {'K', 13}, {'L', 18}, 
    {'M', 7},   {'N', 5},   {'O', 15}, {'P', 22}, {'Q', 27}, {'R', 10}, {'S', 8},  {'T', 3}, 
    {'U', 12},  {'V', 24},  {'W', 14}, {'X', 25}, {'Y', 29}, {'Z', 19}, {'1', 62}, {'2', 60}, 
    {'3', 56},  {'4', 48},  {'5', 32}, {'6', 33}, {'7', 35}, {'8', 39}, {'9', 47}, {'0', 63}
};

//  keyerControl bit definitions
#define     DIT_L      0x01     // Dit latch
#define     DAH_L      0x02     // Dah latch
#define     DIT_PROC   0x04     // Dit is being processed

//-------------------------------  CHANGE KEYER SETTINGS HERE  -------------------------------------------------------------
#define     PDLSWAP    0x00     // 0x00 for normal, 0x08 for swap
#define     IAMBICB    0x10     // 0x00 for Iambic A, 0x10 for Iambic B
//-------------------------------  CHANGE KEYER SETTINGS HERE  -------------------------------------------------------------

//Keyer Variables for IAMBIC keyer K2NG
unsigned char       keyerControl;
unsigned char       keyerState;
unsigned long       ditTime;                // No. milliseconds per dit
int 		    CWSpeed;                // Speed controlled by A7 
static long 	    idletimer;	            // will inhibit all polling to keep keying clean
enum KSTYPE {IDLE, CHK_DIT, CHK_DAH, KEYED_PREP, KEYED, INTER_ELEMENT };

// some text variables for the display and terminal functions
#define bw 3
String bwtext[bw] = { "W", "M", "N" };
#define stp 3
String steptext[stp] = {"10 ", "100", "1K "};
#define mod 4
String modetext[mod] = {"LSB", "USB", "CW ", "CW "};

// define terminal / cat active at start
int terminal = 1;                              // 1: terminal active at start

unsigned long  catStartTime    = 0;
unsigned long  catElapsedTime  = 0;
// stage buffer to avoid blocking on serial writes when using CAT
#define STQUESIZE 64
unsigned char stg_buf[STQUESIZE];
int stg_in = 0;
int stg_out = 0;

// bsm=0 is 40 meter, bsm=1 is 20 meter (used in CAT routine)
int Band_bsm0_Low              =  7000000;
int Band_bsm0_High             =  7300000;
int Band_bsm1_Low              = 14000000;    
int Band_bsm1_High             = 14350000;
const char txt0[7]          = "  1.2";
const char txt2[8]          = "Patriot";

//************************************************************************************************************

//-------------------------------  CHOOSE YOUR DISPLAY CONNECTION TYPE HERE  --------------------------------

// 4BIT LCD 20 x 4 line display  (LCD pins standard according Ten-tec documentation)
//#include <Wire.h>
//#include <LiquidCrystal.h>    
//LiquidCrystal lcd(26, 27, 28, 29, 30, 31);      //  Set de LCD pins

// I2C LCD  20 x 4 line display  (I2C pins to LCD: addr, en,rw,rs,d4,d5,d6,d7,bl,blpol)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address tp 0x27
LiquidCrystal_I2C lcd(0x3F, 20, 4);

//-------------------------------  CHOOSE YOUR DISPLAY CONNECTION TYPE HERE  --------------------------------

// ------------------------------  IF WANTED, ENABLE THE OLED TYPE DISPLAY HERE ------------------------------
// OLED 128 x 32 I2C (ADAFRUIT)
// enable OLED with uncomment #define OLED
// RST is pin 35 (optional)
//#define OLED 

#ifdef OLED 
  // Load Library  if no OLED then you can comment these 4 lines out 
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #define OLED_RESET 35
  Adafruit_SSD1306 display(OLED_RESET);
#endif
// ------------------------------  IF WANTED, ENABLE THE OLED TYPE DISPLAY HERE ------------------------------

//************************************************************************************************************

// Sketch variables
String stringFREQ;
String stringRIT;
int TX_key;
int PTT_SSB_Key;
int old_PTT_SSB_Key;
int old_mode;
int old_bsm;            
int forcedSplash;

int Step_Select_Button          = 0;
int Step_Select_Button1         = 0;
int Step_Multi_Function_Button  = 0;
int Step_Multi_Function_Button1 = 0;
int Selected_BW                 = 0;            // current Band width 
					        // 0= wide, 1 = medium, 2= narrow
int old_Selected_BW             = 4;            // put illigale value to force 1st update at startup
int Selected_Step               = 0;            // Current Step
                                                // 0=10,  1=100, 2=1K
int old_Selected_Step           = 4;            // put illigale value to force 1st update at startup
int Selected_Other              = 0;            // band and U3

byte s                          = 0x01;         // s = select
byte m                          = 0x08;         // m = multi
byte b                          = 0x00;         // b = bandwidth
byte t                          = 0x00;         // s + m ored
byte old_b                      = 0x00;         // for the TX routine

// Encoder Stuff 
const int encoder0PinA          = 6; 	// reversed for 507
const int encoder0PinB          = 7; 	// reversed for 507

int val; 
int encoder0Pos                 = 0;
int encoder0PinALast            = LOW;
int encoder0PinBLast            = LOW;
int n                           = LOW;
int o                           = LOW;

//************************************************************************************************************

//--------  OFFSET VALUES -- ADJUST TO YOUR PATRIOT DDS OFFSET AND CW PITCH  -----------------------
long DDS_offset_value           = 400 ;         // <<  Offset for easy frequency tweaking added by HB9MTN
long CW_offset_value            = 700 ;         // <<  CW shift on RX
// -------  please here the default mode and band --------------------------
int mode                        = 0;            // mode 1 = cw ,  mode 0 = ssb
int bsm                         = 0;            // bsm = 0 is 40 meters ,  bsm = 1 is 20 meters
// -------  please here you start frequency per band -----------------------
const long meter_40             =  7077000;     // ENTER YOUR STARTUP FREQUENCY HERE FOR 40 MTR IN Hz
const long meter_20             = 14205000;     // ENTER YOUR STARUP FREQUENCY HERE FOR 20 MTR IN Hz

//**************************************************************************************************************


// Parameters dealing with frequency management  --  AND DEFAULT STARTUP FREQUENCIES -----
const long Reference            = 50.0e6;          	// for ad9834 this may be 
							// tweaked in software to 
const long IF_value             = 9.00e6;               //  I.F. Frequency
long IF;
long frequency_40               = meter_40 + IF_value; 	// saved 40 meter freq + IF_value! HI side injection

long frequency_20               = meter_20 - IF_value;  // saved 20 meter freq - IF_value! LOW side injection
long frequency_TX;                                 
long TX_frequency;
long RIT_frequency;
long RX_frequency;
long Frequency_Step             = 10;
long frequency                  = 0;
long frequency_old              = 0;
long frequency_old_TX           = 0;
long frequency_tune             = 0;
long old_frequency_tune         = 0;
long frequency_default          = 0;
long fcalc;
long TX_Frequency               = 0;
long CW_offset;
long offset;

// Timer Stuff
unsigned long loopStartTime     = 0;
unsigned long loopElapsedTime   = 0;
unsigned long LastFreqWriteTime = 0;
unsigned long LastFreqDispTime  = 0;

//-----------------------------------------------------
void Default_frequency();
void AD9834_init();
void AD9834_reset();
void program_freq0(long freq);
void program_freq1(long freq1);  
void UpdateFreq(long freq);

void RX_Rit();             

void TX_routine();
void RX_routine();
void Encoder();
void AD9834_reset_low();
void AD9834_reset_high();

void Change_Band();
void Step_Flash();
void RIT_Read();

void Multi_Function();          
void Step_Selection();           
void Selection();               
void Step_Multi_Function();     

//----------------------------------------------------- 
void clock_data_to_ad9834(unsigned int data_word);
//-----------------------------------------------------

void setup() 
{
  // these pins are for the AD9834 control
  pinMode (SCLK_BIT,                 OUTPUT);    // clock
  pinMode (FSYNC_BIT,                OUTPUT);    // fsync
  pinMode (SDATA_BIT,                OUTPUT);    // data
  pinMode (RESET_BIT,                OUTPUT);    // reset
  pinMode (FREQ_REGISTER_BIT,        OUTPUT);    // freq register select

  //---------------  Encoder ----------------------------
  pinMode (encoder0PinA,             INPUT);     // 
  pinMode (encoder0PinB,             INPUT);     // 

  //-----------------------------------------------------
  pinMode (TX_Dit,                   INPUT);     // Dit Key line 
  pinMode (TX_Dah,                   INPUT);     // Dah Key line
  pinMode (TX_OUT,                   OUTPUT);    // control line for TX stuff
  pinMode (Band_End_Flash_led,       OUTPUT);    // line that flashes an led
  pinMode (PTT_SSB,                  INPUT);     // mic key has pull-up
  pinMode (SSB_CW,                   OUTPUT);    // control line for ssb cw switches

  pinMode (Multi_Function_Button,    INPUT);     // Choose from Band width, Step size, Other
  pinMode (Select_Button,            INPUT);     //  Selection from the above
  pinMode (Side_Tone,                OUTPUT);    // sidetone enable
  pinMode (Band_Select,              OUTPUT);
  pinMode (MUTE,                     OUTPUT);
  pinMode (MIC_LINE_MUTE,            OUTPUT);    // low on receive

  digitalWrite (Band_End_Flash_led,  LOW); 	 //  not in 81324
  digitalWrite (MUTE,                LOW);
  
  digitalWrite (TX_OUT,              LOW);                                            
  digitalWrite (Band_End_Flash_led,  LOW);
  digitalWrite (Side_Tone,           LOW);    
  digitalWrite (FREQ_REGISTER_BIT,   LOW);
  digitalWrite (SSB_CW,              LOW);
  digitalWrite (Band_Select,         LOW);
  digitalWrite (MUTE,                HIGH);
  digitalWrite (MIC_LINE_MUTE,       LOW);    //  receive mode

  // start the display with a welcome screen for 2 seconds
  lcd.begin(20, 4);                           // 20 chars 4 lines
  lcd.clear();                                // WD9GYM modification adjusted by W8CQD
  lcd.setCursor(0,0);
  lcd.print("-----------pam 1.2--");
  lcd.setCursor(0,1);
  lcd.print("  Ten-Tec  Patriot");
  lcd.setCursor(0,2);
  lcd.print("--------------------");

  #ifdef OLED
    // ADFRUIT OLED 128 x 32 
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    display.display();                          // show splashscreen (with correct Adafruit_SSD1306.cpp it will be the Ten-Tec logo)
  #endif
  delay(2000);
  
  // start Patriot at selected default band and mode
  old_bsm = bsm;          		      // needed to swith correct.
  if (bsm) frequency_default = frequency_20; else frequency_default = frequency_40; 	// change this to meter_20 for 20 meter default
  Change_Band();
  Default_frequency();
  if (bsm) old_bsm = 1; else old_bsm = 0;     // needed to swith correct.

  // initialize I2C stuff
  Wire.begin();                               // wake up I2C bus
  Wire.beginTransmission(0x20);  
  Wire.send(0x00);                            // IODIRA register
  Wire.send(0x00);                            // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(0x20);
  Wire.send(0x01);                            // IODIRB register
  Wire.send(0x00);                            // set all of port B to outputs
  Wire.endTransmission();

  Frequency_Step = 100;                       // Can change this whatever step size one wants
  Selected_Step = Step_100_Hz;

  // DDS
  AD9834_init();
  AD9834_reset();                             // low to high
 
  digitalWrite(FSYNC_BIT,            HIGH);   // 
  digitalWrite(SCLK_BIT,             HIGH);   // 

  encoder0PinALast = digitalRead(encoder0PinA);   
  attachCoreTimerService(TimerOverFlow);    //See function at the bottom of the file.

  // serial baudrate for K3 emulation at highist speed.
  Serial.begin(38400);

  keyerState   = IDLE;
  keyerControl = IAMBICB | PDLSWAP;
  checkWPM();                                // Set CW Speed based on A7 pot
 
  //See if user wants to use a straight key because is he pressing the straight key or the 3,5 mm jack is short
  if ((digitalRead(TX_Dah) == LOW) || (digitalRead(TX_Dit) == LOW)) {    //Is a lever pressed?
    ST_key = 1;        //If so, enter straight key mode  
  }

  Splash_MODE();

}   //    end of setup

//======================= Main Part =================================
void loop()    
{
  TX_routine(); 
  if (keyerState == IDLE && millis() - idletimer > 500) {  // no polling and user interaction allowed during cw keying
    if( !un_stage() ) Poll_Cat();                          // send data to CAT. If nothing to send, get next command.
    Encoder();
    RX_Rit();
    Multi_Function(); 

    loopElapsedTime    = millis() - loopStartTime;
    if( 1000 < loopElapsedTime )
    {
      if( !ST_key ) {  
        checkWPM();
        lcd.setCursor(10,3); 
        lcd.print(CWSpeed);
      } else {
        lcd.setCursor(10,3); 
        lcd.print("SK");
      } 
      if ( terminal ) Terminal_Refresh();
      loopStartTime = millis();                 // Reset Timer
    }
    writeSmeter();  //Add call to S Meter display routine WD9GYM/W8CQD
  }
}    //  END LOOP

//-----------------------------------------------------
void  RX_Rit()
{
  RIT_Read();
  frequency_tune  = frequency + RitFreqOffset; // RitFreqOffset is from Rit_Read();
  UpdateFreq(frequency_tune);
  splash_RX_freq();   // this only needs to be updated when encoder changed. 
}

//------------------------------------------------------
void RIT_Read()
{
  int RitReadValueNew =0 ;
  RitReadValueNew = analogRead(RitReadPin);

  RitReadValue = (RitReadValueNew + (12 * RitReadValue)) / 13;
  if(RitReadValue < 500) 
    RitFreqOffset = RitReadValue-500;
  else if(RitReadValue < 523) 
    RitFreqOffset = 0;		//Deadband in middle of pot
  else 
    RitFreqOffset = RitReadValue - 523;

  splash_RIT();    			//   comment out if display is not needed
}

//-----------------------------------------------------
void UpdateFreq(long freq)
{
  if (LastFreqWriteTime != 0)
  { 
    if ((millis() - LastFreqWriteTime) < 100) return; 
  }
  LastFreqWriteTime = millis();
  if(freq == frequency_old) return;
  program_freq0( freq );
  frequency_old = freq;
}

//--------------------------------------------------------------
void UpdateFreq1(long frequency_TX)
{
  if (LastFreqWriteTime != 0)
  { 
    if ((millis() - LastFreqWriteTime) < 100) return; 
  }
  LastFreqWriteTime = millis();
  if(frequency_TX == frequency_old_TX) return;
  program_freq1( frequency_TX );
  frequency_old_TX = frequency_TX;
}


void TX_on()
{
  TX_Frequency = frequency;
  frequency_tune  = TX_Frequency;             	// RitFreqOffset is from Rit_Read();
  digitalWrite ( FREQ_REGISTER_BIT,   HIGH);  	// 
  UpdateFreq1(frequency_tune);
        
  lcd.setCursor(13, 3);                        	// print the s meter on line 4
  lcd.print("T ###  ");                       	// blank out bars
          
  old_b = b;                                 	// save original b into old_b
  b = 0x00;                                   	// b is now set to wide filter setting
  Select_Multi_BW_Ored();                     	// b is sent to port expander ic
            
  if (mode==0) {
    digitalWrite ( MIC_LINE_MUTE, HIGH );       // turns Q35, Q16 off, unmutes mic/line
    digitalWrite ( SSB_CW, HIGH );            	// this causes the ALC line to connect
  } else {
    digitalWrite ( SSB_CW, LOW );               // enables the cw pull down circuit  
    digitalWrite ( Side_Tone, HIGH );           // enables side-tone source
    digitalWrite ( Band_End_Flash_led, HIGH );
  }
  digitalWrite ( TX_OUT, HIGH );              	// Truns on Q199 (pwr cntrl)(switched lo/dds)
}

void TX_off() {
  b = old_b;                                  	// original b is now restored
  Select_Multi_BW_Ored();                     	// original b is sent to port expander
         
  digitalWrite ( TX_OUT, LOW );               	// turn off TX stuff
  digitalWrite ( FREQ_REGISTER_BIT, LOW );    	// added 6/23/14  
  if (mode==0) { digitalWrite ( MIC_LINE_MUTE, LOW ); }        // turns Q36, Q16 on, mutes mic/line
  if (mode==1) { digitalWrite ( Side_Tone, LOW ); }            // side-tone off
  if (mode==1) { digitalWrite ( Band_End_Flash_led, LOW ); }

}

//---------------------  TX Routine  -------------------------------
void TX_routine()      
{  //------------------  SSB Portion  ----------------------------
   PTT_SSB_Key = digitalRead( PTT_SSB );              // check to see if PTT is pressed, 
   if   ( PTT_SSB_Key == LOW  )                       // if pressed do the following
    {
      do
        { 
          if (mode == 1) { mode=0; frequency_old=0; UpdateFreq(frequency_tune); Splash_MODE(); }                                
          TX_on();
          
          PTT_SSB_Key = digitalRead(PTT_SSB);         // check to see if PTT is pressed  
        } while ( PTT_SSB_Key == LOW ); 
          TX_off();
}  // End of SSB TX routine
      //---------------  CW Portion  --------------------------------
    if ( ST_key ) {                                    // is ST_Key is set to YES? Then use Straight key mode
    TX_key = digitalRead(TX_Dit);                      //  Maybe put these on an interrupt!
     if ( TX_key == LOW )                              // was high   
     {
       do
       {
         if (mode == 0) { mode=1; frequency_old=0; UpdateFreq(frequency_tune); Splash_MODE(); }     
         TX_on();
          
         TX_key = digitalRead(TX_Dit);                // reads dit key line
       } while (TX_key == LOW);                       // key still down
         TX_off();
     }
   } 
   else
   {                                                  //If ST_key is not 1, then use IAMBIC
    static long ktimer;
    // Basic Iambic Keyer
    // keyerControl contains processing flags and keyer mode bits
    // Supports Iambic A and B
    // State machine based, uses calls to millis() for timing.
    // Code adapted from openqrp.org
    switch (keyerState) {
    case IDLE:
        // Wait for direct or latched paddle press
        if ((digitalRead(TX_Dit) == LOW) || (digitalRead(TX_Dah) == LOW) || (keyerControl & 0x03)) {
            update_PaddleLatch();
            keyerState = CHK_DIT;
        }
        break;

    case CHK_DIT:
        // See if the dit paddle was pressed
        if (keyerControl & DIT_L) {
            keyerControl |= DIT_PROC;
            ktimer = ditTime;
            keyerState = KEYED_PREP;
        }
        else {
            keyerState = CHK_DAH;
        }
        break;
        
    case CHK_DAH:
        // See if dah paddle was pressed
        if (keyerControl & DAH_L) {
            ktimer = ditTime*3;
            keyerState = KEYED_PREP;
        }
        else {
            keyerState = IDLE;
                idletimer = millis();     // Set timer to keep CW clean
        }
        break;
        
    case KEYED_PREP:
        // Assert key down, start timing, state shared for dit or dah
        if (mode == 0) { mode=1; frequency_old=0; UpdateFreq(frequency_tune); Splash_MODE(); }                                
        TX_on();
        ktimer += millis();                   // set ktimer to interval end time
        keyerControl &= ~(DIT_L + DAH_L);     // clear both paddle latch bits
        keyerState = KEYED;                   // next state
        //loopStartTime = millis();         // Reset display Timer to keep CW clean
        //smeterLast = millis();       // Reset smeter Timer to keep CW clean
        break;
        
    case KEYED:
        // Wait for timer to expire
        if (millis() > ktimer) {              // are we at end of key down ?
          TX_off();
          ktimer = millis() + ditTime;      // inter-element time
          keyerState = INTER_ELEMENT;       // next state
          //loopStartTime = millis();         // Reset display Timer to keep CW clean
          //smeterLast = millis();       // Reset smeter Timer to keep CW clean
        }
        else if (keyerControl & IAMBICB) {
          update_PaddleLatch();             // early paddle latch in Iambic B mode
        }
        break; 
 
    case INTER_ELEMENT:
        // Insert time between dits/dahs
        update_PaddleLatch();                 // latch paddle state
        if (millis() > ktimer) {              // are we at end of inter-space ?
            if (keyerControl & DIT_PROC) {    // was it a dit or dah ?
                keyerControl &= ~(DIT_L + DIT_PROC);   // clear two bits
                keyerState = CHK_DAH;         // dit done, check for dah
            }
            else {
                keyerControl &= ~(DAH_L);     // clear dah latch
                keyerState = IDLE;            // go idle
                idletimer = millis();     // Set timer to keep CW clean
            }
        }
        break;
    }
  }
}
// end of TX_routine()

//    Latch dit and/or dah press, called by de keyer routine and checking PDLSWAP!
void update_PaddleLatch(){
  if (digitalRead(TX_Dit) == LOW) {
      if (keyerControl & PDLSWAP) keyerControl |= DAH_L; else keyerControl |= DIT_L;
  }
  if (digitalRead(TX_Dah) == LOW) {
      if (keyerControl & PDLSWAP) keyerControl |= DIT_L; else keyerControl |= DAH_L;
  }
}

// Calculate new time constants based on wpm value
void loadWPM(int wpm){
  ditTime = 1200/(wpm+3);              // correction factor = 3
}

// Checks the Keyer speed Pot and updates value 
void checkWPM(){
  CWSpeedReadValue = analogRead(CWSpeedReadPin);
  CWSpeedReadValue = map(CWSpeedReadValue, 0, 1024, 5, 45);
  loadWPM(CWSpeedReadValue);
  CWSpeed = CWSpeedReadValue;
}

// More then 0.5 second SELECT is Freq Announce
void announce(char *str){
  while (*str) 
    key_announce(*str++); 
}

void beep(int LENGTH) {
  digitalWrite(Side_Tone, HIGH);
  digitalWrite(Band_End_Flash_led, HIGH);
  delay(LENGTH);
  for (int i=0; i <= 10e3; i++);       // delay to equel with TX speed
  digitalWrite(Side_Tone, LOW);
  digitalWrite(Band_End_Flash_led, LOW);
  delay(ditTime) ;
}

void key_announce(char c){
  for (int i=0; i<N_MORSE; i++) {
    if (morsetab[i].c == c) {
      unsigned char p = morsetab[i].pat ;
      while (p != 1) {
        if (p & 1)
          beep(ditTime*3) ;
        else
          beep(ditTime) ;
          p = p / 2 ;
      }
      delay(ditTime*3) ;
      return ;
      }
  }
}

//------------------------CAT Routine based on Elecraft K3 -------------------------------
//   some general routines for serial printing

int un_stage(){              // send a char on serial 
char c;
   if( stg_in == stg_out ) return 0;
   c = stg_buf[stg_out++];
   stg_out &= ( STQUESIZE - 1);
   Serial.write(c);
   return 1;
}
void stage( unsigned char c ){
  stg_buf[stg_in++] = c;
  stg_in &= ( STQUESIZE - 1 );
}
void stage_str( String st ){
int i;
char c;
  for( i = 0; i < st.length(); ++i ){
     c= st.charAt( i );
     stage(c);
  }    
}
void stage_num( int val ){   // send number in ascii 
char buf[12];
char c;
int i;
   itoa( val, buf, 10 );
   i= 0;
   while( c = buf[i++] ) stage(c);  
}

void Poll_Cat() {
static String command = "";
String lcommand;
char c;
int rit;

    if (Serial.available() == 0) return;
    
    while( Serial.available() ){
       c = Serial.read();
       command += c;
       if( c == ';' ) break;
    }
    
    if( c != ';' ) { terminal = 0; return; }   // command not complete yet but need to switch of terminal
  
    lcommand = command.substring(0,2);
 
    if( command.substring(2,3) == ";" || command.substring(2,4) == "$;" || command.substring(0,2) == "RV" ){      /* it is a get command */
      stage_str(lcommand);    // echo the command 
      if( command.substring(2,3) == "$") stage('$');
      
      if (lcommand == "IF") {
        RX_frequency = frequency_tune - IF;
        stage_str("000");
        if( RX_frequency < 10000000 ) stage('0');
        stage_num(RX_frequency);  
        stage_str("     ");
        rit= RitFreqOffset;
        if( rit >= 0 ) stage_str("+0");
        else{
          stage_str("-0"); 
          rit = - rit;
        }
        if( rit < 100 ) stage('0');
        if( rit < 10 ) stage('0');                                  // IF[f]*****+yyyyrx*00tmvspbd1*;
        stage_num(rit);
        stage_str("10 0003000001");                                 // rit,xit,xmit,cw mode fixed filed 
      }
      else if(lcommand == "FA") {                                   // VFO A
        stage_str("000"); 
        if( frequency_tune -IF < 10000000 ) stage('0');  
        stage_num(frequency_tune - IF);  
      } 
      else if(lcommand == "KS") stage_num(CWSpeed);                // KEYER SPEED
      else if(lcommand == "FW") stage_str("0000") , stage_num(Selected_BW+1);
      else if(lcommand == "MD") { if (mode==0 && bsm==0) stage('1'); if (mode==0 && bsm==1) stage('2'); if (mode==1) stage ('3'); }                        // Mode       
      else if(lcommand == "RV" && command.substring(2,3) == "F"){  // battery voltage in Front field 
        stage(command.charAt(2));
        double value = analogRead(BatteryReadPin)* BatteryVconvert;
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
      else if(lcommand == "RV" && command.substring(2,3) == "A"){  // Rebel Alliance Mod version in Aux: field
        stage(command.charAt(2));
        stage_str(txt0);
      }
      else if(lcommand == "RV" && command.substring(2,3) == "D"){  // Rebel Alliance Mod in DSP: field   
        stage(command.charAt(2));
        stage_str(txt2);
      }
      else if(lcommand == "RV" && command.substring(2,3) == "M"){  // Keyer Speed in MCU: field
        stage(command.charAt(2));
        stage_num(CWSpeed);
      }
      else if(lcommand == "RV" && command.substring(2,3) == "R"){  // Keyer Speed in MCU: field
        stage(command.charAt(2));
        stage_str(steptext[Selected_Step]);
      }
      else if(lcommand == "SM"){
        stage_str("00");
        SmeterReadValue = analogRead(SmeterReadPin);
        SmeterReadValue = map(SmeterReadValue, 0, 1023, 0, 21);
        if( SmeterReadValue < 10 ) stage('0');
        stage_num(SmeterReadValue);
      }   
      else {
        stage('0');   // send back nill command not know / used
      }
    stage(';');       // response terminator 
    }
 
    else  {} set_cat(lcommand,command);    // else it's a set command 
   
    command = "";   // clear for next command
}

void set_cat(String lcom, String com ){
long value;
int split =0 ;
 
    if( lcom == "FA" ){    // set vfo freq 
      value = com.substring(2,13).toInt(); 
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
        if( lcom == "FA" && ( value > 1800000 && value < 30000000) ) frequency = value + IF;
        }
    }
    else if( lcom == "FW" ){             // xtal filter select
      value = com.charAt(6) - '0';
      if( value < 4 && value != 0 ){
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
    else if ( lcom == "MD" ){
      value = com.charAt(2) - '0';
      if ( value == 1 || value == 2) { mode=0; frequency_old=0; UpdateFreq(frequency_tune); Splash_MODE(); }
      if ( value == 3) {  mode=1; frequency_old=0; UpdateFreq(frequency_tune); Splash_MODE(); }
     }
}

//--------------------------- Encoder Routine -----------------Dana KD0UTH ----  
void Frequency_down() {
        frequency = frequency - Frequency_Step;
        LastFreqDispTime = millis();
        if ( bsm == 1 ) { 
          Band_20_Limit(); 
        }
        else if ( bsm == 0 ) { 
          Band_40_Limit(); 
        }
}

void Frequency_up() {
        frequency = frequency + Frequency_Step;
        LastFreqDispTime = millis();
        if ( bsm == 1 ) { 
          Band_20_Limit(); 
        }
        else if ( bsm == 0 ) { 
          Band_40_Limit(); 
        }
}  

void EncoderStandard()  // original routine works
{  
  n = digitalRead(encoder0PinA);
  if ( encoder0PinALast != n)
  {
    if ((encoder0PinALast == LOW) && (n == HIGH)) 
    {
      if (digitalRead(encoder0PinB) == LOW) //  Frequency_down
      {      //encoder0Pos--;
        Frequency_down();
      } 
      else                                  //  Frequency_up
      {      //encoder0Pos++;
        Frequency_up();
      }
    } 
    encoder0PinALast = n;
  }
}

void Encoder()  // fast encoder routine
{  
    n = digitalRead(encoder0PinA);
    o = digitalRead(encoder0PinB);

    if ((encoder0PinALast == LOW) && (n == HIGH)) 
    {
        if (o == LOW) 
        {
            Frequency_down();    //encoder0Pos--;
        
        } else 
        {
            Frequency_up();       //encoder0Pos++;
        }
    } else if ((encoder0PinALast == HIGH) && (n == LOW))  
    {                                                     // now we get 36 steps/rev instead of 10
        if (o == HIGH)
        {
            Frequency_down();
        } else
        {
            Frequency_up();
        }
    } else if ((encoder0PinBLast == LOW) && (o == HIGH))
    {
        if (n == LOW)
        {
            Frequency_up();
        } else
        {
            Frequency_down();
        }
    } else if ((encoder0PinBLast == HIGH) && (o == LOW))
    {
        if (n == HIGH)
        {
            Frequency_up();
        } else
        {
            Frequency_down();
        }
    }
    encoder0PinALast = n;
    encoder0PinBLast = o;
}

//-------------------------------------------------------
void Change_Band()
{
  if ( bsm == 1 )                              //  select 40 or 20 meters 1 for 20 0 for 40
  { 
    digitalWrite(Band_Select, HIGH);
    IF = -IF_value;
    offset = -DDS_offset_value;
    CW_offset = -CW_offset_value;
  }
  else 
  { 
    digitalWrite(Band_Select, LOW);
    IF = IF_value;
    offset = DDS_offset_value;
    CW_offset = CW_offset_value;
  }
  Band_Set_40_20M();
  Splash_MODE();
  Selected_Other = bsm;
}

//------------------ Band Select ------------------------------------
void Band_Set_40_20M()
{
  if ( old_bsm != bsm)                          //  this helps 5/13/14
  {
    if ( bsm == 1 )                             //  select 40 or 20 meters 1 for 20 0 for 40
    { 
      frequency_40 = frequency;                 //  save and restore memorized frequency
      frequency_default = frequency_20;
    }
    else 
    { 
      frequency_20 = frequency;                 //  save and restore memorized frequency
      frequency_default = frequency_40; 
    }
    Default_frequency();                        //  set new frequency
  }
  old_bsm = bsm;                                //  this helps 5/13/14
}

//--------------------Default Frequency-----------------------------
void Default_frequency()
{
  frequency = frequency_default;
  UpdateFreq(frequency);
  splash_RX_freq(); 
}   //  end   Default_frequency

//-----------------------------------------------------
void  Band_40_Limit()
{
  if ( frequency >= 16.2e6 )
  { 
    frequency = 16.2e6;
    stop_led_on();    
  }
  else if ( frequency <= 16.0e6 )  
  { 
    frequency = 16.0e6;
    stop_led_on();
  }
  else { 
    stop_led_off(); 
  }
}

//-----------------------------------------------------  
void  Band_20_Limit()
{
  if ( frequency >= 5.35e6 )
  { 
    frequency = 5.35e6;
    stop_led_on();    
  }
  else if ( frequency <= 5.0e6 )  
  { 
    frequency = 5.0e6;
    stop_led_on();
  } 
  else { 
    stop_led_off(); 
  }
}

//-----------------------------------------------------  
void Step_Flash()
{
  stop_led_on();
  for (int i=0; i <= 25e3; i++); // short delay 
  stop_led_off();   
}

//-----------------------------------------------------
void stop_led_on()  //  band edge and flash
{
  digitalWrite(Band_End_Flash_led, HIGH);
}

//-----------------------------------------------------
void stop_led_off()
{
  digitalWrite(Band_End_Flash_led, LOW);
}

//===================================================================
void Multi_Function() //  pushbutton for BW, Step, Other
{ 
  // look into a skip rtoutine for this
  Step_Multi_Function_Button = digitalRead(Multi_Function_Button);
  if (Step_Multi_Function_Button == HIGH) 
  {   
       unsigned long time;
       unsigned long start_time;
       unsigned long long_time;
       long_time = millis();
       
       time = millis();
       while( digitalRead(Multi_Function_Button) == HIGH ){ 
         
         // function button is pressed longer then 0.5 seconds
         if ( (millis() - long_time) > 500 ) { 
           // tune
           old_mode=mode;
           mode=1; //cw
           TX_on();
           // wait for button release
           while( digitalRead(Multi_Function_Button) == HIGH ){ 
           }   
           TX_off();
           mode=old_mode;
           Splash_MODE();
           return;        
         } 
         start_time = time;
         while( (time - start_time) < 7) {
           time = millis();
         }
       } // Debounce end
    while( digitalRead(Multi_Function_Button) == HIGH ){ 
    }  // added for testing
    for (int i=0; i <= 150e3; i++); // short delay

    Step_Multi_Function_Button1 = Step_Multi_Function_Button1 + 1;
    if (Step_Multi_Function_Button1 > 2 ) 
    { 
      Step_Multi_Function_Button1 = 0; 
    }
  }
  Step_Function();
}  // end Multi_Function()

//================================================================== 
void Step_Function()
{
  if (keyerState == KEYED) return;   // don't change the bw while iambic active
  switch ( Step_Multi_Function_Button1 )
  {
  case 0:
    m = 0x08;   // GPA3(24) Controls Function Green led
    Select_Multi_BW_Ored();
    Step_Select_Button1 = Selected_BW; // 
    Step_Select(); //
    Selection();
    for (int i=0; i <= 255; i++); // short delay
    break;   //

  case 1:
    m = 0x10;   // GPA4(25) Controls Function Yellow led
    Select_Multi_BW_Ored();
    Step_Select_Button1 = Selected_Step; //
    Step_Select(); //
    Selection();
    for (int i=0; i <= 255; i++); // short delay
    break;   //

  case 2: 
    m = 0x20;   // GPA5(26) Controls Function Red led
    Select_Multi_BW_Ored();
    Step_Select_Button1 = Selected_Other; //
    Step_Select(); //
    Selection();
    for (int i=0; i <= 255; i++); // short delay
    break;   //  
  }
}  // end Step_Function()

//===================================================================
void  Selection()
{
    Step_Select_Button = digitalRead(Select_Button);
    if (Step_Select_Button == HIGH) 
    {   
       // Debounce start
       unsigned long time;
       unsigned long start_time;
       unsigned long long_time;
       long_time = millis();
       
       time = millis();
       while( digitalRead(Select_Button) == HIGH ){ 
         
         // function button is pressed longer then 0.5 seconds
         if ( (millis() - long_time) > 500 ) { 
           // announce frequency
           TX_frequency = (frequency_tune - IF)/100;
           char buffer[8];
           ltoa(TX_frequency, buffer, 10);
           announce(buffer);
           // wait for button release
           while( digitalRead(Select_Button) == HIGH ){ 
           }   
           return;        
         } 
         start_time = time;
         while( (time - start_time) < 7) {
           time = millis();
         }
       } // Debounce end
        Step_Select_Button1 = Step_Select_Button1 + 1;
        if (Step_Select_Button1 > 2 || (Step_Select_Button1 > 1 && Step_Multi_Function_Button1 == 2) ) 
        { 
            Step_Select_Button1 = 0; 
        }
    }
    Step_Select(); 
}

//-----------------------------------------------------------------------  
void Step_Select()
{
  switch ( Step_Select_Button1 )
  {
  case 0: //   Select_Green   
    s = 0x01;  // GPA0(21) Controls Selection Green led 
    if (Step_Multi_Function_Button1 == 0)
    {
      b = 0x00; // Hardware control of I.F. filter shape
      Selected_BW = Wide_BW;  // GPA7(28)LOW_GPA6(27)LOW wide
    } 
    else if (Step_Multi_Function_Button1 == 1)
    {
      Frequency_Step = 10;   //  Can change this whatever step size one wants
      Selected_Step = Step_10_Hz; 
    } 
    else if (Step_Multi_Function_Button1 == 2)
    {
      bsm = 0;
      Change_Band();
      Selected_Other = Other_1_user; 
      // Other_1();
    } 
    for (int i=0; i <= 255; i++); // short delay  
    break;

  case 1: //   Select_Yellow  
    s = 0x02;    //  GPA1(22) Controls Selection Green led
    if (Step_Multi_Function_Button1 == 0) 
    {
      b = 0x40; // Hardware control of I.F. filter shape
      Selected_BW = Medium_BW;  //  GPA7(28)LOW_GPA6(27)HIGH medium
    } 
    else if (Step_Multi_Function_Button1 == 1) 
    {
      Frequency_Step = 100;   //  Can change this whatever step size one wants
      Selected_Step = Step_100_Hz; 
    }
    else if (Step_Multi_Function_Button1 == 2) 
    {
      bsm = 1;
      Change_Band();
      Selected_Other = Other_2_user; 

      //   Other_2(); 
    }
    for (int i=0; i <= 255; i++); // short delay   
    break; 

  case 2: //   Select_Red    
    s = 0x04;    //  GPA2(23) Controls Selection Green led
    if (Step_Multi_Function_Button1 == 0) 
    {
      b = 0x80; // Hardware control of I.F. filter shape
      Selected_BW = Narrow_BW;   //  GPA7(28)HIGH_GPA6(27)LOW narrow
    } 
    else if (Step_Multi_Function_Button1 == 1) 
    {
      Frequency_Step = 1e3;    //  Can change this whatever step size one wants
      Selected_Step = Step_1000_Hz;
    }
    else if (Step_Multi_Function_Button1 == 2) 
    {
      Selected_Other = Other_3_user; 

      //       Other_3(); 
    }
    for (int i=0; i <= 255; i++); // short delay
    break;     
  }
  Select_Multi_BW_Ored();
  Splash_Step_Size();
  Splash_BW();
}  // end Step_Select()

//----------------------------------------------------------------------------------
void Select_Multi_BW_Ored()
{
  t = s | m | b ;    // or'ed bits

  Wire.beginTransmission(0x20);
  Wire.send(0x12); // GPIOA
  Wire.send(t); // port A  result of s, m, b
  Wire.endTransmission(); 

}  // end  Select_Multi_BW_Ored()

//-----------------------------------------------------------------------------
// ****************  Dont bother the code below  ******************************
// \/  \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/
//-----------------------------------------------------------------------------
void program_freq0(long frequency)
{
  AD9834_reset_high();  
  int flow,fhigh;
  fcalc = (frequency + (CW_offset*mode))*(268.435456e6 / (Reference + offset));    // 2^28 =
  flow = fcalc&0x3fff;              //  49.99975mhz  
  fhigh = (fcalc>>14)&0x3fff;
  digitalWrite(FSYNC_BIT, LOW);  //
  clock_data_to_ad9834(flow|AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(fhigh|AD9834_FREQ0_REGISTER_SELECT_BIT);
  digitalWrite(FSYNC_BIT, HIGH);
  AD9834_reset_low();
}    // end   program_freq0

//------------------------------------------------------------------------------

void program_freq1(long frequency_TX)
{
  AD9834_reset_high(); 
  int flow,fhigh;
  fcalc = frequency*(268.435456e6 / (Reference + offset));    // 2^28 =
  flow = fcalc&0x3fff;              //  use for 49.99975mhz   
  fhigh = (fcalc>>14)&0x3fff;
  digitalWrite(FSYNC_BIT, LOW);  
  clock_data_to_ad9834(flow|AD9834_FREQ1_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(fhigh|AD9834_FREQ1_REGISTER_SELECT_BIT);
  digitalWrite(FSYNC_BIT, HIGH);  
  AD9834_reset_low();
}  

//------------------------------------------------------------------------------
void clock_data_to_ad9834(unsigned int data_word)
{
  char bcount;
  unsigned int iData;
  iData=data_word;
  digitalWrite(SCLK_BIT, HIGH);  //portb.SCLK_BIT = 1;  
  // make sure clock high - only chnage data when high
  for(bcount=0;bcount<16;bcount++)
  {
    if((iData & 0x8000)) digitalWrite(SDATA_BIT, HIGH);  //portb.SDATA_BIT = 1; 
    // test and set data bits
    else  digitalWrite(SDATA_BIT, LOW);  
    digitalWrite(SCLK_BIT, LOW);  
    digitalWrite(SCLK_BIT, HIGH);     
    // set clock high - only change data when high
    iData = iData<<1; // shift the word 1 bit to the left
  }  // end for
}      // end  clock_data_to_ad9834

//-----------------------------------------------------------------------------
void AD9834_init()      // set up registers
{
  AD9834_reset_high(); 
  digitalWrite(FSYNC_BIT, LOW);
  clock_data_to_ad9834(0x2300);  // Reset goes high to 0 the registers and enable the output to mid scale.
  clock_data_to_ad9834((FREQ0_INIT_VALUE&0x3fff)|AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(((FREQ0_INIT_VALUE>>14)&0x3fff)|AD9834_FREQ0_REGISTER_SELECT_BIT);
  clock_data_to_ad9834(0x2200); // reset goes low to enable the output.
  AD9834_reset_low();
  digitalWrite(FSYNC_BIT, HIGH);  
}  //  end   AD9834_init()

//----------------------------------------------------------------------------   
void AD9834_reset()
{
  digitalWrite(RESET_BIT, HIGH);  // hardware connection
  for (int i=0; i <= 2048; i++);  // small delay

  digitalWrite(RESET_BIT, LOW);   // hardware connection
}  // end AD9834_reset()

//-----------------------------------------------------------------------------
void AD9834_reset_low()
{
  digitalWrite(RESET_BIT, LOW);
}  // end AD9834_reset_low()

//..............................................................................     
void AD9834_reset_high()
{  
  digitalWrite(RESET_BIT, HIGH);
}  // end  AD9834_reset_high()

//^^^^^^^^^^^^^^^^^^^^^^^^^  DON'T BOTHER CODE ABOVE  ^^^^^^^^^^^^^^^^^^^^^^^^^ 
//=============================================================================

//------------------------Display Stuff below-----------------------------------

//------------------- Splash RIT -----------------------------------------------  
void splash_RIT()      // not used
{ 
  if ( old_RitFreqOffset != RitFreqOffset) // only if RIT changes
  { 
    lcd.setCursor(13, 1);
    lcd.print("     ");                       // spaces

    lcd.setCursor(13, 1); 
    stringRIT = String( RitFreqOffset, DEC);

    if (RitFreqOffset) lcd.print(stringRIT);
  }
  old_RitFreqOffset = RitFreqOffset;      // test for Rit change
}

//------------------------------------------------------------------------------
void splash_RX_freq()
{
  #ifdef OLED  
    if ((millis() - LastFreqDispTime) < 40)  return;      // OLED is slow and gives unpredicted results with the fast encoder routine
  #endif
  long RXD_frequency;   
  if ( old_frequency_tune != frequency_tune || forcedSplash )
  {
    RXD_frequency = frequency_tune - IF; 
    stringFREQ = String(RXD_frequency , DEC);
    lcd.setCursor(1, 1);    
    if (RXD_frequency > 10000000)
    {
    lcd.print("14." + stringFREQ.substring(2,5) + "."+ stringFREQ.substring(5,7)+"   ");
    }
    else  
    {
    lcd.print(" 7." + stringFREQ.substring(1,4) + "."+ stringFREQ.substring(4,6)+"   ");
    }  
    #ifdef OLED
      // OLED routine will displaty all settings and frequency in one go. This is because of the way the display works: the total display is updated at once
      // this display.display() command freezes the processor for some 10ths of milliseconds 
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(2);
      display.setCursor(0,0);
      if (RXD_frequency > 10000000)
      {
      display.print("14." + stringFREQ.substring(2,5) + "."+ stringFREQ.substring(5,7));
      }
      else  
      {
      display.print(" 7." + stringFREQ.substring(1,4) + "."+ stringFREQ.substring(4,6));
      }  
      if (RitFreqOffset > 0) display.print("+"); else if (RitFreqOffset < 0 ) display.print("-");
      display.setTextSize(1);
      display.setCursor(0,25);
      if ( !ST_key )  display.print(bwtext[Selected_BW] + " " + steptext[Selected_Step] + " " + modetext[((mode*2)+bsm)] + " " + CWSpeed + " S ");
      if ( ST_key )   display.print(bwtext[Selected_BW] + " " + steptext[Selected_Step] + " " + modetext[((mode*2)+bsm)] + " SK S ");
      if (level > 40) display.print("=");
      if (level > 30) display.print("=");
      if (level > 20) display.print("=");
      if (level > 10)  display.print("=");
      if (level > 7)  display.print("=");
      if (level > 5)  display.print("=");
      display.display();
    #endif
  }
  old_frequency_tune = frequency_tune;
  #ifdef OLED  
    forcedSplash=0;
  #endif
}

//-----------------------------------------------------------------

void Splash_Step_Size()
{   if (old_Selected_Step == Selected_Step) return;
    lcd.setCursor(2, 3);
    lcd.print(steptext[Selected_Step]);
    old_Selected_Step = Selected_Step;
    #ifdef OLED  
      forcedSplash=1;
    #endif
}
//--------------------------------------------------------------------
void Splash_BW()
{   if (old_Selected_BW == Selected_BW) return;
    lcd.setCursor(0, 3);
    lcd.print(bwtext[Selected_BW]);
    old_Selected_BW = Selected_BW;
    #ifdef OLED  
      forcedSplash=1;
    #endif
}

//--------------------------------------------------------------------
void Splash_MODE()
{   
    lcd.setCursor(6, 3);
    lcd.print(modetext[((mode*2)+bsm)]);
    #ifdef OLED  
      forcedSplash=1;
    #endif
}

//-----------------------------------------------------------------------------
uint32_t TimerOverFlow(uint32_t currentTime)
{
  return (currentTime + CORE_TICK_RATE*(1));//the Core Tick Rate is 1ms
}

// ==========================================================================================================================================
void writeSmeter()                 // WD9GYM modification - adjusted by W8CQD
{
  smeterTime = millis(); // grab current time
  smeterInterval = smeterTime - smeterLast; // calculate interval between this and last event

    if (smeterInterval > 200) // ignore checks less than 200mS after initial edge
  {

    SmeterReadValue = analogRead(SmeterReadPin);   // read value of signal 0 - 1023
    level = map(SmeterReadValue, 0, 1023, 0, 41);    // constrain the value into db 0 - 40

    lcd.setCursor(13, 3);                      // print the s meter on line 4
    lcd.print("S      ");                      // blank out bars

    if (level > 30) level = 40;
    if (level > 20 && level < 31) level = 30;
    if (level > 10 && level < 21) level = 20;
    if (level > 7 && level < 10) level = 9;
    if (level > 5 && level < 8) level = 7;
    if (level > 3 && level < 6) level = 5;
    if (level > 1 && level < 4) level = 3;
    if (level > 0 && level < 2) level = 1;
    switch( level ){                           // write each bar required
    case 40:                                   // do not put break between case statements
      lcd.createChar(4, meter_s30);            // let the code fall through
      lcd.setCursor(19,3); 
      lcd.write( 4 );
    case 30: 
      lcd.createChar(4, meter_s30);
    case 20: 
      if( level == 20 ) lcd.createChar(4, meter_s20); 
      lcd.setCursor(18,3); 
      lcd.write( 4 );
    case 10: 
      lcd.createChar(3, meter_s10);
    case 9: 
      if( level == 9 ) lcd.createChar(3, meter_s9); 
      lcd.setCursor(17,3); 
      lcd.write( 3 );
    case 7: 
      lcd.createChar(2, meter_s7);
    case 5: 
      if( level == 5 ) lcd.createChar(2, meter_s5); 
      lcd.setCursor(16,3); 
      lcd.write( 2 );
    case 3: 
      lcd.createChar(1, meter_s3);
    case 1: 
      if( level == 1 ) lcd.createChar(1, meter_s1); 
      lcd.setCursor(15,3); 
      lcd.write( 1 );
    case 0:
    default: 
      break;
    }
    smeterLast = smeterTime; // set up for next event
    #ifdef OLED  
      forcedSplash=1;
    #endif
  }

}

//Terminal output
void Terminal_Refresh()
{
  if ( terminal ) {
    Serial.print("\e[1;1H\e[2J");                      // Cursor to 1,1 left top corner

    // 1st Line frequency and RIT or Message
    RX_frequency = frequency_tune - IF;
    Serial.print(RX_frequency * 0.001);
    Serial.print(" RIT ");
    //RIT 
    Serial.print(RitFreqOffset);
    Serial.println();
    // 2nd line, BW, STEP, MODE, SPEED
    if ( !ST_key )  Serial.print(bwtext[Selected_BW] + " " + steptext[Selected_Step] + " " + modetext[((mode*2)+bsm)] + " " + CWSpeed + " S " + level);
    if ( ST_key )   Serial.print(bwtext[Selected_BW] + " " + steptext[Selected_Step] + " " + modetext[((mode*2)+bsm)] + " SK S " + level);

  }
}


