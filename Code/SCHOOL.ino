/* ΠΡΟΓΡΑΜΜΑ ΕΛΕΓΧΟΥ ΠΟΙΟΤΗΤΑΣ ΤΑΞΗΣ
   ΙΑΝΟΥΑΡΙΟΣ - ΑΠΡΙΛΙΟΣ 2019

   Ελέγχουμε διάφορες μετρήσεις και βαθμολογούμε ανάλογα
   Ο κάθε αισθητήρας δίνει πράσινο, κίτρινο, ή κόκκινο ανάλογα με προκαθορισμένα όρια
   ΟΛΟΙ οι αισθητήρες μαζί, δίνουν ένα βαθμό πράσινο, κίτρινο, ή κόκκινο

   Χρησιμοποιούμε τους παρακάτω αισθητήρες


   DHT11 - Temperature : παράδειγμα από samples τιμών 25,26,27
   DHT11 - Humidity :  samples 34,33,28
   MQ135 Air qlt : samples 250,270,290
   BH1750 Light Sensor : samples 600,700,800
   Sparkfun Electret microphone: samples 500-700
   KY-013 - Analog Temp: samples 25,26,27

  ΑΞΙΟΛΟΓΗΣΗ ΓΙΑ ΠΡΑΣΙΝΟ/ΚΙΤΡΙΝΟ/ΚΟΚΚΙΝΟ ΒΑΘΜΟ
  θέτουμε *εμείς* τα παρακάτω επίπεδα αξιολόγησης

  -   3 λεπτά ανοχή στην μία ώρα για τις κακές μετρήσεις (κόκκινο) = 5% του χρόνου.
  -  12 λεπτά ανοχή στην μία ώρα για τις μέτριες μετρήσεις (κίτρινο) = 20% του χρόνου.
  -  45 λεπτά ανοχή στην μία ώρα για της καλές (πράσινο) = 75% του χρόνου.
  ΩΡΑ ΕΝΝΟΕΙΤΑΙ 60 ΛΕΠΤΑ ΚΑΙ ΟΧΙ 45


  Σε κάθε αισθητήρα ορίζουμε 5 ζώνες τιμών
   -- μία πράσινη
   -- δύο κίτρινες
   -- δύο κόκκινες. Περισσότερα στον κώδικα
*/

#include <LiquidCrystal.h>      // lcd screen
#include "globals.h"            // παράμετροι που χρησιμοποιούμε σε όλο το πρόγραμμα (globals)
LiquidCrystal lcd ( 8, 9, 4, 5, 6, 7 ); // select the pins used on the LCD panel


int lcd_button;                 //  which lcd button was presed
int which_button;               //ποιό κουμπί πατήθηκε από την lcd

float Hum, Temp1, Temp2;        //  humidity, temperature of DHT_11 and KY013 live measurements
uint16_t Light;                 //  light indensity  BH1750 live measurement
int Gas;                        //  CO2
unsigned int Sound;             //  sound live measurement

int i = 0;                    //η μεταβλητή που χρησιμοποιούμε σε ένα loop

char line0[16], line1[16];    // οι δύο σειρές της οθόνης

unsigned long Millis_Now, Millis_Lap_Disp, Millis_Lap_Read; //μετρητές χρόνου.Θέλουμε να αξιολογούμε την ποιότητα των μετρήσεων περιοδικά

void read_from_all_sensors() {
  //Τώρα παίρνουμε τις live μετρήσεις

  Sound = read_sound_100();
  Light = read_LIGHT();
  // Light = constrain ( Light, Limits_Light[0], Limits_Light[5] );
  Gas = read_gas();
  Temp1 = read_DHT11_temp();
  Hum = read_DHT11_hum();
  Temp2 = read_Analog_Temp();
  // σε κάθε loop ενημερώνουμε τους πίνακες κατανομής
  for ( i = 0; i <= 5; i++ ) {
    if ( Light > ( Limits_Light[i] ) && ( Light <= ( Limits_Light[i + 1] ) ) )
      dst_Light[i] = dst_Light[i] + 1;
    if ( Temp2 > ( Limits_Temp[i] ) && ( Temp2 <= ( Limits_Temp[i + 1] ) ) )
      dst_Temp[i] = dst_Temp[i] + 1;
    if ( Hum > ( Limits_DH11_hum[i] ) && ( Hum <= ( Limits_DH11_hum[i + 1] ) ) )
      dst_DH11_hum[i] = dst_DH11_hum[i] + 1;
    if ( Temp1 > ( Limits_DH11_Temp[i] ) && ( Temp1 <= ( Limits_DH11_Temp[i + 1] ) ) )
      dst_DH11_Temp[i] = dst_DH11_Temp[i] + 1;
    if ( Gas > ( Limits_MQ7[i] ) && ( Gas <= ( Limits_MQ7[i + 1] ) ) )
      dst_MQ7[i] = dst_MQ7[i] + 1;
    if ( Sound > ( Limits_Sound[i] ) && ( Sound <= ( Limits_Sound[i + 1] ) ) )
      dst_Sound[i] = dst_Sound[i] + 1;
  }
}

void show_on_lcd_all_results() {
  int num_of_reds = 0, num_of_yellows = 0, num_of_greens = 0, j;
  char * result = "!";
  sprintf (line1, "%s%s%s%s%s%s", dst_to_qlt(dst_Sound), dst_to_qlt(dst_Light), dst_to_qlt(dst_MQ7), dst_to_qlt(dst_Temp), dst_to_qlt(dst_DH11_hum), result);
  for (j = 0; j <= 12; j += 3) {
    if (line1[j] == 'B') num_of_reds++;   // BAD
    if (line1[j] == 'M') num_of_yellows++; // MED
    if (line1[j] == 'O') num_of_greens++; // OK!
  }


  if (num_of_reds >= 2)
  { result = "R";
    RGB_color(255, 0, 0); // Red
  } else if (num_of_greens >= 4) {
    RGB_color(0, 255, 0); // Green
    result = "G";
  }
  else {
    RGB_color(255, 255, 255); // White for Yellow
    result = "Y";
  }

  lcd.setCursor ( 0, 0 );
  lcd.print ( "SndLigGasTmpHumG");
  lcd.setCursor ( 0, 1 );

  sprintf (line1, "%s%s%s%s%s%s", dst_to_qlt(dst_Sound), dst_to_qlt(dst_Light), dst_to_qlt(dst_MQ7), dst_to_qlt(dst_Temp), dst_to_qlt(dst_DH11_hum), result);

  lcd.print ( line1 );

} // end show_on_lcd_all_results

void setup() {
  if (enable_print == 1)   // debugging purposes
    Serial.begin(9600);

  //initialise sensors
  setup_lcd();
  lcd.clear();
  lcd.setCursor ( 0, 0 );
  lcd.print ("CLASS QUALITY v1" );
  lcd.setCursor ( 0, 1 );
  lcd.print ("SENSORS CHECK " );
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  setup_Analog_Temp();
  setup_DHT11();
  setup_gas();
  setup_Sound_Sensor();
  setup_LIGHT();
  Millis_Lap_Disp = millis();
  Millis_Lap_Read = millis();

  lcd.print ("OK" );
  delay(2000);
  lcd.clear();
} //  end setup

void loop() {
  Millis_Now = millis();
  // περιοδικά (κάθε DISPLAY_EVERY msecs) αξιολογούμε και δείχνουμε ΟΛΑ τα αποτελέσματα των κατανομών

  if ( ( Millis_Now - Millis_Lap_Disp ) > DISPLAY_EVERY ) {
    show_on_lcd_all_results();
    Millis_Lap_Disp = Millis_Now;
    delay(7000);
  } // end display results

  // περιοδικά (κάθε READ_EVERY msecs) διαβάζουμε από ολους τους αισθητήρες
  if ( ( Millis_Now - Millis_Lap_Read ) > READ_EVERY ) {
    read_from_all_sensors();
    Millis_Lap_Read = Millis_Now;
  }

  //
  which_button = read_LCD_buttons();
  switch ( which_button ) {           // depending on which button was pushed, we perform an action
    case buttonSELECT: {
        lcd_button = 0;
        break;
      }
    case buttonLEFT: {
        lcd_button = 1;
        break;
      }
    case buttonDOWN: {
        lcd_button = 2;
        break;
      }
    case buttonRIGHT: {
        lcd_button = 4;
        break;
      }
    case buttonUP: {
        lcd_button = 3;
        break;
      }
  } // end switch button pressed

  if ( lcd_button == 0 )
    show_on_lcd_dst ( "TEM ", dst_Temp, ( int ) Temp1 );
  if ( lcd_button == 1 )
    show_on_lcd_dst ( "LGT ", dst_Light, ( int ) Light );
  if ( lcd_button == 2 )
    show_on_lcd_dst ( "HUM ", dst_DH11_hum, ( int ) Hum );
  if ( lcd_button == 3 )
    show_on_lcd_dst ( "GAS ", dst_MQ7, ( int ) Gas );
  if ( lcd_button == 4 )
    show_on_lcd_dst ( "SND ", dst_Sound, ( int ) Sound );
}


// display on LCD sensor name, distribution of sensor, live reading
void show_on_lcd_dst ( char sens[], unsigned int dOfS[], int live ) {

  sprintf ( line0, "%3d%3d%4d%3d%3d", dOfS[0], dOfS[1], dOfS[2], dOfS[3], dOfS[4] );
  lcd.setCursor ( 0, 0 );
  lcd.print ( line0 );
  sprintf ( line1, "%s<%5d> %s ", sens, live, dst_to_qlt ( dOfS ) );
  lcd.setCursor ( 0, 1 );
  lcd.print ( line1 );
}

// dst_to_qlt (x)
// input : ένα πίνακα κατανομών x, και επιστρέφει
// output: string BAD, MED, OK! ανάλογα το πλήθος και την κατανομή ανά εύρος

char *dst_to_qlt ( unsigned int x[] ) {
  unsigned int Sum;
  float Green, Yellow, Red;
  Sum = x[0] + x[1] + x[2] + x[3] + x[4]; // σύνολο ΟΛΩΝ των τιμών (πλήθος μετρήσεων)
  // για κάθε ζώνη βρίσκουμε το ποσοστό της (σαν % επι του όλου)
  Green = ( float ) ( ( float ) x[2] / ( float ) Sum );      // μέση ζώνη Γ
  Yellow = ( float ) ( ( float ) ( x[1] + x[3] ) / ( float ) Sum ); // ζώνη Β + Δ
  Red = ( float ) ( ( float ) ( x[0] + x[4] ) / ( float ) Sum ); // ακριανή ζώνη Α + Ε
  if ( Red >= RED_PCT )
    return ( "BAD" );
  else if ( Yellow >= YEL_PCT )
    return ( "MED" );
  else
    return ( "OK!" );
}

// set RGB led color
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
