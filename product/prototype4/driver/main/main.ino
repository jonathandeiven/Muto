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

//Serialization from _____
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
void setup(void);
void loop(void);
void setButton(joyReport_t *joy, uint8_t button);
void clearButton(joyReport_t *joy, uint8_t button);
void sendJoyReport(joyReport_t *report);
void sendButton(joyReport_t *joy, uint8_t button, int value);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  delay(200);


  for (uint8_t ind=0; ind<8; ind++) {
      joyReport.axis[ind] = ind*1000;
  }
    
  for (uint8_t ind=0; ind<sizeof(joyReport.button); ind++) {
        joyReport.button[ind] = 0;
  }

  /*******************
   *    SET PINS
   ******************/
   
  //Module 1 (Top Left)
  module1.pinDet1 = 47;
  module1.pinDet2 = 46;
  module1.pinD1   = 45;
  module1.pinD2   = 44;
  module1.pinD3   = 43;
  module1.pinD4   = 42;
  module1.pinA1   = A2;
  module1.pinA2   = A3;

  //Module 2 (Bottom Left)
  module2.pinDet1 = 26;
  module2.pinDet2 = 27;
  module2.pinD1   = 24;
  module2.pinD2   = 25;
  module2.pinD3   = 22;
  module2.pinD4   = 23;
  module2.pinA1   = A4;
  module2.pinA2   = A5;

  //Module 3 (Top Right)
  module3.pinDet1 = 53;
  module3.pinDet2 = 52;
  module3.pinD1   = 51;
  module3.pinD2   = 50;
  module3.pinD3   = 49;
  module3.pinD4   = 48;
  module3.pinA1   = A0;
  module3.pinA2   = A1;

  //Module 4 (Bottom Right)
  module4.pinDet1 = 41;
  module4.pinDet2 = 40;
  module4.pinD1   = 3;
  module4.pinD2   = 2;
  module4.pinD3   = 5;
  module4.pinD4   = 4;
  module4.pinA1   = A7;
  module4.pinA2   = A6;

  //Static inputs
  controller.btnHome  = 28;
  controller.triggerL = 13;
  controller.triggerR = 29;

  modules[0] = module1;
  modules[1] = module2;
  modules[2] = module3;
  modules[3] = module4;

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
    if ( digitalRead(modules[i].pinDet1) == 0 && 
         digitalRead(modules[i].pinDet2) == 0) {
      //Camera Stick
      controller.RX = modules[i].pinA1;
      controller.RY = modules[i].pinA2;
    } else if ( digitalRead(modules[i].pinDet1) == 0 && 
         digitalRead(modules[i].pinDet2) == 1) {
      //Control Stick
      controller.LX = modules[i].pinA1;
      controller.LY = modules[i].pinA2;
    } else if ( digitalRead(modules[i].pinDet1) == 1 && 
         digitalRead(modules[i].pinDet2) == 0) {
      //Face Buttons
      controller.btnA = modules[i].pinD1;
      controller.btnB = modules[i].pinD2;
      controller.btnX = modules[i].pinD3;
      controller.btnY = modules[i].pinD4;
    } else if ( digitalRead(modules[i].pinDet1) == 1 && 
         digitalRead(modules[i].pinDet2) == 1) {
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
  controllerState.btnHome = digitalRead(controller.btnHome);

  /*****************
   * SERIALIZATION
   ****************/
  //Set joystick value 
  joyReport.axis[0] = map(controllerState.LX, 0, 1023, -32768, 32767);
  joyReport.axis[1] = map(controllerState.LY, 0, 1023, -32768, 32767);
  joyReport.axis[2] = map(controllerState.RX, 0, 1023, -32768, 32767);
  joyReport.axis[3] = map(controllerState.RY, 0, 1023, -32768, 32767);

  //Send the button values
  sendButton(&joyReport, buttonMap.dirUp,    controllerState.dirUp);
  sendButton(&joyReport, buttonMap.dirDown,  controllerState.dirDown);
  sendButton(&joyReport, buttonMap.dirLeft,  controllerState.dirLeft);
  sendButton(&joyReport, buttonMap.dirRight, controllerState.dirRight);
  sendButton(&joyReport, buttonMap.btnA,     controllerState.btnA);
  sendButton(&joyReport, buttonMap.btnB,     controllerState.btnB);
  sendButton(&joyReport, buttonMap.btnX,     controllerState.btnX);
  sendButton(&joyReport, buttonMap.btnY,     controllerState.btnY);
  sendButton(&joyReport, buttonMap.triggerL, controllerState.triggerL);
  sendButton(&joyReport, buttonMap.triggerR, controllerState.triggerR);
  sendButton(&joyReport, buttonMap.btnHome,  controllerState.btnHome);
  
  //Send report serialization
  sendJoyReport(&joyReport);
  
  delay(100);        // delay in between reads for stability
}

// configure buttons
void sendButton(joyReport_t *joy, uint8_t button, int value)
{
  if (value == 1) {
    setButton(&joyReport, button);
  } else {
    clearButton(&joyReport, button);
  }
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

void sendJoyReport(struct joyReport_t *report)
{
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
}

