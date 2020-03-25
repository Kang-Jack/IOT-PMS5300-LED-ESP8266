#include <Wire.h>
#include "datad.h"
#include "ESP_Sensors.h"
#include "ESP_OLED.h"
#include "ESP_PMS5003S.h"

void setup(void){
  Wire.pins(pinSDA, pinSCL);
  Serial.begin(115200);
  setupOled();
 if (!setupSensors()){
    novalid_BMP_oled();
  }
  setupPMS5003S();
 
  Serial.println("start");
  set_m_text();
  new_screen_oled(0,0,"Starting ESP12S");
  wake();
}

void loop(void){
  readInput();
  /*Serial.println("loop");
  Serial.println(String(workingSec));
  Serial.println(String(reading));*/
  if(reading==HIGH)
  {
    reading = LOW;
    set_m_text();
    new_screen_oled(0,0,"Data is coming...");
    if (!isWake)
    {
      wake();
    }
      workingSec=waittingSec;
  }
  if (workingSec<1)
  {
    sleep();
  }
  handlePMS5003S();
  handleTHP();
  if (workingSec>=1)
  {
      display_bmp_temp();
      display_AM2320_Humidity();
      display_bmp_Pressure();
      display_bmp_Altitude();

      set_m_text();
      display_AQI2_5();
      display_AQI10();
      delay(500);    
      workingSec--;
  }
  else
  {    
    delay(500);  
    display_last_AQI();
    delay(500); 
    display_last_temp();
    delay(500);
    display_bme_last_Pressure();
    delay(500); 
  }

}
