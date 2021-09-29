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
unsigned long current_time = 0 ;
unsigned long previous_time = 0 ;
unsigned long time_interval = 0 ;

int random_pos_x = 4 ;
int random_pos_y = 4 ;

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

    if((current_pos_x == random_pos_x) && (current_pos_y ==  random_pos_y)){
      GenerateRandom();
    }
    lit_random();
    
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
    
    current_time = millis() ;
    time_interval = current_time - previous_time ;
    if(time_interval>=300){
    current_pos_x++;
    previous_time = current_time ;
    }
    
    if (current_pos_x == 8) {
      current_pos_x = 0;
    }
  }
}
void go_left() {

  while (current_pos_x >= 0) {

    if((current_pos_x == random_pos_x) && (current_pos_y ==  random_pos_y)){
      GenerateRandom();
    }
    lit_random();
    
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
    
    current_time = millis() ;
    time_interval = current_time - previous_time ;
    if(time_interval>=300){
    current_pos_x--;
    previous_time = current_time ;
    }
    
    if (current_pos_x == -1) {
      current_pos_x = 7;
    }
  }
}
void go_down() {

  while (current_pos_y <= 7) {
    
    if((current_pos_x == random_pos_x) && (current_pos_y ==  random_pos_y)){
      GenerateRandom();
    }
    lit_random();
    
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
    current_time = millis() ;
    time_interval = current_time - previous_time ;
    if(time_interval>=300){
    current_pos_y++;
    previous_time = current_time ;
    }
    if (current_pos_y == 8) {
      current_pos_y = 0;
    }

  }
}
void go_up() {

  while (current_pos_y >= 0) {
    if((current_pos_x == random_pos_x) && (current_pos_y ==  random_pos_y)){
      GenerateRandom();
    }
    lit_random();

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

    current_time = millis() ;
    time_interval = current_time - previous_time ;
    if(time_interval>=300){
    current_pos_y--;
    previous_time = current_time ;
    }

    if (current_pos_y == -1) {
      current_pos_y = 7;
    }
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

void GenerateRandom(){
  random_pos_x = random(7);
  random_pos_y = random(7);
  }
  
void lit_random(){
  lit(random_pos_x,random_pos_y); // x -> cathode :: y-> anode 
  }
