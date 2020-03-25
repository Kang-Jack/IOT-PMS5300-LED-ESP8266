#include "AM232X.h"
#include <Adafruit_BMP280.h>
AM232X AM2320;
#define SEALEVELPRESSURE_HPA (1013.25)
bool bmpStatus =false;
Adafruit_BMP280 bmp; // use I2C interface

bool InitBmp(){
  int i=0;
  bool isOK=false;
  while (i<10){
    if (!bmp.begin(0x76)) {
      Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
        i++;
        delay(10);
      }
    else
    {
      isOK=true;
      i=10;
        /* Default settings from datasheet. */
     // bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
      //                Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
      //                Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
       //               Adafruit_BMP280::FILTER_X16,      /* Filtering. */
        //              Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    }
    return isOK;
  }
}
bool setupSensors(void){
  AM2320.begin(pinSDA, pinSCL);
  pinMode(buttonPin, INPUT);
  bmpStatus=InitBmp();
  return bmpStatus;
}
void readInput(){
  if(reading==LOW){
      reading = digitalRead(buttonPin);
  }
}
void handleTHP(){
  if (workingSec>=1){
    int status = AM2320.read();
    Serial.println(String(status));
    if(status == AM232X_OK){
      hum = AM2320.humidity;
    }
    Serial.println(String(AM232X_OK));
    //display_AM2320_temp(status);
    if (bmpStatus){
      temp = bmp.readTemperature();
      pres = bmp.readPressure() / 100.0F;
      alti = bmp.readAltitude(SEALEVELPRESSURE_HPA);
    } 
  } 
}