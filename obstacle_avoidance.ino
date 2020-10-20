// motor components
const int PWM1 = 11;
const int inA1 = 8;
const int inB1 = 12;
const int PWM2 = 6;
const int inA2 = 4;
const int inB2 = 7;

// sensor components
const int echo_mid = 9;
const int trig_mid = 13;
const int echo_left = 10;
const int echo_right = 3;
const int trig2 = 2;      // left and right sensor connection
// left, middle, right in perspective of robot facing front
  // gnd, echo-PWN, trig-digitial, vcc

long duration_mid; 
int distance_mid; 
long duration_left; 
int distance_left; 
long duration_right; 
int distance_right; 

void setup() {
  // set all the motor control pins to outputs
  pinMode(PWM1, OUTPUT);
  pinMode(inA1, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB2, OUTPUT);

// sensor pins
  pinMode(trig_mid, OUTPUT); 
  pinMode(echo_mid, INPUT); 
  pinMode(echo_left, INPUT); 
  pinMode(echo_right, INPUT);   
  pinMode(trig2, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  // distance calculations
  digitalWrite(trig_mid, LOW);
  delay(250);
  digitalWrite(trig_mid, HIGH);
  delay(250);
  digitalWrite(trig_mid, LOW);
  duration_mid = pulseIn(echo_mid, HIGH);
  distance_mid = duration_mid * 0.034 / 2; 

  digitalWrite(trig2, LOW);
  delay(250);
  digitalWrite(trig2, HIGH);
  delay(250);
  digitalWrite(trig2, LOW);
  duration_left = pulseIn(echo_left, HIGH);
  distance_left = duration_left * 0.034 / 2; 

  digitalWrite(trig2, LOW);
  delay(250);
  digitalWrite(trig2, HIGH);
  delay(250);
  digitalWrite(trig2, LOW);
  duration_right = pulseIn(echo_right, HIGH);
  distance_right = duration_right * 0.034 / 2;   


  // motor controls
  analogWrite(PWM1, 20);
  analogWrite(PWM2, 28);
  
  if (distance_mid <= 35) {
    if (distance_right <= 45) {
      digitalWrite(inA1, HIGH);
      digitalWrite(inB1, LOW);
      digitalWrite(inA2, HIGH);
      digitalWrite(inB2, LOW); 
      delay(120);
    }
    else {
      digitalWrite(inA1, LOW);
      digitalWrite(inB1, HIGH);
      digitalWrite(inA2, LOW);
      digitalWrite(inB2, HIGH); 
      delay(120);
    }
  }
  
  else if (distance_right <= 25) {
    digitalWrite(inA1, HIGH);
    digitalWrite(inB1, LOW);
    digitalWrite(inA2, HIGH);
    digitalWrite(inB2, LOW); 
    delay(60);
  }
  else if (distance_left <= 25) {
    digitalWrite(inA1, LOW);
    digitalWrite(inB1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB2, HIGH); 
    delay(60);
  }

  
  else {
    digitalWrite(inA1, LOW);
    digitalWrite(inB1, HIGH);
    digitalWrite(inA2, HIGH);
    digitalWrite(inB2, LOW); 
    delay(60);
  }
  

}
