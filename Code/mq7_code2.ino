int gas_din = 3;
int gas_ain = A1;
int ad_value;


void setup_gas() {
    pinMode ( 8, OUTPUT );
    pinMode ( 9, OUTPUT );
    pinMode ( gas_din, INPUT );
    pinMode ( gas_ain, INPUT );
    //Serial.begin(9600);
}
int read_gas() {
    ad_value = analogRead ( gas_ain );
    if ( enable_print==1 ) {
        Serial.print ( "GAS " );
        Serial.println ( ad_value );
    }
    //delay(500);
    if ( ad_value < 150 ) {
        digitalWrite ( 9, HIGH );
        //delay(100);
        digitalWrite ( 8, LOW );
        //delay(100);
        if ( ad_value > 150 ) {
            digitalWrite ( 8, HIGH );
            //delay(100);
            digitalWrite ( 9, LOW );
            //delay(100);
        }
    }
    return ( ad_value );
}
