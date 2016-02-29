/*
 * Muto prototype code for Arduino Mega 2560
 * Works for: 11 digital buttons and 2 analog sticks 
 * Author: Jefferson Wang, Jonathan Deiven, Elvina Tse
 */


// Initialize all Digital Pins

//Module 1
int pin1  = 1;
int pin2  = 2;
int pin3  = 3;
int pin4  = 4;
int pin5  = 5;
int pin6  = 6;

//Module 2
int pin7  = 7;
int pin8  = 8;
int pin9  = 9;
int pin10 = 10;
int pin11 = 11;
int pin12 = 12;

//Module 3
int pin13 = 13;
int pin14 = 14;
int pin15 = 15;
int pin16 = 16;
int pin17 = 17;
int pin18 = 18;

//Module 4
int pin19 = 19;
int pin20 = 20;
int pin21 = 21;
int pin22 = 22;
int pin23 = 23;
int pin24 = 24;

//Static buttons
int leftTrigger  = 25;
int rightTrigger = 26;
int buttonHome   = 27;

// Initialize all Analog Pins

//Module 1
int pinA1 = A1;
int pinA2 = A2;

//Module 2
int pinA3 = A3;
int pinA4 = A4;

//Module 3
int pinA5 = A5;
int pinA6 = A6;

//Module 4
int pinA7 = A7;
int pinA8 = A8;

// Initialize variables for controller variables

// Digital Pins for D-Pad
int d_left, d_up, d_right, d_down;

// Digital Pins for Facebuttons Buttons
int b_a, b_b, b_x, b_y;

// Analog Pins for Movement Joystick
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
  pinMode(pin1,  INPUT);
  pinMode(pin2,  INPUT);
  pinMode(pin3,  INPUT);
  pinMode(pin4,  INPUT);
  pinMode(pin5,  INPUT);
  pinMode(pin6,  INPUT);
  pinMode(pin7,  INPUT);
  pinMode(pin8,  INPUT);
  pinMode(pin9,  INPUT);
  pinMode(pin10, INPUT);
  pinMode(pin11, INPUT);
  pinMode(pin12, INPUT);
  pinMode(pin13, INPUT);
  pinMode(pin14, INPUT);
  pinMode(pin15, INPUT);
  pinMode(pin16, INPUT);
  pinMode(pin17, INPUT);
  pinMode(pin18, INPUT);
  pinMode(pin19, INPUT);
  pinMode(pin20, INPUT);
  pinMode(pin21, INPUT);
  pinMode(pin22, INPUT);
  pinMode(pin23, INPUT);
  pinMode(pin24, INPUT);
  pinMode(leftTrigger,  INPUT); 
  pinMode(rightTrigger, INPUT);
  pinMode(buttonHome,   INPUT);
  
  //Set analog inputs
  pinMode(pinA1, INPUT);
  pinMode(pinA2, INPUT);
  pinMode(pinA3, INPUT);
  pinMode(pinA4, INPUT);
  pinMode(pinA5, INPUT);
  pinMode(pinA6, INPUT);
  pinMode(pinA7, INPUT);
  pinMode(pinA8, INPUT);


  // Digital is 1; Analog is 0
  int pinADCheck = pin1;
  //D-Pad is 1; Face Button is 0
  //Left Stick is 1; Right Stick is 0
  int pinCompCheck = pin2;
  int Comp1 = pin3;
  int Comp2 = pin
  
  for (int i = 0; i < 4; i++) {
    if (pinADCheck = 1) { //Digital
      if (pinComp = 1) { //D-Pad
        d_left = pin3;
        d_up = pin4;
        d_right = pin5;
        d_down = pin6;
      } else { //Face Buttons
        b_a = pin3;
        b_b = pin4;
        b_x = pin5;
        b_y = pin6;
      }
    } else { //Analog
      if (pinComp = 1) { //Movement Stick
        xOne = pinA1;
        yOne = pinA2;
      } else { //Camera Stick
        xTwo = pinA1;
        yTwo = pinA2;
      }
    }
  }
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
