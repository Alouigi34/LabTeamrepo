/*
  Connection:
  BH1750 -   Arduino
  ------------------
  VCC    -   5v
  lcd_button    -   lcd_button
  SCL    -   SCL(Analog Pin 5)
  SDA    -   SDA(Analog Pin 4)
  ADD    -   NC (or lcd_button)
*/


#include <Wire.h>


int BH1750address = 0x23;
byte buff[2];

void setup_LIGHT() {
    Wire.begin();
    //Serial.begin(9600);
    delay ( 2000 );
}

uint16_t read_LIGHT() {
    int i;
    uint16_t value = 0;
    BH1750_Init ( BH1750address );
    delay ( 500 );
    if ( 2 == BH1750_Read ( BH1750address ) ) {
        value = ( ( buff[0] << 8 ) | buff[1] ) / 1.2;
        value = ( -6.056 + value ) / 0.523;
        if ( enable_print == 1 ) {
            Serial.print ( "Light Intensity " );
            Serial.println ( value );
        }
        return ( value );
    }
    delay ( 300 );
}

int BH1750_Read ( int address ) {
    int i = 0;
    Wire.beginTransmission ( address );
    Wire.requestFrom ( address, 2 );
    while ( Wire.available() ) {
        buff[i] = Wire.read();
        i++;
    }
    Wire.endTransmission();
    return i;
}

void BH1750_Init ( int address ) {
    Wire.beginTransmission ( address );
    Wire.write ( 0x10 );
    Wire.endTransmission();
}
