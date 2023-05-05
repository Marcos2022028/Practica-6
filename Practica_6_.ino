#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <RTClib.h>

#define lcdAddress 0x27  
#define filas 2
#define columnas 16
LiquidCrystal_I2C pantallalcd(lcdAddress, columnas, filas);

OneWire ourWire(6);
DallasTemperature sensors(&ourWire);

RTC_DS3231 rtc;

#define SIN 5
#define salidabuzzer() pinMode(SIN,OUTPUT)
#define encenbuzzer() tone(SIN,1000)
#define apagadobuzzer() noTone(SIN)

#define JUAN 2
#define salidabomba() pinMode(JUAN,OUTPUT)
#define encenderbomba() digitalWrite(JUAN,HIGH)
#define apagarbomba() digitalWrite(JUAN,LOW)

void setup() {
  pantallalcd.init();
  pantallalcd.backlight();
  sensors.begin();
  rtc.begin();
  rtc.adjust(DateTime(__DATE__,__TIME__));
  salidabuzzer();
  salidabomba();

}

void loop() {
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);
  pantallalcd.setCursor(0,0);  
  pantallalcd.print(temperatura);
  pantallalcd.print("°C ");
  
  DateTime fecha = rtc.now();
  pantallalcd.print(  fecha.hour());
  pantallalcd.print(":");				
  pantallalcd.print(fecha.minute());
  
  delay(200);

  if (fecha.hour() == 12 && fecha.minute() == 12 && fecha.second() == 0){    
    encenbuzzer();
    pantallalcd.setCursor(0,1);
    pantallalcd.print("   Inicia en  ");
    delay(5000);
    pantallalcd.clear();
    
  } 
  if (fecha.hour() == 12 && fecha.minute() == 12 && fecha.second() == 11) {
  apagadobuzzer();
  pantallalcd.setCursor(0,1);
  pantallalcd.print("   Hora de regar   ");
  apagarbomba();
  delay(20000);
  pantallalcd.clear();
  } else{
    encenderbomba();
  }
}