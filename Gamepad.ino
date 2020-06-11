#include <XInput.h>

// Setup
const boolean UseLeftJoystick   = true;  // set to true to enable left joystick
const boolean InvertLeftYAxis   = true;  // set to true to use inverted left joy Y
const boolean InvertLeftXAxis   = true;

const boolean UseRightJoystick  = false;  // set to true to enable right joystick
const boolean InvertRightYAxis  = false;  // set to true to use inverted right joy Y

const boolean UseTriggerButtons = false;   // set to false if using analog triggers

const int ADC_Max = 1023;  // 10 bit

// Joystick Pins
const int Pin_LeftJoyX  = A0;
const int Pin_LeftJoyY  = A1;
const int Pin_RightJoyX = A2;
const int Pin_RightJoyY = A3;

const int Pin_ButtonL3 = 0;
const int Pin_ButtonR3 = 1;

// Button Pins
const int Pin_ButtonA     = 5;
const int Pin_ButtonB     = 4;
const int Pin_ButtonX     = 3;
const int Pin_ButtonY     = 2;
const int Pin_ButtonLB    = 6;
const int Pin_ButtonRB    = 7;
const int Pin_ButtonBACK  = 8;
const int Pin_ButtonSTART = 9;

const int Pin_DpadUP      = 10;
const int Pin_DpadDOWN    = 11;
const int Pin_DpadLEFT    = 12;
const int Pin_DpadRIGHT   = 13;

// Trigger Pins

const int Pin_TriggerL    = A4;
const int Pin_TriggerR    = A5;

void setup() {
	// Set buttons as inputs, using internal pull-up resistors

  if (UseTriggerButtons == true) {
    pinMode(Pin_TriggerL, INPUT_PULLUP);
    pinMode(Pin_TriggerR, INPUT_PULLUP);
  }
  // If using potentiometers for the triggers, set range
  else {
    XInput.setTriggerRange(0, ADC_Max);
  }

	pinMode(Pin_ButtonA, INPUT_PULLUP);
	pinMode(Pin_ButtonB, INPUT_PULLUP);
	pinMode(Pin_ButtonX, INPUT_PULLUP);
	pinMode(Pin_ButtonY, INPUT_PULLUP);

  pinMode(Pin_ButtonLB, INPUT_PULLUP);
  pinMode(Pin_ButtonRB, INPUT_PULLUP);

  pinMode(Pin_ButtonBACK, INPUT_PULLUP);
  pinMode(Pin_ButtonSTART, INPUT_PULLUP);
 

	pinMode(Pin_ButtonL3, INPUT_PULLUP);
	pinMode(Pin_ButtonR3, INPUT_PULLUP);
  
  pinMode(Pin_DpadUP, INPUT_PULLUP);
  pinMode(Pin_DpadDOWN, INPUT_PULLUP);
  pinMode(Pin_DpadLEFT, INPUT_PULLUP);
  pinMode(Pin_DpadRIGHT, INPUT_PULLUP);

	XInput.setJoystickRange(0, ADC_Max);  // Set joystick range to the ADC
	XInput.setAutoSend(false);  // Wait for all controls before sending

	XInput.begin();
}

void loop() {
	// Read pin values and store in variables
	// (Note the "!" to invert the state, because LOW = pressed)
	boolean buttonA = !digitalRead(Pin_ButtonA);
	boolean buttonB = !digitalRead(Pin_ButtonB);
	boolean buttonX = !digitalRead(Pin_ButtonX);
	boolean buttonY = !digitalRead(Pin_ButtonY);

  boolean buttonLB = !digitalRead(Pin_ButtonLB);
  boolean buttonRB = !digitalRead(Pin_ButtonRB);
  
  boolean buttonBack  = !digitalRead(Pin_ButtonBack);
  boolean buttonStart = !digitalRead(Pin_ButtonStart);

	boolean buttonL3 = !digitalRead(Pin_ButtonL3);
	boolean buttonR3 = !digitalRead(Pin_ButtonR3);

  boolean dpadUp    = !digitalRead(Pin_DpadUP);
  boolean dpadDown  = !digitalRead(Pin_DpadDOWN);
  boolean dpadLeft  = !digitalRead(Pin_DpadLEFT);
  boolean dpadRight = !digitalRead(Pin_DpadRIGHT);


	// Set XInput buttons
	XInput.setButton(BUTTON_A, buttonA);
	XInput.setButton(BUTTON_B, buttonB);
	XInput.setButton(BUTTON_X, buttonX);
	XInput.setButton(BUTTON_Y, buttonY);

  XInput.setButton(BUTTON_LB, buttonLB);
  XInput.setButton(BUTTON_RB, buttonRB);

  XInput.setButton(BUTTON_BACK, buttonBack);
  XInput.setButton(BUTTON_START, buttonStart);

	XInput.setButton(BUTTON_L3, buttonL3);
	XInput.setButton(BUTTON_R3, buttonR3);

  // Set Dpad Values

  XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);

  // Set Trigger values

  if (UseTriggerButtons == true) {
    // Read trigger buttons
    boolean triggerLeft  = !digitalRead(Pin_TriggerL);
    boolean triggerRight = !digitalRead(Pin_TriggerR);

    // Set the triggers as if they were buttons
    XInput.setButton(TRIGGER_LEFT, triggerLeft);
    XInput.setButton(TRIGGER_RIGHT, triggerRight);
  }
  else {
    // Read trigger potentiometer values
    int triggerLeft  = analogRead(Pin_TriggerL);
    int triggerRight = analogRead(Pin_TriggerR);

    // Set the trigger values as analog
    XInput.setTrigger(TRIGGER_LEFT, triggerLeft);
    XInput.setTrigger(TRIGGER_RIGHT, triggerRight);
  }

	// Set left joystick
	if (UseLeftJoystick == true) {
		int leftJoyX = analogRead(Pin_LeftJoyX);
		int leftJoyY = analogRead(Pin_LeftJoyY);

		// White lie here... most generic joysticks are typically
		// inverted by default. If the "Invert" variable is false
		// then we need to do this transformation.
		if (InvertLeftYAxis == false) {
			leftJoyY = ADC_Max - leftJoyY;
		}
    if (InvertLeftXAxis == true) {
      leftJoyX = ADC_Max - leftJoyX;
    }

		XInput.setJoystick(JOY_LEFT, leftJoyX, leftJoyY);
	}

	// Set right joystick
	if (UseRightJoystick == true) {
		int rightJoyX = analogRead(Pin_RightJoyX);
		int rightJoyY = analogRead(Pin_RightJoyY);

		if (InvertRightYAxis == false) {
			rightJoyY = ADC_Max - rightJoyY;
		}

		XInput.setJoystick(JOY_RIGHT, rightJoyX, rightJoyY);
	}

	// Send control data to the computer
	XInput.send();
}
