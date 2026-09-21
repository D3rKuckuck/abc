#include "Servo.h"

int targetAngles[18] = {
  90, 120, 90,  
  70, 90, 100,  
  70, 90, 90,  
  70, 65, 90,  
  65, 55, 90,  
  60, 75, 90 
};

int servoPins[18] = {
  A0, A1, A2,      
  A3, A4, A5,      
  13, 12, 11,     
  10, 9, 8,   
  7, 6, 5,   
  4, 3, 2    
};

Servo myServos[18];

void setup() {
  baseplacing();
  delay(2000);

  walk(5);

  baseplacing();
}

void loop() {
}

void baseplacing() {
  for (int i = 0; i < 18; i++) {
    myServos[i].attach(servoPins[i]);
    int finalPos = constrain(targetAngles[i], 0, 180);
    myServos[i].write(finalPos);
  }
}

void walk(int steps) {
  for (int s = 0; s < steps; s++) {

    // шаг первой группы ног (1,3,5)
    stepGroup(0, 20, 15);
    delay(200);

    // шаг второй группы ног (2,4,6)
    stepGroup(1, 20, 15);
    delay(200);
  }
}

void stepGroup(int group, int liftAngle, int pushAngle) {

  // ---------------------------------------------------
  // 1. Поднимаем выбранную группу ног
  // ---------------------------------------------------
  for (int i = 0; i < 6; i++) {

    int sIndex = i * 3;

    if (i % 2 == group) {
      // поднимаем ногу
      myServos[sIndex + 1].write(targetAngles[sIndex + 1] + liftAngle);
    }
  }

  delay(120);

  // ---------------------------------------------------
  // 2. Переносим поднятые ноги вперед
  // ---------------------------------------------------
  for (int i = 0; i < 6; i++) {

    int sIndex = i * 3;

    if (i % 2 == group) {
      // поворачиваем вперед
      myServos[sIndex].write(targetAngles[sIndex] + pushAngle);
    }
  }

  delay(120);

  // ---------------------------------------------------
  // 3. Опускаем ноги на землю
  // ---------------------------------------------------
  for (int i = 0; i < 6; i++) {

    int sIndex = i * 3;

    if (i % 2 == group) {
      myServos[sIndex + 1].write(targetAngles[sIndex + 1]);
    }
  }

  delay(120);

  // ---------------------------------------------------
  // 4. Толчок — все ноги двигаются назад
  // стоящие на земле толкают корпус вперед
  // ---------------------------------------------------
  for (int i = 0; i < 6; i++) {

    int sIndex = i * 3;

    // все ноги толкают назад
    myServos[sIndex].write(targetAngles[sIndex] - pushAngle);
  }

  delay(150);

  // ---------------------------------------------------
  // 5. Возвращаем ноги в базовую позицию
  // ---------------------------------------------------
  for (int i = 0; i < 6; i++) {

    int sIndex = i * 3;

    myServos[sIndex].write(targetAngles[sIndex]);
  }

  delay(120);
}
