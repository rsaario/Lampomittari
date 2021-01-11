#include <LiquidCrystal.h>
#include "ajastin.h"

ajastin T3(1000); 

LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

void setup()
{
Serial.begin(9600);
lcd.begin(16, 2);
Serial.println("Temp Display");
}

void loop(){
  if(T3.timeIsUp()){
    int reading = analogRead(A0);
      float voltage = reading * (5000 / 1024.0);
      float temperature = (voltage - 500) / 10;
      lcd.setCursor(0,0);
        lcd.print("Sopiva ilma");
        lcd.setCursor(0,1);
        lcd.print(temperature);
        lcd.print("\337C");
        Serial.println(temperature);
        delay (1000);
        lcd.clear();
}
