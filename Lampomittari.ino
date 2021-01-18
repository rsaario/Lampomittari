#include <LiquidCrystal.h>
#include <Smoothed.h>
#include "ajastin.h"

//määrittää ajastimen nimen ja ajan
ajastin T1(1000); 
//määritetään lcd sana ohjaamaan näyttöä                                
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);
                                //RS,E,D4,D5,D6,D7
//määriteään float datatyypeiksi                        
Smoothed <float> tempAveg;
float smoothedTempAvg;
float lastSmoothedTempAvg;

void setup()
{
Serial.begin(9600);
//käynnistää näytön
lcd.begin(16, 2);
Serial.println("Temp Display");
//aloitetaan ja määritetään keskiarvo laskennalle arvojen määrä
tempAveg.begin(SMOOTHED_AVERAGE, 100);
}
//lämpötilan luku toiminto
void getTemp(){
  int reading = analogRead(A0);
      float voltage = reading * (5000 / 1024.0);
      float temperature = (voltage - 500) / 10;
      //lisätään arvo keskiarvo laskentaan
      tempAveg.add(temperature);
      //haetaan keskiarvo
      smoothedTempAvg = tempAveg.get();     
}   
//näytölle kirjoitus toiminto
void writeLcd(){ 
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

void updateLcd(){
  lastSmoothedTempAvg = tempAveg.getLast();
  /*vertaa aikaisempaa keskiarvoa uuteen keskiarvoon ja suorittaa sen 
  mukaan näytön kirjoitus funktion*/
  if(smoothedTempAvg > lastSmoothedTempAvg || smoothedTempAvg < lastSmoothedTempAvg){
    writeLcd();
  }
}

void loop(){
  getTemp();
  //kun aika on täynnä suorittaa sisällytetyt funktiot
  if(T1.timeIsUp()){
   updateLcd();
   tempAveg.clear();
  }  
}
