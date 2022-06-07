// Patriot_507_Ver_1_10_Release_K2FXZ_V_3S
// F_Zia, K2FXZ, 2022_0514
// Dependencies:
// Install chipKit Uno32 core for Arduino IDE
// https://chipkit.net/wiki/index.php/How-To_Install_chipKIT_Core
// Install LiquidCrystal_I2C library
// included in TT507...zip file
// LCD: replace BATT > VOPK
// LCD: swap    VOPK   MODE

// Patriot_507_Ver_1_10_Release_K2FZZ_V_2S
// F_Zia, K2FZZ
// 2021_0606: Segmented Code into function files for easy update
// 2021_0619: added BATTery measurement on power-On splash screen
// 2021_0620: added VOPK (Vout Peak measurement) instead of BATT on LCD
//            PowerOutReadPin = A3; // Reads RF out voltage at Antenna
//            added Splash_Pout_Vpeak()

// Patriot_507_Ver_1_10_Release_K2FZZ_V_1
// F_Zia, K2FZZ, 2021_0525
// Added  LCD I2C 0x3F 20x4
// L/R Justified LCD Text

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
   Program for the ChipKit Uno32
   This is a simple program to demonstrate a 2 band QRP Amateur Radio Transceiver
   Amateur Programmer Bill Curb (WA4CDM).
   This program will need to be cleaned up a bit and no doubt be made more efficient!
   Compiled using the MPIDE for the ChipKit Uno32.

   Prog for ad9834
   Serial timming setup for AD9834 DDS
   start > Fsync is high (1), Sclk taken high (1), Data is stable (0, or 1),
   Fsync is taken low (0), Sclk is taken low (0), then high (1), data changes
   Sclk starts again.
   Control Register D15, D14 = 00, D13(B28) = 1, D12(HLB) = X,
   Reset goes high to set the internal reg to 0 and sets the output to midscale.
   Reset is then taken low to enable output.
 ***************************************************
   This is real basic code to get things working.
 *****************************************************************
   The pinout for the LCD is as follows: Also the LCD is setup up for 4 lines 20 charactors.
   LCD RS pin to digital pin 26
   LCD Enable pin to digital pin 27
   LCD D4 pin to digital pin 28
   LCD D5 pin to digital pin 29
   LCD D6 pin to digital pin 30
   LCD D7 pin to digital pin 31
   LCD R/W pin to ground
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)    analogWrite(Side_Tone, 127);
 *****************************************************************
   SELECT button steps from in
   BW ( <Wide, green>, <Medium, yellow>, <Narrow, red> ).
   STEP ( <100 hz, green, <1Khz, yellow>, 10Khz, red> ).
   BND ( < 40M >, < 20M >, < , > ) OTHER has yet to be defined

   Default Band_width will be wide ( Green led lite ).
   When pressing the function button one of three leds will lite.
   as explained above the select button will choose which setting will be used.
   The Orange led in the Ten-Tec logo will flash to each step the STEP is set
   too when tuning.  As it will also turn on when at the BAND edges.
   The TT logo led will also flash to indicate ALC. Input levels should be kept low enough
   to only flash this led on Peaks.
   Default frequency on power up will be the calling frequency of the
   40 meter band.
   I.F. Frequency used is 9.0 mhz.
   DDS Range is:
   40 meters will use HI side injection.
   9(I.F.) + 7(40m) = 16mhz.  9(I.F.) + 7.30 = 16.3 mhz.
   20 meters will use LO side injection.
   14(20m) - 9(I.F.) = 5mhz.  14.350(20m) - 9(I.F.) = 5.35 mhz.

   The Headphone jack can supply a headphone or speaker. The header pins(2)
   if shorted will drive a speaker.
   Unshorted inserts 100 ohm resistors in series with the headphone to limit
   the level to the headphones.

   The RIT knob will be at 0 offset in the Top Dead Center position. And will
   go about -500 hz to +500 hz when turned to either extreme. Total range
   about +/- 500 hz. This may change!

 **************************************************************************************

   Added an MCP23017 16-bit I/O Expander with Serial Interface to free up
   some I/O pins on the ChipKit Uno32 board.
   The parts of the 507 being controlled by this ic will be the Multi-purpose
   leds, the Select leds and the Wide/medium/Narrow control.
   5/1/2014 added a couple of routines to keep the filter wide on TX of SSB or CW
   Port B can be used by the user for external control.

   GPAO (21) Select Green led
   GPA1 (22) Select Yellow led
   GPA2 (23) Select Red led
   GPA3 (24) MP_A Green led
   GPA4 (25) MP_B Yellow led
   GPA5 (26) MP_C Red led
   GPA6 (27) Medium A8 BW_control
   GPA7 (28) Narrow A9 BW_control

   A mask function will be used to combine the various bits together.
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

#define led                                 13
#define MUTE                                4
#define MIC_LINE_MUTE                       34

#define Side_Tone                           3           // 

#define PTT_SSB                             22          // ptt input pulled high 
#define SSB_CW                              42          // control line for /SSB_CW switches output
// high for cw , low for ssb
#define TX_Dah                              33          // 
#define TX_Dit                              32          //  
#define TX_OUT                              38          //  
#define Band_End_Flash_led                  24          // // also this led will flash every 100/1khz/10khz is tuned
#define Band_Select                         41          // output for band select
#define Multi_Function_Button               5           //
#define Flash                               Band_End_Flash_led

#define Select_Button                       2           // 

#define Wide_BW                             0           // 
#define Medium_BW                           1           // 
#define Narrow_BW                           2           // 


#define Step_100_Hz                         0
#define Step_1000_hz                        1
#define Step_10000_hz                       2

#define  Other_1_user                       0           // 40 meters
#define  Other_2_user                       1           // 20 meters
#define  Other_3_user                       2           // anything you desire!

const int RitReadPin        = A0;  // pin that the sensor is attached to used for a rit routine later.
int RitReadValue            = 0;
int RitFreqOffset           = 0;
int old_RitFreqOffset       = 0;

const int SmeterReadPin     = A1;  // To give a relative signal strength based on AGC voltage.
int SmeterReadValue         = 0;

const int BatteryReadPin    = A2;  // Reads 1/5 th or 0.20 of supply voltage.
int BatteryReadValue        = 0;

const int PowerOutReadPin   = A3;  // Reads RF out voltage at Antenna.
int PowerOutReadValue       = 0;

const int CodeReadPin       = A6;  // Can be used to decode CW.
int CodeReadValue           = 0;

const int CWSpeedReadPin    = A7;  // To adjust CW speed for user written keyer.
int CWSpeedReadValue        = 0;

#include "Wire.h"
// #include <LiquidCrystal.h>                 // 4-bit LCD Stuff
// LiquidCrystal lcd(26, 27, 28, 29, 30, 31); // 4-bit LCD Stuff

// F_Zia, K2FZZ, 2021_0525
// Added  LCD I2C 20x4
#include <LiquidCrystal_I2C.h> //  LCD I2C Address: 0x3F Size: 20x4
LiquidCrystal_I2C lcd(0x3F, 20, 4);

const char txt52[5]         = " ";
const char txt57[6]         = "FREQ:" ;
const char txt60[6]         = "STEP:";
const char txt62[3]         = "RX";
const char txt63[3]         = "TX";
const char txt64[4]         = "RIT";
const char txt65[5]         = "BAND"; // F_Zia 2021_0525 Band > BAND
const char txt66[4]         = "20M";
const char txt67[4]         = "40M";
const char txt69[4]         = "   ";
const char txt70[5]         = "    ";
const char txt71[6]         = "     ";
const char txt72[10]        = "        ";
const char txt85[2]         = "W";
const char txt86[2]         = "M";
const char txt87[2]         = "N";
const char txt90[5]         = "STEP";
//const char txt110[5]        = "BATT"; // F_Zia 2021_0525 BAT > BATT
const char txt110[5]        = "VOPK"; // F_Zia 2022_0514 BATT > VOPK (Vout Peak)
const char txt120[3]        = "BW";
const char txt130[5]        = "MODE";
const char txt132[3]        = "CW";
const char txt135[4]        = "SSB";
const char txt140[9]        = "    WIDE"; // F_Zia 2021_0525 "    WIDE"
const char txt150[9]        = "  MEDIUM"; // F_Zia 2021_0525 "  MEDIUM"
const char txt160[9]        = "  NARROW"; // F_Zia 2021_0525 "  NARROW"
const char txt170[9]        = "        ";

String stringFREQ;
String stringREF;
String string_Frequency_Step;
String stringRIT;
String stringVolts;
String stringBW;

int TX_key;
int PTT_SSB_Key;
int old_PTT_SSB_Key;

int band_sel;                           // select band 40 or 20 meter
int band_set;
int bsm;

int Step_Select_Button          = 0;
int Step_Select_Button1         = 0;
int Step_Multi_Function_Button  = 0;
int Step_Multi_Function_Button1 = 0;
int Selected_BW                 = 0;    // current Band width
// 0= wide, 1 = medium, 2= narrow
int Selected_Step               = 0;    // Current Step
int Selected_Other              = 0;    // To be used for anything

int old_bsm                     = 0;    // this helps 5/13/14

int old_BatteryReadValue        = 0;

byte s = 0x00;                    // s = select
byte m = 0x00;                    // m = multi
byte b = 0x00;                    // b = bandwidth
byte t = 0x00;                    // s + m ored
byte old_b = 0x00;                // for the TX routine

//-----------------------------------------------------
// Encoder Stuff
const int encoder0PinA          = 6; // reversed for 507
const int encoder0PinB          = 7; // reversed for 507

int val;
int encoder0Pos                 = 0;
int encoder0PinALast            = LOW;
int n                           = LOW;

//-----------------------------------------------------
// K2FXZ 2022_0522, changed power on default freqs to FT8 freqs and tweak Reference

//const long meter_40             = 16.285e6; // Band frequency + IF, default for 40
const long meter_40             = 16.074e6; // Band frequency + IF, default for 40
                                            // HI  side injection 40 meter
                                            // range 16 > 16.3 mhz
//const long meter_20             = 5.285e6;  // Band frequency - IF, default for 20
const long meter_20             = 5.074e6;  // Band frequency - IF, default for 20
                                            // LOW side injection 20 meter
                                            // range 5 > 5.35 mhz
//const long Reference            = 50.0e6;   // for ad9834 this may be
const long Reference            = 49.999700e6;   // for ad9834 this may be
                                            // tweaked in software to
long frequency_TX;                          // fine tune the Radio
long TX_frequency;
long RIT_frequency;
long RX_frequency;
long save_rec_frequency;
long Frequency_Step;
long old_Frequency_Step;
long frequency                  = 0;
long frequency_old              = 0;
long frequency_old_TX           = 0;
long frequency_tune             = 0;
long old_frequency_tune         = 0;
long frequency_default          = 0;
long fcalc;
long IF                         = 9.00e6;   // IF (Intermediate Frequency)
long TX_Frequency               = 0;

//-----------------------------------------------------
// Debug Stuff

unsigned long   loopCount       = 0;
unsigned long   lastLoopCount   = 0;
unsigned long   loopsPerSecond  = 0;
unsigned int    printCount      = 0;

unsigned long   loopStartTime   = 0;
unsigned long   loopElapsedTime = 0;
float           loopSpeed       = 0;

unsigned long LastFreqWriteTime = 0;

void    serialDump();

//-----------------------------------------------------

void Default_frequency();
void AD9834_init();
void AD9834_reset();
void program_freq0(long freq);
void program_freq1(long freq1);
void UpdateFreq(long freq);

void RX_Rit();

//   void Frequency_up();
//   void Frequency_down();


void TX_routine();
void RX_routine();
void Encoder();
void AD9834_reset_low();
void AD9834_reset_high();

void Change_Band();
void Step_Flash();
void RIT_Read();

void Multi_Function();          //
void Step_Selection();          //
void Selection();               //
void Step_Multi_Function();     //

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

  digitalWrite (Band_End_Flash_led,  LOW);       // not in 81324

  digitalWrite (MUTE,                LOW);


  BatteryReadValue = analogRead(BatteryReadPin);

  Default_Settings();
  // I2C stuff
  Wire.begin();                             // wake up I2C bus
  Wire.beginTransmission(0x20);
  Wire.send(0x00);                          // IODIRA register
  Wire.send(0x00);                          // set all of port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(0x20);
  Wire.send(0x01);                          // IODIRB register
  Wire.send(0x00);                          // set all of port B to outputs
  Wire.endTransmission();

  //-----------------------------------------------------
  // DDS
  AD9834_init();
  AD9834_reset();                            // low to high
  //-----------------------------------------------------

  digitalWrite(TX_OUT,              LOW);    // turn off TX
  digitalWrite(SSB_CW,              LOW);    // keeps tx in ssb mode until high

  //-----------------------------------------------------
  Frequency_Step = 100;   //  Can change this whatever step size one wants
  Selected_Step = Step_100_Hz;
  DDS_Setup();
  encoder0PinALast = digitalRead(encoder0PinA);
  //attachInterrupt(encoder0PinA, Encoder, CHANGE);
  //attachInterrupt(encoder0PinB, Encoder, CHANGE);
  attachCoreTimerService(TimerOverFlow); //See function at the bottom of the file

  Serial.begin(115200);
  Serial.println("Patriot Ready:");

  lcd.begin(20, 4);                    // 20 chars 4 lines
  // or change to suit ones lcd display
  // turn on LCD backlight, F_Zia 2021_0525
  lcd.backlight();

  // display power-on message on LCD, F_Zia 2021_0619
  lcd.setCursor(0, 0);
  lcd.print("TT-Patriot Ready");

  BatteryReadValue = analogRead(BatteryReadPin);
  lcd.setCursor(0, 1);
  lcd.print("PS (mV) ");
  lcd.print(BatteryReadValue << 4);
  delay(5000);
  lcd.clear();
  
  Display_Setup();

} //    end of setup

//===================================================================

//======================= Main Part =================================
void loop()
{
  //  TX_routine();
  Encoder();
  TX_routine();
  RX_Rit();
  Multi_Function();

  loopCount++;
  loopElapsedTime    = millis() - loopStartTime;

  if ( 1000 <= loopElapsedTime )
  {
    serialDump();    // comment this out to remove the one second tick
  }
}    //  END LOOP
