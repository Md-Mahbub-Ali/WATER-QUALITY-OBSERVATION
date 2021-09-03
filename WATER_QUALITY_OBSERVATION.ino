
//MD MAHBUB ALI

#include <GravityTDS.h>
#include <EEPROM.h>
#include "GravityTDS.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 16);
#define ONE_WIRE_BUS 6 //DS18B20 sensor
#define TdsSensorPin A1 //TDS sensor

OneWire oneWire(ONE_WIRE_BUS);
GravityTDS gravityTds;

DallasTemperature sensors(&oneWire);

float tdsValue = 0;
int turbidity;
int sensorPin = A0; //TURBIDITY sensor
int sensorValue;

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("WATER QUALITY");
  delay(1000);
  lcd.clear();
  sensors.begin();
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  
  gravityTds.setAdcRange(1024);  
  gravityTds.begin();  


}
void loop() {

turbiditty();
turbiditty_show();

delay(1000);
lcd.clear();
tds_temp();
tds_temp_show();
lcd.clear();
}


void turbiditty()
{  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
   turbidity = map(sensorValue, 0, 760, 100, 0); // if sensorValue is equal 0 and 760, turbidity will show 100 and 0 respectively
  delay(100);
}

void turbiditty_show()
{
  lcd.setCursor(0, 0);
  lcd.print("turbidity:");
  lcd.print("   ");
  lcd.setCursor(10, 0);
  lcd.print(turbidity);
  delay(100);

  if (turbidity < 20) {
    lcd.setCursor(0, 1);
    lcd.print("its CLEAR");
  }
  if (turbidity < 0) {
    turbidity = 0;
    lcd.setCursor(0, 1);
    lcd.print("its CLEAR");
  }
  if ((turbidity > 20) && (turbidity < 50)) {

    lcd.setCursor(0, 1);
    lcd.print(" its CLOUDY ");
  }
  if (turbidity > 50) {

    lcd.setCursor(0, 1);
    lcd.print(" its DIRTY ");
  }
  }


void tds_temp()
{ sensors.requestTemperatures();

  gravityTds.setTemperature(sensors.getTempCByIndex(0));  
  gravityTds.update();  
  tdsValue = gravityTds.getTdsValue();  

  Serial.print(tdsValue, 0);
  Serial.println("ppm");
  Serial.print("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0));
}

void tds_temp_show()

{
  
  lcd.setCursor(0, 0);
  lcd.print("TDS: ");
  lcd.print(tdsValue, 0);
  lcd.print(" PPM");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" C");

  delay(1500);
  }
