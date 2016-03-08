/*
 * Muto prototype code for Arduino Mega 2560
 * Works for: 11 digital buttons and 2 analog sticks 
 * Author: Jonathan Deiven
 */

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
  module1.pinA1   = 1;
  module1.pinA2   = 1;

  //Module 2
  module2.pinDet1 = 1;
  module2.pinDet1 = 1;
  module2.pinD1   = 1;
  module2.pinD2   = 1;
  module2.pinD3   = 1;
  module2.pinD4   = 1;
  module2.pinA1   = 1;
  module2.pinA2   = 1;

  //Module 3
  module3.pinDet1 = 1;
  module3.pinDet1 = 1;
  module3.pinD1   = 1;
  module3.pinD2   = 1;
  module3.pinD3   = 1;
  module3.pinD4   = 1;
  module3.pinA1   = 1;
  module3.pinA2   = 1;

  //Module 4
  module4.pinDet1 = 1;
  module4.pinDet1 = 1;
  module4.pinD1   = 1;
  module4.pinD2   = 1;
  module4.pinD3   = 1;
  module4.pinD4   = 1;
  module4.pinA1   = 1;
  module4.pinA2   = 1;

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

  delay(50);        // delay in between reads for stability
}
