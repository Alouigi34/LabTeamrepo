/*
   DHT11 Temperature samples 25,26,27
   DHT11 Humidity samples 34,33,28
   MQ135 Air quality samples 250,270,290
   BH1750 Light Sensor samples 600,700,800
   Sparkfun Electret samples 500-700
  3 λεπτά ανοχή στην ώρα για το κόκκινο LED = 5% του χρόνου.
  12 λεπτά ανοχή στην ώρα για το κίτρινο LED = 20% του χρόνου.
  45 λεπτά ανοχή στην ώρα για το πράσινο LED = 75% του χρόνου.
*/

/////////////lcd

//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// read the buttons

//////
void A100_loop_analog(void);
void setup_Analog_Temp(void) ;
void lcd_light(void);
void lcd_temp(void);
void lcd_gas(void);
void lcd_hum(void);





int gnd;
float Hum, Temp1, Temp2;
uint16_t Light;
int Gas, Sound;

int enable_print = 1;

int i = 0;
#define y1 0
#define g1 1
#define g2 2
#define y2 3
unsigned int distribution_Temp[5] = {0, 0, 0, 0, 0};
int distribution_Light[5] = {0, 0, 0, 0, 0};
unsigned int distribution_DH11_hum[5] = {0, 0, 0, 0, 0};
unsigned int distribution_DH11_Temp[5] = {0, 0, 0, 0, 0};
unsigned int distribution_MQ7[5] = {0, 0, 0, 0, 0};
unsigned int Limits_Temp[6] = {0, 15, 20, 25, 30, 100};
unsigned int Limits_Light[6] = {0, 400, 500, 600, 700, 3276};
unsigned int Limits_DH11_hum[6] = {0, 20, 30, 43, 53, 100};
unsigned int Limits_DH11_Temp[6] = {0, 15, 20, 25, 30, 100};
unsigned int Limits_MQ7[6] = {0, 100, 150, 170, 230, 2000};
int ax;
//int Limits_SOUND[4] ={15,20,25,30};
void setup() {

  setup_Analog_Temp();
  setup_DHT11();
  setup_gas();
  setup_Sound_Sensor();
  setup_lcd();
  setup_LIGHT();
  //lcd.clear();


}

void loop() {
  enable_print = 0;
  A100_loop_analog();
  Light = loop_LIGHT();
  A100_loop_analog();
  Gas = loop_gas();
  A100_loop_analog();
  Temp1 = loop_DHT11_temp();
  Hum = loop_DHT11_hum();
  A100_loop_analog();
  Temp2 = loop_Analog_Temp();
  for (i = 0; i <= 5; i++) {
    if (Light > (Limits_Light[i]) && (Light < (Limits_Light[i + 1])))           {
      distribution_Light[i] = distribution_Light[i] + 1;
    }
  }
  for (i = 0; i <= 5; i++) {
    if (Temp2 > (Limits_Temp[i]) && (Temp2 < (Limits_Temp[i + 1])))             {
      distribution_Temp[i] = distribution_Temp[i] + 1;
    }
  }
  for (i = 0; i <= 5; i++) {
    if (Hum > (Limits_DH11_hum[i]) && (Hum < (Limits_DH11_hum[i + 1])))         {
      distribution_DH11_hum[i] = distribution_DH11_hum[i] + 1;
    }
  }
  for (i = 0; i <= 5; i++) {
    if (Temp1 > (Limits_DH11_Temp[i]) && (Temp1 < (Limits_DH11_Temp[i + 1])))   {
      distribution_DH11_Temp[i] = distribution_DH11_Temp[i] + 1;
    }
  }
  for (i = 0; i <= 5; i++) {
    if (Gas > (Limits_MQ7[i]) && (Gas < (Limits_MQ7[i + 1])))                    {
      distribution_MQ7[i] = distribution_MQ7[i] + 1;
    }
  }

  lcd.setCursor(2, 0);           // move cursor to second line "1" and 9 spaces over

  //lcd.print(" ");
  //lcd.setCursor(2, 4);
  //  lcd.print(distribution_Light[1]);
  //  lcd.print(" ");
  //  lcd.print(distribution_Light[2]);
  //  lcd.print(" ");
  //  lcd.print(distribution_Light[3]);
  //  lcd.print(" ");
  //  lcd.print(distribution_Light[4]);
  //  lcd.print(" ");
  //lcd.clear();


  lcd.setCursor(0, 0);

  ax = read_LCD_buttons();
  switch (ax)               // depending on which button was pushed, we perform an action
  {
    case 4:
      {

        gnd = 0;
        break;

      }
    case 3:
      {
        gnd = 1;
        break;
     }
  case 2: 
    {
      gnd = 2;
      break;
  }
  case 0: 
    {
      gnd = 3;
      break;
    }
  }  


  


  if (gnd == 0) {
    lcd_light();
  }

  if (gnd == 1) {
    lcd_temp();
  }

 if (gnd == 2) {
    lcd_gas();
  }
   if (gnd == 3) {
    lcd_hum();
  }


  



  // display seconds elapsed since power-up
  //  Serial.print(distribution_Light[1]);
  //  Serial.print(" ");
  //  Serial.print(distribution_Light[2]);
  //  Serial.print(" ");
  //  Serial.print(distribution_Light[3]);
  //  Serial.print(" ");
  //  Serial.println(distribution_Light[4]);
}

void A100_loop_analog(void) {
  for (i = 0; i <= 100; i++) {
    Sound = loop_Sound_Sensor();

  }


}

void lcd_light(void) {
  lcd.print(distribution_Light[0]);
  lcd.print(" ");
  lcd.print(distribution_Light[1]);
  lcd.print(" ");
  lcd.print(distribution_Light[2]);
  lcd.print(" ");
  lcd.print(distribution_Light[3]);
  lcd.print(" ");
  lcd.print(distribution_Light[4]);
  lcd.print(" ");
}

void lcd_temp(void) {
  lcd.print(distribution_Temp[0]);
  lcd.print(" ");
  lcd.print(distribution_Temp[1]);
  lcd.print(" ");
  lcd.print(distribution_Temp[2]);
  lcd.print(" ");
  lcd.print(distribution_Temp[3]);
  lcd.print(" ");
  lcd.print(distribution_Temp[4]);
  lcd.print(" ");


}
void lcd_gas(void) {
lcd.print(distribution_MQ7[0]);
  lcd.print(" ");
  lcd.print(distribution_MQ7[1]);
  lcd.print(" ");
  lcd.print(distribution_MQ7[2]);
  lcd.print(" ");
  lcd.print(distribution_MQ7[3]);
  lcd.print(" ");
  lcd.print(distribution_MQ7[4]);
  lcd.print(" ");


  
}
void lcd_hum(void) {

lcd.print(distribution_DH11_hum[0]);
  lcd.print(" ");
  lcd.print(distribution_DH11_hum[1]);
  lcd.print(" ");
  lcd.print(distribution_DH11_hum[2]);
  lcd.print(" ");
  lcd.print(distribution_DH11_hum[3]);
  lcd.print(" ");
  lcd.print(distribution_DH11_hum[4]);
  lcd.print(" ");

  
}
