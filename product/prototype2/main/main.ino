/*
 * Muto prototype code for Arduino Mega 2560
 * Works for: 11 digital buttons and 2 analog sticks 
 * Author: Jonathan Deiven
 */

/***********************************
 *  CONTROLLER MAPPING 
 *  
 *  Analogs:
 *  x-axis   <-----> LX
 *  y-axis   <-----> LY
 *  z-axis   <-----> RX
 *  x-rot    <-----> RY
 *  
 *  Digitals:
 *  Button0  <-----> D-Pad Up
 *  Button1  <-----> D-Pad Down
 *  Button2  <-----> D-Pad Left
 *  Button3  <-----> D-Pad Right
 *  Button4  <-----> Left Bumper
 *  Button5  <-----> Right Bumper
 *  Button6  <-----> Home
 *  Button7  <-----> A
 *  Button8  <-----> B
 *  Button9  <-----> X
 *  Button10 <-----> Y
 *  
 ***********************************/

typedef struct joyReport_t {
    int16_t axis[8];
    uint8_t button[5]; // 8 buttons per byte
} joyReport_t;

joyReport_t joyReport;

//Struct for module pins
struct Module
{
   int pinDet1, pinDet2; //detection pins
   int pinD1, pinD2, pinD3, pinD4; //digital pins
   int pinA1, pinA2; //analog pins
   char hello;
} module1, module2, module3, module4;

Module modules[4];

/*Struct to contain pins of controller
 *(aka pins we are actually using) */
struct Controller
{
  int dirUp, dirDown, dirLeft, dirRight;
  int btnA, btnB, btnX, btnY;
  int LX, LY, RX, RY;
  int btnHome, triggerL, triggerR;
} controller;

//Struct to store state of controller
struct ControllerState
{
  int dirUp, dirDown, dirLeft, dirRight;
  int btnA, btnB, btnX, btnY;
  int LX, LY, RX, RY;
  int btnHome, triggerL, triggerR;
};

//Map of buttons to HID
struct ButtonMap
{
  int dirUp    = 0;
  int dirDown  = 1;
  int dirLeft  = 2;
  int dirRight = 3;
  int triggerL = 4;
  int triggerR = 5;
  int btnHome  = 6;
  int btnA     = 7;
  int btnB     = 8;
  int btnX     = 9;
  int btnY     = 10;
} buttonMap;

//Forward function declarations
void setButton(joyReport_t *joy, uint8_t button);
void clearButton(joyReport_t *joy, uint8_t button);
void sendJoyReport(joyReport_t *report);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  modules[0] = module1;
  modules[1] = module2;
  modules[2] = module3;
  modules[3] = module4;

  /*******************
   *    SET PINS
   ******************/
   
  //Module 1
  module1.pinDet1 = 1;
  module1.pinDet1 = 1;
  module1.pinD1   = 1;
  module1.pinD2   = 1;
  module1.pinD3   = 1;
  module1.pinD4   = 1;
  module1.pinA1   = A1;
  module1.pinA2   = A1;

  //Module 2
  module2.pinDet1 = 1;
  module2.pinDet1 = 1;
  module2.pinD1   = 1;
  module2.pinD2   = 1;
  module2.pinD3   = 1;
  module2.pinD4   = 1;
  module2.pinA1   = A1;
  module2.pinA2   = A1;

  //Module 3
  module3.pinDet1 = 1;
  module3.pinDet1 = 1;
  module3.pinD1   = 1;
  module3.pinD2   = 1;
  module3.pinD3   = 1;
  module3.pinD4   = 1;
  module3.pinA1   = A1;
  module3.pinA2   = A1;

  //Module 4
  module4.pinDet1 = 1;
  module4.pinDet1 = 1;
  module4.pinD1   = 1;
  module4.pinD2   = 1;
  module4.pinD3   = 1;
  module4.pinD4   = 1;
  module4.pinA1   = A1;
  module4.pinA2   = A1;

  //Static inputs
  controller.btnHome  = 1;
  controller.triggerL = 1;
  controller.triggerR = 1;

  /*******************
   *    DETECTION
   ******************/
   
  //Set the detection pins for input
  for (int i = 0; i < 4; i++) {
    pinMode(modules[i].pinDet1, INPUT);
    pinMode(modules[i].pinDet2, INPUT);
  }

  //Based on detection pins, set controller inputs
  for (int i = 0; i < 4; i++) {
    if ( modules[i].pinDet1 == 0 && modules[i].pinDet2 == 0) {
      //Camera Stick
      controller.RX = modules[i].pinA1;
      controller.RY = modules[i].pinA2;
    } else if ( modules[i].pinDet1 == 0 && modules[i].pinDet2 == 1) {
      //Control Stick
      controller.LX = modules[i].pinA1;
      controller.LY = modules[i].pinA2;
    } else if ( modules[i].pinDet1 == 1 && modules[i].pinDet2 == 0) {
      //Face Buttons
      controller.btnA = modules[i].pinD1;
      controller.btnB = modules[i].pinD2;
      controller.btnX = modules[i].pinD3;
      controller.btnY = modules[i].pinD4;
    } else if ( modules[i].pinDet1 == 1 && modules[i].pinDet2 == 1) {
      //D-Pad
      controller.dirUp    = modules[i].pinD1;
      controller.dirDown  = modules[i].pinD2;
      controller.dirLeft  = modules[i].pinD3;
      controller.dirRight = modules[i].pinD4;
    }
  }

  //Set game controller inputs as pins
  pinMode(controller.LX, INPUT);
  pinMode(controller.LY, INPUT);
  pinMode(controller.RX, INPUT);
  pinMode(controller.RY, INPUT);
  pinMode(controller.dirUp, INPUT);
  pinMode(controller.dirDown, INPUT);
  pinMode(controller.dirLeft, INPUT);
  pinMode(controller.dirRight, INPUT);
  pinMode(controller.btnA, INPUT);
  pinMode(controller.btnB, INPUT);
  pinMode(controller.btnX, INPUT);
  pinMode(controller.btnY, INPUT);
  pinMode(controller.btnHome, INPUT);
  pinMode(controller.triggerL, INPUT);
  pinMode(controller.triggerR, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  struct ControllerState controllerState;

  //Read analog input pins
  controllerState.LX = analogRead(controller.LX);
  controllerState.LY = analogRead(controller.LY);
  controllerState.RX = analogRead(controller.RX);
  controllerState.RY = analogRead(controller.RY);

  //Read digital trigger pins
  controllerState.triggerL = digitalRead(controller.triggerL);
  controllerState.triggerR = digitalRead(controller.triggerR);

  //Read digital D-Pad pins
  controllerState.dirUp    = digitalRead(controller.dirUp);
  controllerState.dirDown  = digitalRead(controller.dirDown);
  controllerState.dirLeft  = digitalRead(controller.dirLeft);
  controllerState.dirRight = digitalRead(controller.dirRight);

  //Read digital button pins
  controllerState.btnA = digitalRead(controller.btnA);
  controllerState.btnB = digitalRead(controller.btnB);
  controllerState.btnX = digitalRead(controller.btnX);
  controllerState.btnY = digitalRead(controller.btnY);

  //Read digital home button pin
  controllerState.btnHome = analogRead(controller.btnHome);

    // Print feedback of inputs for debugging
  Serial.print("Triggers Left: " );
  Serial.print(controllerState.triggerL);
  Serial.print(" Right: ");
  Serial.print(controllerState.triggerR);
  Serial.print(" | D-Pad Left: ");
  Serial.print( controllerState.dirLeft);
  Serial.print(" Up: ");
  Serial.print(controllerState.dirUp);
  Serial.print(" Down: ");
  Serial.print(controllerState.dirDown);
  Serial.print(" Right: ");
  Serial.println(controllerState.dirRight);
  Serial.print("Face A: ");
  Serial.print(controllerState.btnA);
  Serial.print(" B: ");
  Serial.print(controllerState.btnB);
  Serial.print(" X: ");
  Serial.print(controllerState.btnX);
  Serial.print(" Y: ");
  Serial.print(controllerState.btnY);
  Serial.print(" | Home: ");
  Serial.print(controllerState.btnHome);
  Serial.print(" | Analogs X1: ");
  Serial.print(controllerState.LX);
  Serial.print(" Y1: ");
  Serial.print(controllerState.LY);
  Serial.print(" X2: ");
  Serial.print(controllerState.RX);
  Serial.print(" Y2: ");
  Serial.println(controllerState.RY);
  Serial.println(" ");
  
  delay(100);        // delay in between reads for stability
}

// turn a button on
void setButton(joyReport_t *joy, uint8_t button)
{
    uint8_t index = button/8;
    uint8_t bit = button - 8*index;

    joy->button[index] |= 1 << bit;
}

// turn a button off
void clearButton(joyReport_t *joy, uint8_t button)
{
    uint8_t index = button/8;
    uint8_t bit = button - 8*index;

    joy->button[index] &= ~(1 << bit);
}
