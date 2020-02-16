
#include <Wire.h>
#include "datad.h"
#include "SSD1306.h"

#include "ESP_PMS5003S.h"
#include "AM232X.h"

AM232X AM2320;

#define SEALEVELPRESSURE_HPA (1013.25)

const int pinSDA = D2;
const int pinSCL = D1;
const int buttonPin = D5;//14;    // the number of the pushbutton pin

SSD1306Wire  display(0x3c, pinSDA, pinSCL);


const int delayTime = 4000; 
const int waittingSec = 60;
int workingSec = 60;
int reading = LOW;
void readInput(){
  if(reading==LOW){
      reading = digitalRead(buttonPin);
  }
}
void init_oled() {
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 0, "Init OLED");
}
void set_s_text(){
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);;
}
void set_m_text(){
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);;
}
void set_b_text(){
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_24);
}

void new_screen_oled(int x,int y,char* mesg){
  display.clear();
  display.drawString(x, y, mesg);
  display.display();
  delay(1000);
}
void display_AM2320_temp(int status) {
  if(status == AM232X_OK){
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Temperature (*C)");
    set_b_text();
    display.drawString(0,22, String(AM2320.temperature));
    display.display();
    delay(delayTime);
    }

}
void display_AM2320_Humidity(int status) {
   if(status == AM232X_OK){
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Humidity");
    set_b_text();
    display.drawString(0,22, String(AM2320.humidity));
    display.display();
    delay(2000);
   }
}
void display_AM2320_last_temp() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Last Temp & Humi");
    set_m_text();
    display.drawString(0,22,String(AM2320.temperature));
    display.drawString(45,22, "*C");
    display.drawString(0,44, String(AM2320.humidity));
    display.drawString(45,44, "%");
    display.display();
    delay(delayTime);
}
void display_AQI2_5() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,aqiString_25);
    set_b_text();
    display.drawString(0,22, String(aqi2_5));
    set_m_text();
    display.drawString(65,22, "AQI2_5");
    display.display();
    delay(delayTime);
}
void display_AQI10() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,aqiString10);
    set_b_text();
    display.drawString(0,22, String(aqi10));
    set_m_text();
    display.drawString(65,22, "AQI10");
    display.display();
    delay(delayTime);
}

void display_last_AQI() {
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Last AQI is");
    set_b_text();
    if (aqi2_5>aqi10)
    {
      display.drawString(0,22, String(aqi2_5));
      set_m_text();
      display.drawString(65,22, "AQI2_5");
    }
    else
    {
      display.drawString(0,22, String(aqi10));
      set_m_text();
      display.drawString(65,22, "AQI10");
    }
    display.display();
    delay(delayTime);
}

void handleAM2320(){
     if (workingSec>=1){
      int status = AM2320.read();
      Serial.println(String(status));
      Serial.println(String(AM232X_OK));
      display_AM2320_temp(status);
      display_AM2320_Humidity(status);
     }
    
 }
void setup(void){
  Wire.pins(pinSDA, pinSCL);
  AM2320.begin(pinSDA, pinSCL);
  Serial.begin(115200);
  init_oled();
  setupPMS5003S();
  pinMode(buttonPin, INPUT);
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
  handleAM2320();
  if (workingSec>=1)
  {
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
    display_AM2320_last_temp();
    delay(500); 
  }

}
