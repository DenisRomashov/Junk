#define Trig 9
#define Echo 8
#define LIGHT  A0

void setup() {
  pinMode(Trig, OUTPUT); //инициируем как выход 
  pinMode(Echo, INPUT); //инициируем как вход 
  Serial.begin(9600); 
}

unsigned int impulseTime=0; 
unsigned int distance_sm=0; 

void loop() {
  // считываем уровень освещённости. Кстати, объявлять
  int lightness = analogRead(LIGHT);
  digitalWrite(Trig, HIGH); 
  /* Подаем импульс на вход trig дальномера */
  delayMicroseconds(10); // равный 10 микросекундам 
  digitalWrite(Trig, LOW); // Отключаем 
  impulseTime=pulseIn(Echo, HIGH); // Замеряем длину импульса 
  distance_sm=impulseTime/58; // Пересчитываем в сантиметры 
  Serial.print("Light ");
  Serial.println(lightness);
  Serial.print("Distance ");
  Serial.println(distance_sm); // Выводим на порт 
  delay(1000); 
}
