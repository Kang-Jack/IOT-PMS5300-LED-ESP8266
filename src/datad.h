const int buttonPin = 14;//14;    // the number of the pushbutton pin
const int pinSDA = 4;
const int pinSCL = 5;

unsigned pmsAto10;
unsigned pmsAto2_5;
unsigned pmsAto1;
float pmsForm;
int aqi2_5;
int aqi10;
char aqiString_25[10];
char aqiString10[10];
char aqiTime[6];

const int max_length = 40;
char msg[40];
char float_str_temp[8];

float temp;
float hum;
float pres;
float alti;

const int delayTime = 4000; 
const int waittingSec = 60;
int workingSec = 60;

int reading = 0l;
