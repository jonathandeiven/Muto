/*
 * Muto prototype code for Arduino Mega 2560
 * Works for: 11 digital buttons and 2 analog sticks 
 * Author: Jefferson Wang, Jonathan Deiven, Elvina Tse
 */

// Digital Pins for Triggers
int leftTrigger  = 22;
int rightTrigger = 24;

// Digital Pins for D-Pad
int d_left       = 26;
int d_up         = 28;
int d_right      = 32;
int d_down       = 30;

// Digital Pins for Buttons
int b_a          = 34;
int b_b          = 36;
int b_x          = 38;
int b_y          = 40;
int b_muto       = 42;

//Analog Pins for Movement Joystick
int xOne = A0;
int yOne = A1;
int xPositionOne = 0;
int yPositionOne = 0;

//Analog Pins for Camera Joystick
int xTwo = A8;
int yTwo = A9;
int xPositionTwo = 0;
int yPositionTwo = 0;

//Setup
void setup() {
  //Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  //Set digital inputs
  pinMode(rightTrigger, INPUT);
  pinMode(leftTrigger, INPUT);
  pinMode(d_left, INPUT);
  pinMode(d_up, INPUT);
  pinMode(d_down, INPUT);
  pinMode(d_right, INPUT);
  pinMode(b_a, INPUT);
  pinMode(b_b, INPUT);
  pinMode(b_x, INPUT);
  pinMode(b_y, INPUT);
  pinMode(b_muto, INPUT);
  
  //Set analog inputs
  pinMode(xOne, INPUT);
  pinMode(yOne, INPUT);
  pinMode(xTwo, INPUT);
  pinMode(yTwo, INPUT);
}

//Loop
void loop() {
  // read the analog pins
  xPositionOne = analogRead(xOne);
  yPositionOne = analogRead(yOne);
  xPositionTwo = analogRead(xTwo);
  yPositionTwo = analogRead(yTwo);
  
  // read the digital trigger pins
  int rightState   = digitalRead(rightTrigger);
  int leftState    = digitalRead(leftTrigger);
  
  // read the digital D-pad pins
  int dpadLState   = digitalRead(d_left);
  int dpadUState   = digitalRead(d_up);
  int dpadRState   = digitalRead(d_right);
  int dpadDState   = digitalRead(d_down);
  
  // read the digital button pins
  int btnAState    = digitalRead(b_a);
  int btnBState    = digitalRead(b_b);
  int btnXState    = digitalRead(b_x);
  int btnYState    = digitalRead(b_y);
  int btnMutoState = digitalRead(b_muto);
  
  // Print feedback of inputs for debugging
  Serial.print("Triggers Left: " );
  Serial.print(leftState);
  Serial.print(" Right: ");
  Serial.print(rightState);
  Serial.print(" | D-Pad Left: ");
  Serial.print(dpadLState);
  Serial.print(" Up: ");
  Serial.print(dpadUState);
  Serial.print(" Down: ");
  Serial.print(dpadDState);
  Serial.print(" Right: ");
  Serial.println(dpadRState);
  Serial.print("Face A: ");
  Serial.print(btnAState);
  Serial.print(" B: ");
  Serial.print(btnBState);
  Serial.print(" X: ");
  Serial.print(btnXState);
  Serial.print(" Y: ");
  Serial.print(btnYState);
  Serial.print(" | Home: ");
  Serial.print(btnMutoState);
  Serial.print(" | Analogs X1: ");
  Serial.print(xPositionOne);
  Serial.print(" Y1: ");
  Serial.print(yPositionOne);
  Serial.print(" X2: ");
  Serial.print(xPositionTwo);
  Serial.print(" Y2: ");
  Serial.println(yPositionTwo);
  Serial.println(" ");
  
  delay(2); // delay in between reads for stability
}
