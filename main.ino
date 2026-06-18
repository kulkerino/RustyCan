// --- PINY PRE MOTORY ---
const int M1F = 16; 
const int M1B = 17; 
const int M2F = 25; 
const int M2B = 26; 

// --- PINY PRE SENZORY ---
const int Sl = 34; 
const int Sm = 36; 
const int Sr = 39; 

// --- NASTAVENIE RÝCHLOSTI A PAUZY ---
int speed_fwd = 100;       // Rýchlosť rovno
int turn_power = 70;      // Sila vonkajšieho kolesa v zákrute (aby prekonalo trenie)
// int step_delay = 40;       // Magická pauza v milisekundách (čas na dokončenie pohybu)

bool leftReading = 0;
bool middleReading = 0;
bool rightReading = 0;


void setup() {
  Serial.begin(115200); 

  pinMode(M1F, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2F, OUTPUT);
  pinMode(M2B, OUTPUT);

  pinMode(Sl, INPUT);
  pinMode(Sm, INPUT);
  pinMode(Sr, INPUT);
}

void loop() {
  leftReading = digitalRead(Sl);
  middleReading = digitalRead(Sm);
  rightReading = digitalRead(Sr);

  if(middleReading){
    forward();
  
  }
  else if(leftReading){
    adjust_left();
  }
  else if(rightReading){
    adjust_right();
  }
}

// --- FUNKCIE PRE POHYB ---

void forward() {
  analogWrite(M1F, speed_fwd);
  analogWrite(M1B, 0);

  analogWrite(M2F, speed_fwd);
  analogWrite(M2B, 0);
}

void turn_left() {
  // Pivot otočka: Ľavé koleso čiastočne cúva, pravé tlačí
  analogWrite(M1F, 0);
  analogWrite(M1B, 0); 

  analogWrite(M2F, turn_power);
  analogWrite(M2B, 0);
}

void turn_right() {
  // Pivot otočka: Ľavé koleso tlačí, pravé čiastočne cúva
  analogWrite(M1F, turn_power);
  analogWrite(M1B, 0);

  analogWrite(M2F, 0);
  analogWrite(M2B, 0);
}

void adjust_right() {
    while(!middleReading) {
        middleReading = digitalRead(Sm);
        turn_right();
        delay(10);
    }
    forward();
}

void adjust_left() {
    while(!middleReading) {
        middleReading = digitalRead(Sm);
        turn_left();
        delay(10);
    }
    forward();
}
