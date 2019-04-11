int SOUND_NOW;

void setup_Sound_Sensor() {
  // put your setup code here, to run once:

  pinMode(A2, INPUT);

  //Serial.begin(9600);
}

int loop_Sound_Sensor() {
  // put your main code here, to run repeatedly:
  SOUND_NOW = analogRead(A2);
  //Serial.print("Sound voltage ");
    if (enable_print==1){
       Serial.println(SOUND_NOW);
    }
return(SOUND_NOW);
}
