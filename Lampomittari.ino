#include <LiquidCrystal.h>
#include <Smoothed.h>
#include "ajastin.h"

ajastin T3(1000); 

LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

Smoothed <float> tempAveg;

void setup()
{
Serial.begin(9600);
lcd.begin(16, 2);
Serial.println("Temp Display");
tempAveg.begin(SMOOTHED_AVERAGE, 100);
}

void showTemp(){
  int reading = analogRead(A0);
      float voltage = reading * (5000 / 1024.0);
      float temperature = (voltage - 500) / 10;
      tempAveg.add(temperature);
      float smoothedTempAvg = tempAveg.get();     
   if(temperature >24) {
        lcd.setCursor(0,0);
        lcd.print("Liian l\xe1mmin");
        lcd.setCursor(0,1);
        lcd.print(smoothedTempAvg);
        lcd.print("\337C");
        Serial.println(smoothedTempAvg);
   }else if(temperature <20){
        lcd.setCursor(0,0);
        lcd.print("Liian viile\xe1");
        lcd.setCursor(0,1);
        lcd.print(smoothedTempAvg);
        lcd.print("\337C");
        Serial.println(smoothedTempAvg);        
   }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Sopiva ilma");
        lcd.setCursor(0,1);
        lcd.print(smoothedTempAvg);
        lcd.print("\337C");
        Serial.println(smoothedTempAvg);
   }
   tempAveg.clear();
}

void loop(){
  if(T3.timeIsUp()){
   showTemp(); 
  }
}
