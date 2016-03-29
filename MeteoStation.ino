// include the library code:
#include "lib/LiquidCrystal.h"
#include "lib/DHT.h"
#include "lib/ds3231/DS3231.h"
#include <EEPROM.h>
#include "lib/Adafruit_BMP085_U.h"

DS3231 Clock(SDA, SCL);
Time RTC_Time;

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
DHT sensor;
int DHTpin = 9;
int result;
//used to get data from DHT22 every 5 secs
int DHTcounter = 0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

byte degree[8] = // degree symbol
{
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte colon[8] = // colon symbol
{
  B00000,
  B01100,
  B01100,
  B00000,
  B01100,
  B01100,
  B00000,
};

void setup() {
  // set up the LCD's number of columns and rows:
  delay(1000);
  lcd.begin(16, 2);
  Clock.begin();
  lcd.createChar(1, degree); // creating degree symbol by 1
  lcd.createChar(3, colon); // creating colon symbol by 3
  bmp.begin();
}

void loop() {
  RTC_Time = Clock.getTime();
  lcd.setCursor(0, 0);
  if (RTC_Time.hour < 10) {
    lcd.print(0);
    lcd.setCursor(1, 0);
   } 
  lcd.print(RTC_Time.hour);
 
  lcd.setCursor(2, 0);
  lcd.write(byte(3));

  lcd.setCursor(3, 0);
  if (RTC_Time.min < 10) {
    lcd.print(0);
    lcd.setCursor(4, 0);
  }
  lcd.print(RTC_Time.min);
 
  
  lcd.setCursor(5, 0);
  lcd.write(byte(3));

  lcd.setCursor(6, 0);
  if (RTC_Time.sec < 10) {
    lcd.print(0);
    lcd.setCursor(7, 0);
  } 
  lcd.print(RTC_Time.sec);


  lcd.setCursor(11, 0);
  if (RTC_Time.date < 10) {
    lcd.print(0);
    lcd.setCursor(12, 0);
  }
  lcd.print(RTC_Time.date);


  lcd.setCursor(13, 0);
  lcd.print(".");

  lcd.setCursor(14, 0);
  if (RTC_Time.mon < 10) {
    lcd.print(0);
    lcd.setCursor(15, 0);
  }
  lcd.print(RTC_Time.mon);


  if(DHTcounter % 5 == 0) {
    DHTcounter = 0;
    result = sensor.read(DHTpin);
    switch(result){
      case DHT_OK:
        lcd.setCursor(0, 1);
        lcd.print("   C     %");
        lcd.setCursor(2, 1);
        lcd.write(byte(1));
        lcd.setCursor(0, 1);
        lcd.print((int) sensor.tem);
        lcd.setCursor(7, 1);
        lcd.print((int) sensor.hum);
        break;
      case DHT_ERROR_CHECKSUM:  
        lcd.setCursor(0, 1);
        lcd.print("Checksum error");
        //Serial.println("Checksum error");       
        break;
      case DHT_ERROR_DATA:  
        lcd.setCursor(0, 1);
        lcd.print("Sensor error");  
        //Serial.println("Sensor error"); 
        break;
      case DHT_ERROR_NO_REPLY:
        lcd.setCursor(0, 1);
        lcd.print("No response from sensor");  
        //Serial.println("No response from sensor");        
        break;
      default:
        lcd.setCursor(0, 1);
        lcd.print("Unknown error");
        //Serial.println(Unknown error);         
        break;
    }
  }
  DHTcounter++;
  
  sensors_event_t event;
  bmp.getEvent(&event);
  if(event.pressure) {
    lcd.setCursor(13, 1);
    lcd.print((int) (event.pressure/1.333));
  }
  delay(1000);
}
