#include <Wire.h>
#include "lib/LiquidCrystal_I2C.h"
#include "lib/DHT.h"
#include "lib/Adafruit_BMP085_U.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

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
  bmp.begin();
}
void loop() {
  lcd.clear();
  result = sensor.read(DHTpin);
  switch(result){
    case DHT_OK:      
      lcd.setCursor(0, 0);
      lcd.print("Hum:           %");
      lcd.setCursor(10, 0);
      lcd.print((float)sensor.hum);
      lcd.setCursor(0, 1);
      lcd.print("Temp:          C");
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
  delay(5000);

  /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Prs:         hPa");
    lcd.setCursor(10, 0);
    lcd.print((int) event.pressure);
    lcd.setCursor(0, 1);
    lcd.print("Alt:           m");
    lcd.setCursor(11, 1);
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    lcd.print((int) bmp.pressureToAltitude(seaLevelPressure,event.pressure));
    delay(5000);
  }
}
