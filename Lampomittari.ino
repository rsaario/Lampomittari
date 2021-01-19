#include <LiquidCrystal.h>
#include <Smoothed.h>
#include "ajastin.h"
#include "tmp36.h"

//määrittää ajastimen nimen ja ajan
ajastin T1(1000);
tmp36 sensorPin (A0);
//määritetään lcd sana ohjaamaan näyttöä                                
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);
                                //RS,E,D4,D5,D6,D7
//määriteään float datatyypeiksi                        
float lastSmoothedTempAvg;

void setup()
{
Serial.begin(9600);
//käynnistää näytön
lcd.begin(16, 2);
Serial.println("Temp Display");
}
//näytölle kirjoitus toiminto
void writeLcd(float smoothedTempAvg){ 
  //tulostaa jos lämpötila ylittää 24 astetta  
   if(smoothedTempAvg >24) {
        lcd.setCursor(0,0);
        lcd.print("Liian l\xe1mmin");
        lcd.setCursor(0,1);
        //määrittää mitä tulostuu ja muuttaa luvun yhdelle desimaalille
        lcd.print(smoothedTempAvg,1);
        //tulostaa celsius merkin
        lcd.print("\337C");
        Serial.println(smoothedTempAvg);
   }//tulostaa jos lämpötila alittaa 20 astetta
   else if(smoothedTempAvg <20){
        lcd.setCursor(0,0);
        lcd.print("Liian viile\xe1");
        lcd.setCursor(0,1);
        lcd.print(smoothedTempAvg,1);
        lcd.print("\337C");
        Serial.println(smoothedTempAvg);        
   }//annettujen arvojen välissä tulostuva ilmoitus
   else{
        lcd.setCursor(0,0);
        lcd.print("Sopiva ilma ");    
        lcd.setCursor(0,1);
        lcd.print(smoothedTempAvg,1);
        lcd.print("\337C");
        Serial.println(smoothedTempAvg);
   }
}

void updateLcd(float smoothedTempAvg){
  /*vertaa aikaisempaa keskiarvoa uuteen keskiarvoon ja suorittaa sen 
  mukaan näytön kirjoitus funktion*/
  if(smoothedTempAvg != lastSmoothedTempAvg){
    writeLcd(smoothedTempAvg);
    lastSmoothedTempAvg = smoothedTempAvg;
  }
}

void loop(){
  float smoothedTempAvg = sensorPin.getTemp();
  //kun aika on täynnä suorittaa sisällytetyt funktiot
  if(T1.timeIsUp()){
   updateLcd(smoothedTempAvg);
   Serial.print("vanha keskiarvo ");
   Serial.println(lastSmoothedTempAvg);
  }  
}
