#include "./Thirdparty/SSD1306.h"
SSD1306Wire  display(0x3c, pinSDA, pinSCL);
void setupOled() {

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
/*void display_AM2320_temp(int status) {
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
}*/
void display_AM2320_Humidity() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Humidity");
    set_b_text();
    display.drawString(0,22, String(hum));
    display.display();
    delay(2000);
}
void display_last_temp() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Last Temp & Humi");
    set_m_text();
    //display.drawString(0,22,String(AM2320.temperature));
    display.drawString(0,22,String(temp));
    display.drawString(45,22, "*C");
    display.drawString(0,44, String(hum));
    display.drawString(45,44, "%");
    display.display();
    delay(delayTime);
}
void display_bme_last_Pressure() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Last Pres & Alti");
    set_m_text();
    display.drawString(0,22,String(String(pres)));
    display.drawString(60,22, "hPa");
    display.drawString(0,44, String(alti));
    display.drawString(60,44, "M");
    display.display();
    delay(delayTime);
}

void display_bmp_temp() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Temperature (*C)");
    set_b_text();
    display.drawString(0,22, String(temp));
    display.display();
    delay(delayTime);
}
void display_bmp_Pressure() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Pressure (hPa)");
    set_b_text();
    display.drawString(0,22, String(pres));
    display.display();
    delay(delayTime);
}
void display_bmp_Altitude() {
    readInput();
    display.clear();  
    set_m_text();
    display.drawString(0,0,"Altitude (M)");
    set_b_text();
    display.drawString(0,22, String(alti));
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
void novalid_BMP_oled(){
    set_m_text();
    new_screen_oled(0,0,"No valid BMP280 sensor");
    delay(5000);
}


