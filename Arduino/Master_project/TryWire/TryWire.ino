#include <Wire.h>
#define Trig 9
#define Echo 8
#define LIGHT  A0

void setup() {
  Wire.begin();
  pinMode(Trig, OUTPUT); //инициируем как выход 
  pinMode(Echo, INPUT); //инициируем как вход 
  Serial.begin(9600); 
}

unsigned int impulseTime=0; 
unsigned int distance_sm=0; 
byte x = 1;

void loop() {
  // считываем уровень освещённости. Кстати, объявлять
  int lightness = analogRead(LIGHT) / 4;
  
  digitalWrite(Trig, HIGH); 
  /* Подаем импульс на вход trig дальномера */
  delayMicroseconds(10); // равный 10 микросекундам 
  digitalWrite(Trig, LOW); // Отключаем 
  impulseTime=pulseIn(Echo, HIGH); // Замеряем длину импульса 
  distance_sm=impulseTime/58; // Пересчитываем в сантиметры 
  //Начало передачи
  Wire.beginTransmission(8);
  Wire.write("Light ");
  Wire.write(lightness);
  Wire.endTransmission();
  
  Wire.beginTransmission(8);
  Wire.write("Distance ");
  Wire.write(highByte(distance_sm));
  //Wire.endTransmission();
  //Wire.beginTransmission(8);
  Wire.write(lowByte(distance_sm));
  //Wire.write("x is ");
  //Wire.write(x);
  Wire.endTransmission();
  //Пишим в сериал
  Serial.print("Light ");
  Serial.println(lightness);
  Serial.print("Distance ");
  Serial.println(distance_sm); // Выводим на порт 
  
  delay(1000); 
}
