// ********************************************************************
//
// Don't forget to install the AccelStepper library for this example to work
// Library documentation here: https://www.airspayce.com/mikem/arduino/AccelStepper/
// Function reference here: https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#adfb19e3cd2a028a1fe78131787604fd1
// Video that explains how the stepper works: https://www.youtube.com/watch?v=avrdDZD7qEQ&ab_channel=NikodemBartnik
//
// ********************************************************************

#include <AccelStepper.h>
#define STEP 4 // 4 for full step, 8 for half step, explanation here: https://www.motioncontrolonline.org/content-detail.cfm/Motion-Control-Application-Case-Studies/What-is-the-difference-between-full-stepping-the-half-stepping-and-the-micro-drive/content_id/3192

// Motor pin definitions
#define motorPin1 9  // IN1 on the ULN2003 driver 1
#define motorPin2 10 // IN2 on the ULN2003 driver 1
#define motorPin3 11 // IN3 on the ULN2003 driver 1
#define motorPin4 12 // IN4 on the ULN2003 driver 1

AccelStepper stepper1(STEP, motorPin1, motorPin3, motorPin2, motorPin4);

const int buttonPin1 = 2;
const int buttonPin2 = 4;
int buttonState = 0; // variable for reading the pushbutton status
int preState = 0;
int speed_1 = 200;
int speed_2 = 400;
int speed_3 = 600;
int curr_speed = 600;

void setup()
{
   stepper1.setMaxSpeed(600);  
   stepper1.setSpeed(600); 
   Serial.begin(9600);
}



void loop() {
  buttonState = digitalRead(buttonPin2);
  if (buttonState == HIGH) {
    if (preState != buttonState) {
      Serial.println("F");
      stepper1.setSpeed(600);
    }
    
  } else {
    if (preState != buttonState) {
      Serial.println("S");
      stepper1.setSpeed(50);
    }
  }

  stepper1.runSpeed();
  preState = buttonState;
}
