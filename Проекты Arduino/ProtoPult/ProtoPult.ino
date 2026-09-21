int L_JOY_Y;
int R_JOY_X;
int velocity, rotate_velocity, L_V, R_V;
boolean L_dir, R_dir, tank;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // Необходимо снять показания и разобраться с наводками:
  L_JOY_Y = map(analogRead(A7), 0, 1023, 0, 100);
  R_JOY_X = map(analogRead(A5), 0, 1023, 0, 100);
  velocity = 50 - L_JOY_Y;
  velocity = map(velocity, 0, 50, 0, 255);
  velocity = map(velocity, 0, 249, 0, 255);
  rotate_velocity = 50 - R_JOY_X; 
  rotate_velocity = map(rotate_velocity, 0, 50, 0, 255);
  // Избегаем центрального положения левого джойстика
  if (velocity >= 30){
    L_dir = true; // едем вперед
    R_dir = true; // едем вперед
    rotate_velocity = map(rotate_velocity, -249, 249, -100, 100);
    rotate_velocity = constrain(rotate_velocity, -velocity/3, velocity/3);
    if (rotate_velocity >=50){
      L_V = constrain(velocity + rotate_velocity, 0, 255);
      R_V = constrain(velocity - rotate_velocity, 0, 255);
    }
    else if (rotate_velocity <= -10){
      L_V = constrain(velocity + rotate_velocity, 0, 255);
      R_V = constrain(velocity - rotate_velocity, 0, 255);
    }
    else{
        L_V = velocity;
        R_V = velocity;
    }
    tank = false; // не танкуем
  }
  else if (velocity <= -50){
    L_dir = false; // едем Назад
    R_dir = false; // едем Назад
    rotate_velocity = map(rotate_velocity, -249, 249, -100, 100);
    rotate_velocity = constrain(rotate_velocity, -velocity/3, velocity/3);
    if (rotate_velocity >=10){
      L_V = constrain(abs(velocity) - rotate_velocity, 0, 255);
      R_V = constrain(abs(velocity) + rotate_velocity, 0, 255);
    }
    else if (rotate_velocity <= -10){
      L_V = constrain(abs(velocity) - rotate_velocity, 0, 255);
      R_V = constrain(abs(velocity) + rotate_velocity, 0, 255);
    }
    else{
        L_V = abs(velocity);
        R_V = abs(velocity);
    }
    tank = false; // не танкуем
  }
  else{
    rotate_velocity = map(rotate_velocity, -249, 249, -255, 255);
    if (rotate_velocity >= 30){
      L_dir = true; // едем Вперед
      R_dir = false; // едем Назад
      L_V = rotate_velocity;
      R_V = rotate_velocity;
    }
    else if (rotate_velocity <= -30){
      L_dir = false; // едем Назад
      R_dir = true; // едем Вперед
      L_V = abs(rotate_velocity);
      R_V = abs(rotate_velocity);
    }
    tank = true; // Танкуем
  }
  Serial.print(L_V);
  Serial.print("  ");
  Serial.println(R_V);
}
