int SOUND_NOW;

void setup_Sound_Sensor() {
  // put your setup code here, to run once:
  pinMode ( A2, INPUT );
  //Serial.begin(9600);
}

int read_Sound_Sensor() {
  SOUND_NOW = analogRead ( A2 );
  //Serial.print("Sound voltage ");
  if ( enable_print == 1 ) {
    //Serial.println(SOUND_NOW);
  }
  return ( SOUND_NOW );
}

unsigned int read_sound_100() {
  int abc;
  unsigned long int ab;
  ab = 0;
  for ( i = 0; i <= 100; i++ ) {
    Sound = read_Sound_Sensor();
    if ( Sound > 500 ) {
      abc = Sound - 500;
    } else {
      abc = 500 - Sound;
    }
    ab = abc + ab;
  }
  ab = ab / 100;
  if ( enable_print == 1 ) {
    Serial.print ( " entash 100 deigmatwn:" );
    Serial.println ( ab );
  }
  return ( ab );
}
