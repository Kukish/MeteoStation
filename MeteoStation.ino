#include <Wire.h>
#include "lib/LiquidCrystal_I2C.h"
#include "lib/DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT sensor;
int DHTpin = 4;
int result;

void setup() {
  lcd.init();
  lcd.backlight();
  //Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
}
void loop() {
  result = sensor.read(DHTpin);
  switch(result){
    case DHT_OK:      
      lcd.setCursor(0, 0);
      lcd.print("Hum:          %");
      lcd.setCursor(10, 0);
      lcd.print((float)sensor.hum);
      lcd.setCursor(0, 1);
      lcd.print("Temp:         C");
      lcd.setCursor(10, 1);
      lcd.print(sensor.tem);
      //Serial.println((String) "Hum: "+sensor.hum+"% - Temp: "+sensor.tem+"C");  
      break;
    case DHT_ERROR_CHECKSUM:  
      lcd.setCursor(0, 0);
      lcd.print("Checksum error");
      //Serial.println("Checksum error");       
      break;
    case DHT_ERROR_DATA:  
      lcd.setCursor(0, 0);
      lcd.print("Sensor error");  
      //Serial.println("Sensor error"); 
      break;
    case DHT_ERROR_NO_REPLY:
      lcd.setCursor(0, 0);
      lcd.print("No response from sensor");  
      //Serial.println("No response from sensor");        
      break;
    default:
      lcd.setCursor(0, 0);
      lcd.print("Unknown error");
      //Serial.println(Unknown error);         
      break;
  }
  delay(2000);
}
