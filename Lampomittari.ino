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

}
