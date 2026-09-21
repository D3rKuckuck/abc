#define RED 9
#define GREEN 10
#define BLUE 11
void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Первый цикл Максимальный красный постепенно переходит в зеленый
  for (int i=0;i<256;i+=15){
    analogWrite(RED, 255-i); // Понижаем яркость красного каждые 100мс
    analogWrite(GREEN, i); // Повышаем яркость зеленого каждые 100мс
    delay(100);
  }
  // Зеленый в синий
  for (int i=0;i<256;i+=15){
    analogWrite(GREEN, 255-i); // Понижаем яркость зеленого каждые 100мс
    analogWrite(BLUE, i); // Повышаем яркость синего каждые 100мс
    delay(100);
  }
  // Синий в красный
  for (int i=0;i<256;i+=15){
    analogWrite(BLUE, 255-i); // Понижаем яркость синего каждые 100мс
    analogWrite(RED, i); // Повышаем яркость красного каждые 100мс
    delay(100);
  }
}
