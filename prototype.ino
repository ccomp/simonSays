#define arr_len(x) (sizeof(x)/sizeof(*x))
const int FSR0 = A0;
const int FSR1 = A1;
const int FSR2 = A2;
const int FSR3 = A3;
int a, b, c, d, e, f, g, h; //these are for pointers to get a distinct memory address
//Arduino has an issue where pointers point to the same place when instantiated globally

const int LED0 = 3;
int *ledState0 = &e;
unsigned long previousMillis0 = 0;
long onTime00 = 250;
long offTime00 = 750;
long onTime10 = 500;
long offTime10 = 500;

const int LED1 = 4;
int *ledState1 = &f;
unsigned long previousMillis1 = 0;
long onTime01 = 250;
long offTime01 = 750;
long onTime11 = 500;
long offTime11 = 500;

const int LED2 = 5;
int *ledState2 = &g;
unsigned long previousMillis2 = 0;
long onTime02 = 250;
long offTime02 = 750;

const int LED3 = 6;
int *ledState3 = &h;
unsigned long previousMillis3 = 0;
long onTime03 = 250;
long offTime03 = 750;

int *ledStates[4] = {ledState0, ledState1, ledState2, ledState3};
int gameArray[4] = {0, 0, 0, 0};

int *b0 = &a;
int *b1 = &b;
int *b2 = &c;
int *b3 = &d;
int *voltages[4] = {b0, b1, b2, b3};
int voltagesLength = 4;
bool GAME_ON, FIRSTLOAD, LEVEL1;

void setup() {
  // put your setup code here, to run once:
  *ledState0 = LOW;
  *ledState1 = LOW;
  *ledState2 = LOW;
  *ledState3 = LOW;
  FIRSTLOAD = true;
  LEVEL1 = false;
  GAME_ON = false;
  pinMode(FSR0, INPUT);
  pinMode(FSR1, INPUT);
  pinMode(FSR2, INPUT);
  pinMode(FSR3, INPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  readCircuit();
  if (FIRSTLOAD == true) {
    level0(currentMillis);
    for (int i = 0; i < voltagesLength; i++) {
      if (*voltages[i] >= 10) {
        FIRSTLOAD = false;
        unlightAll();
        LEVEL1 = true;
        break;
      }
    }
  } else {
    analogWrite(LED0, *b0);
    analogWrite(LED1, *b1);
    analogWrite(LED2, *b2);
    analogWrite(LED3, *b3); 
  }
  
//  
//  if (LEVEL1 == true) {
//    level1(currentMillis);
//    unlightAll();
//    GAME_ON = true;
//    while (GAME_ON == true) {
//      unsigned long gameMillis = currentMillis;
//      if (currentMillis - gameMillis >= 5000) {
//        GAME_ON = false;
//        LEVEL1 = false;
//        FIRSTLOAD = true;
//        *ledState3 = HIGH; //use this for game over
//        unlightAll();
//        digitalWrite(LED3, *ledState3);
//        break;
//      }
//      readCircuit();
//      analogWrite(LED0, *b0);
//      analogWrite(LED1, *b1);
//      analogWrite(LED2, *b2);
//      analogWrite(LED3, *b3);
//      for (int i = 0; i < voltagesLength; i++) {
//        if (*voltages[i] >= 10) {
//          gameArray[i] = *voltages[i];
//        }
//      }
//      if ((gameArray[0] != 0) && (gameArray[1] != 0) && (gameArray[2] == 0) && (gameArray[3] == 0)) {
//        LEVEL1 = false;
//        unlightAll();
//        *ledState2 = HIGH;
//        digitalWrite(LED2, *ledState2);
//        GAME_ON = false;
//        for (int i = 0; i < 4; i++) {
//          gameArray[i] = 0;
//        }
//      } else {
//        GAME_ON = false;
//        LEVEL1 = false;
//        FIRSTLOAD = true;
//        *ledState3 = HIGH;
//        unlightAll();
//        digitalWrite(LED3, *ledState3);
//      }
//    }
//  }
  
}

void unlightAll() {
  *ledState0 = LOW;
  *ledState1 = LOW;
  *ledState2 = LOW;
  *ledState3 = LOW;
  digitalWrite(LED0, *ledState0);
  digitalWrite(LED1, *ledState1);
  digitalWrite(LED2, *ledState2);
  digitalWrite(LED3, *ledState3);
}

void readCircuit() {
  *b0 = analogRead(FSR0)/4;
  delay(10);
  *b1 = analogRead(FSR1)/4;
  delay(10);
  *b2 = analogRead(FSR2)/4;
  delay(10);
  *b3 = analogRead(FSR3)/4;
  delay(10);
}

void level1(unsigned long currentTime) {
  if ((*ledState0 == HIGH) && (currentTime - previousMillis0 >= onTime10)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH && i != 0) temp = true; 
    }
    if (temp == false) {
      *ledState0 = LOW;
      previousMillis0 = currentTime;
      digitalWrite(LED0, *ledState0); 
    }
  }
  else if ((*ledState0 == LOW) && (currentTime - previousMillis0 >= offTime10)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH) temp = true; 
    }
    if (temp == false) {
     *ledState0 = HIGH;
      previousMillis0 = currentTime;
      digitalWrite(LED0, *ledState0); 
    }
  }
  if ((*ledState1 == HIGH) && (currentTime - previousMillis1 >= onTime11)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH && i != 1) temp = true; 
    }
    if (temp == false) {
     *ledState1 = LOW;
      previousMillis1 = currentTime;
      digitalWrite(LED1, *ledState1); 
    }
  }
  else if ((*ledState1 == LOW) && (currentTime - previousMillis1 >= offTime11)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH) temp = true; 
    }
    if (temp == false) {
     *ledState1 = HIGH;
      previousMillis1 = currentTime;
      digitalWrite(LED1, *ledState1); 
    }
  }
}

void level0(unsigned long currentTime) {
  if ((*ledState0 == HIGH) && (currentTime - previousMillis0 >= onTime00)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH && i != 0) temp = true; 
    }
    if (temp == false) {
      *ledState0 = LOW;
      previousMillis0 = currentTime;
      digitalWrite(LED0, *ledState0); 
    }
  }
  else if ((*ledState0 == LOW) && (currentTime - previousMillis0 >= offTime00)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH) temp = true; 
    }
    if (temp == false) {
     *ledState0 = HIGH;
      previousMillis0 = currentTime;
      digitalWrite(LED0, *ledState0); 
    }
  }
  if ((*ledState1 == HIGH) && (currentTime - previousMillis1 >= onTime01)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH && i != 1) temp = true; 
    }
    if (temp == false) {
     *ledState1 = LOW;
      previousMillis1 = currentTime;
      digitalWrite(LED1, *ledState1); 
    }
  }
  else if ((*ledState1 == LOW) && (currentTime - previousMillis1 >= offTime01)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH) temp = true; 
    }
    if (temp == false) {
     *ledState1 = HIGH;
      previousMillis1 = currentTime;
      digitalWrite(LED1, *ledState1); 
    }
  }
  if ((*ledState2 == HIGH) && (currentTime - previousMillis2 >= onTime02)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH && i != 2) temp = true; 
    }
    if (temp == false) {
     *ledState2 = LOW;
      previousMillis2 = currentTime;
      digitalWrite(LED2, *ledState2); 
    }
  }
  else if ((*ledState2 == LOW) && (currentTime - previousMillis2 >= offTime02)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH) temp = true; 
    }
    if (temp == false) {
     *ledState2 = HIGH;
      previousMillis2 = currentTime;
      digitalWrite(LED2, *ledState2); 
    }
  }
  if ((*ledState3 == HIGH) && (currentTime - previousMillis3 >= onTime03)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH && i != 3) temp = true; 
    }
    if (temp == false) {
     *ledState3 = LOW;
      previousMillis3 = currentTime;
      digitalWrite(LED3, *ledState3); 
    }
  }
  else if ((*ledState3 == LOW) && (currentTime - previousMillis3 >= offTime03)) {
    bool temp = false;
    for (int i = 0; i < 4; i++) {
      if (*ledStates[i] == HIGH) temp = true; 
    }
    if (temp == false) {
     *ledState3 = HIGH;
      previousMillis3 = currentTime;
      digitalWrite(LED3, *ledState3); 
    }
  }
}

