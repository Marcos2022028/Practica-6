#include <Wire.h> //Libreria de I2C
#include <LiquidCrystal_I2C.h>//Libreria I2C LCD
#include <DallasTemperature.h>//Libreri del sensor de temperatura
#include <RTClib.h>//Libreria del reloj

#define lcdAddress 0x27  //Se define acceso del Lcd
#define filas 2//Se definen las filas
#define columnas 16//Se definen las columnas
LiquidCrystal_I2C pantallalcd(lcdAddress, columnas, filas);//Se colocan los define usados anteriormente 

OneWire ourWire(6);//Se coloca el pin del rtc
DallasTemperature sensors(&ourWire);//Declara el sensor de temperatura

RTC_DS3231 rtc;//se le da nombre al rtc

#define SIN 5//Defien el pin del Buzzer
#define outbuzzer() pinMode(SIN,OUTPUT)//salida del buzzer
#define encenbuzzer() tone(SIN,1000)//Encen del buzz
#define apagbuzzer() noTone(SIN)//Apag buzz

#define JUAN 2//Se define pin de la bomba
#define outbomba() pinMode(JUAN,OUTPUT)//Salida de la bomba
#define encenbomba() digitalWrite(JUAN,HIGH)//Encen de la bomba
#define apagbomba() digitalWrite(JUAN,LOW)//Apag de la bomba

void setup() {
  pantallalcd.init();//Iniciador de la lcd
  pantallalcd.backlight();//Iniciador de la luz del lcd
  sensors.begin();
  rtc.begin();
  rtc.adjust(DateTime(__DATE__,__TIME__));//Se inicia la fecha y el tiempo
  outbuzzer();//Salida del buzzer
  outbomba();//Salida de la bomba

}

void loop() {
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);//Se usa la variable para grados celcius
  pantallalcd.setCursor(0,0);  //Inicio del cursor
  pantallalcd.print(temperatura);//Se coloca temperatura en la lcd
  pantallalcd.print(" C ");//Se coloca EL SIGNO
  
  DateTime fecha = rtc.now();//Se coloca fecha
  pantallalcd.print(  fecha.hour());//Uso de la hora
  pantallalcd.print(":");				
  pantallalcd.print(fecha.minute());//Uso de la fecha 
  
  delay(200);//Tiempo estipulado

  if (fecha.hour() == 12 && fecha.minute() == 12 && fecha.second() == 0){//Se inicia bucle con la hora y minutos y el segundo    
    encenbuzzer();//Se enciende el buzzer
    pantallalcd.setCursor(0,1);//Donde inicia el cursor
    pantallalcd.print("   Inicia en  ");//Lo que se enseña en el lcd
    delay(5000);//tiempo
    pantallalcd.clear();//Se limpia la Lcd
    
  } 
  if (fecha.hour() == 12 && fecha.minute() == 12 && fecha.second() == 11) {//Se inicia bucle con la hora y minutos y el segundo   
  apagbuzzer();//Se apaga buzzer
  pantallalcd.setCursor(0,1);//Cursor del lcd
  pantallalcd.print("   Hora de regar   ");///Lo que se enseña en el lcd
  apagbomba();//Se apaga la bomba
  delay(20000);//Tiempo de encendido 
  pantallalcd.clear();//Se lipia la pantalla
  } else{
    encenbomba();//Se apaga la bomba
  }
}
