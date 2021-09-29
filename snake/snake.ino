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

int pos_x_array[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int pos_y_array[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int snake_length = 1 ;

int random_pos_x = 0 ; // = 4 ;
int random_pos_y = 0 ; // = 4 ;

void setup() {
  int i ;
  for (i = 0; i <= 7; i++) {
    pinMode(cathode[i], OUTPUT);
    pinMode(anode[i], OUTPUT);
  }
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  resetAnode();
  resetCathode();

}

void loop() {
  go_right();
}

////////////////////////////FUNCTIONS////////////////////////
void go_right() {
  int i = 0 ;
  while (current_pos_x <= 7) {

    if((current_pos_x == random_pos_x) && (current_pos_y ==  random_pos_y)){
      GenerateRandom();
      snake_length++ ; 
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
    
    for(i=0;i<snake_length;i++){
    lit(pos_x_array[i], pos_y_array[i]);
    } 
    
    current_time = millis() ;
    time_interval = current_time - previous_time ;
    
    if(time_interval>=300){
    current_pos_x++;
    previous_time = current_time ;

    if (current_pos_x == 8) {
      current_pos_x = 0;
    }
    
    for(i=(snake_length-1);i>0;i--){
      pos_x_array[i] = pos_x_array[i-1];
      pos_y_array[i] = pos_y_array[i-1];
    }
    pos_x_array[0] = current_pos_x ;
    pos_y_array[0] = current_pos_y ;
    }
    

  }
}
void go_left() {
  int i = 0  ;
  while (current_pos_x >= 0) {

    if((current_pos_x == random_pos_x) && (current_pos_y ==  random_pos_y)){
      GenerateRandom();
      snake_length++ ;
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
    for(i=0;i<snake_length;i++){
    lit(pos_x_array[i], pos_y_array[i]);
    } 
    
    current_time = millis() ;
    time_interval = current_time - previous_time ;
    if(time_interval>=300){
    current_pos_x--;
    previous_time = current_time ;
    if (current_pos_x == -1) {
      current_pos_x = 7;
    }
    for(i=(snake_length-1);i>0;i--){
      pos_x_array[i] = pos_x_array[i-1];
      pos_y_array[i] = pos_y_array[i-1];
    }
    pos_x_array[0] = current_pos_x ;
    pos_y_array[0] = current_pos_y ;
    }
    

  }
}
void go_down() {
  int i = 0 ;
  while (current_pos_y <= 7) {
    
    if((current_pos_x == random_pos_x) && (current_pos_y ==  random_pos_y)){
      GenerateRandom();
      snake_length++ ;
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

    for(i=0;i<snake_length;i++){
    lit(pos_x_array[i], pos_y_array[i]);
    } 
    current_time = millis() ;
    time_interval = current_time - previous_time ;
    if(time_interval>=300){
    current_pos_y++;
    previous_time = current_time ;
    
    if (current_pos_y == 8) {
      current_pos_y = 0;
    }
    for(i=(snake_length-1);i>0;i--){
      pos_x_array[i] = pos_x_array[i-1];
      pos_y_array[i] = pos_y_array[i-1];
    }
    pos_x_array[0] = current_pos_x ;
    pos_y_array[0] = current_pos_y ;
    }


  }
}
void go_up() {
  int i = 0 ;
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
    for(i=0;i<snake_length;i++){
    lit(pos_x_array[i], pos_y_array[i]);
    } 

    current_time = millis() ;
    time_interval = current_time - previous_time ;
    if(time_interval>=300){
    current_pos_y--;
    previous_time = current_time ;
    
    if (current_pos_y == -1) {
      current_pos_y = 7;
    }
    for(i=(snake_length-1);i>0;i--){
      pos_x_array[i] = pos_x_array[i-1];
      pos_y_array[i] = pos_y_array[i-1];
    }
    pos_x_array[0] = current_pos_x ;
    pos_y_array[0] = current_pos_y ;
    }


  }
}

void lit(int cathodePin, int anodePin) {
  resetCathode();
  resetAnode();
  digitalWrite(cathode[cathodePin], 1);
  digitalWrite(anode[anodePin], 0);
  delay(3);
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
