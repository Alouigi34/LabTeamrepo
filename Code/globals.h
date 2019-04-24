int enable_print = 1;         //    το χρησιμοποιούμε για debugging, αν 1 τότε δείχνει στο serial monitor

#define RED_PCT 0.05            // επίπεδα ανοχής για τις ζώνες
#define YEL_PCT 0.20
#define GRN_PCT 0.75

#define DISPLAY_EVERY 10000  // κάθε πότε (milliseconds) θα δείχνει στην οθόνη -- 30000= 30 seconds
#define READ_EVERY 1000     // κάθε πότε (milliseconds) θα διαβάζει όλους τους αισθητήρες -- 10000= 10 seconds

#define buttonRIGHT  0    // read the buttons of LCD panel  
#define buttonUP     1
#define buttonDOWN   2
#define buttonLEFT   3
#define buttonSELECT 4
#define buttonNONE   5


//εδώ ορίζουμε τους πίνακες κατανομής
//κάθε πίνακας qltdst έχει 5 στοιχεία που είναι το πλήθος των μετρήσεων του αισθητήρα ανά ζώνη
// {R, Y, G, Y, R} RED YELLOW GREEN YELLOW RED

unsigned int dst_Temp[5]      = {0, 0, 0, 0, 0};
unsigned int dst_Light[5]     = {0, 0, 0, 0, 0};
unsigned int dst_DH11_hum[5]  = {0, 0, 0, 0, 0};
unsigned int dst_DH11_Temp[5] = {0, 0, 0, 0, 0};
unsigned int dst_MQ7[5]       = {0, 0, 0, 0, 0};
unsigned int dst_Sound[5]     = {0, 0, 0, 0, 0};

//τα όρια των αισθητήρων              RED    YEL    GRN    YEL   RED
unsigned int Limits_Temp[6]       = {0,   15,    20,    25,   30,   100};   // βαθμοί κελσίου
unsigned int Limits_Light[6]      = {0,  100,   200,  3950, 5000, 30276};   // light
unsigned int Limits_DH11_hum[6]   = {0,   30,    40,    55,   60,   100};   // υγρασία %
unsigned int Limits_DH11_Temp[6]  = {0,   15,    20,    25,   30,   100};   // βαθμοί κελσίου
unsigned int Limits_MQ7[6]        = {0,  100,   150,   170, 1230,  2000};   // CO2
unsigned int Limits_Sound[6]      = {9,    8,     0,    20,   40,  1000};   // sound sensor output, trick for >0 only!!!

// rgb led - pin settings
int red_light_pin = 13;
int green_light_pin = 11;
int blue_light_pin = 12;
