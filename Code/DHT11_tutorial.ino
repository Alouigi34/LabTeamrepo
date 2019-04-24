/* How to use the DHT-11 sensor with Arduino uno
   Temperature and humidity sensor
   More info: http://www.ardumotive.com/how-to-use-dht-11-sensor-en.html
   Dev: Michalis Vasilakis // Date: 2/7/2015 // www.ardumotive.com */

//Libraries
#include <dht.h>
dht DHT;
//Constants
#define DHT11_PIN 3     // DHT 22  (AM2302) - what pin we're connected to


//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup_DHT11() {
    //Serial.begin(9600);
}

float read_DHT11_temp() {
    int chk = DHT.read11 ( DHT11_PIN );   
    temp = DHT.temperature; //Read data and store it to variables hum and temp
    //  Print temp and humidity values to serial monitor
    if ( enable_print == 1 ) {
        Serial.print ( " %, Temp: " );
        Serial.print ( temp );
        Serial.println ( " Celsius" );
    }
    //delay(2000); //Delay 2 sec.
    return ( temp );
}


float read_DHT11_hum() {
    int chk = DHT.read11 ( DHT11_PIN );
    //Read data and store it to variables hum and temp
    hum = DHT.humidity;
    //  Print temp and humidity values to serial monitor
    if ( enable_print == 1 ) {
        Serial.print ( "Humidity: " );
        Serial.println ( hum );
    }
    //delay(2000); //Delay 2 sec.
    return ( hum );
}
