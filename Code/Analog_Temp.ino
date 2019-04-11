int ThermistorPin = A3;
int Vo, LED, Min = 15, Max = 30, Ok1 = 20, Ok2 = 25, Mesos_Oros = 0, seira;
float R1 = 10000; // value of R1 on board
float logR2, R2, Temp;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coeficients for thermistor

void setup_Analog_Temp() {
  //Serial.begin(9600);
  Serial.println("Best Temp:20-25C Good Temp:15-20C & 25-30C Bad Temp:<15 & 30<");
}

float loop_Analog_Temp() {
  seira++;

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculate resistance on thermistor
  logR2 = log(R2);
  Temp = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); // temperature in Kelvin
  Temp = Temp - 273.15; //convert Kelvin to Celcius
  // Temp = (Temp * 9.0)/ 5.0 + 32.0; //convert Celcius to Farenheit

  if (enable_print==1){
     Serial.print("Temperature:");
     Serial.print(Temp);
     Serial.println(" C");
  }
/*  
  LED = 0; //red
  if ((Temp >= Min) && (Temp <= Max)) {
    LED = 1; //orange
    if ((Temp >= Ok1) && (Temp <= Ok2)) {
      LED = 2; //green
    }
  }
*/
return(Temp);
}
