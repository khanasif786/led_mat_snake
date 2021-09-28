// LED matrix snake
// author - Asif khan
// github - khanasif786

// cathode -> positive
// anode -> negative

int cathode[8] = {0, 1, 2, 3, 4, 5, 6, 7};
int anode[8] = {8, 9, 10, 11, 12, 13, A0, A1};
int current_pos_x = 0 ;
int current_pos_y = 0 ;
char CurrentState = 'r';

void setup() {
  int i ;
  for (i = 0; i <= 7; i++) {
    pinMode(cathode[i], OUTPUT);
    pinMode(anode[i], OUTPUT);
  }
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  resetAnode();
  resetCathode();

}

void loop() {
  go_right();
}

////////////////////////////FUNCTIONS////////////////////////
void go_right() {

  while (current_pos_x <= 7) {
    CheckState();
    if (CurrentState != 'r') {
      if (CurrentState == 'f') {
        go_up();
      }
      if (CurrentState == 'b') {
        go_down();
      }
    }
    lit(current_pos_x, current_pos_y);
    current_pos_x++;
    if (current_pos_x == 8) {
      current_pos_x = 0;
    }
    delay(300);
  }
}
void go_left() {

  while (current_pos_x >= 0) {
    CheckState();
    if (CurrentState != 'l') {
      if (CurrentState == 'f') {
        go_up();
      }
      if (CurrentState == 'b') {
        go_down();
      }
    }
    lit(current_pos_x, current_pos_y);
    current_pos_x--;
    if (current_pos_x == -1) {
      current_pos_x = 7;
    }
    delay(300);
  }
}
void go_down() {

  while (current_pos_y <= 7) {
    CheckState();
    if (CurrentState != 'b') {
      if (CurrentState == 'r') {
        go_right();
      }
      if (CurrentState == 'l') {
        go_left();
      }
    }
    lit(current_pos_x, current_pos_y);
    current_pos_y++;
    if (current_pos_y == 8) {
      current_pos_y = 0;
    }
    delay(300);
  }
}
void go_up() {

  while (current_pos_y >= 0) {
    CheckState();
    if (CurrentState != 'f') {
      if (CurrentState == 'r') {
        go_right();
      }
      if (CurrentState == 'l') {
        go_left();
      }
    }
    lit(current_pos_x, current_pos_y);
    current_pos_y--;
    if (current_pos_y == -1) {
      current_pos_y = 7;
    }
    delay(300);
  }
}

void lit(int cathodePin, int anodePin) {
  resetCathode();
  resetAnode();
  digitalWrite(cathode[cathodePin], 1);
  digitalWrite(anode[anodePin], 0);
}

void resetCathode() {
  int i ;
  for (i = 0; i <= 7; i++) {
    digitalWrite(anode[i], 1); // giving opposite values
  }
}

void resetAnode() {
  int i ;
  for (i = 0; i <= 7; i++) {
    digitalWrite(cathode[i], 0); // giving opposite values
  }
}

void CheckState() {
  if (digitalRead(A2) == 0) {
    CurrentState = 'f';
  }
  if (digitalRead(A3) == 0) {
    CurrentState = 'r';
  }
  if (digitalRead(A4) == 0) {
    CurrentState = 'b';
  }
  if (digitalRead(A5) == 0) {
    CurrentState = 'l';
  }
}
