//E-innovators
 //stepper motor speed control using arduino nano
 //digital pin 8,9,10,11

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 32

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 9, 10, 11, 12);
// Stepper stepper(STEPS, 12, 11, 10, 9);
const int buttonPin1 = 2;  
const int buttonPin2 = 4;  
int buttonState = 0;  // variable for reading the pushbutton status
int preState = 0;

// the previous reading from the analog input
int previous = 0;

void setup() {
  // set the speed of the motor to 100 RPMs
  stepper.setSpeed(600);
  // Serial.begin(9600);
  digitalWrite(buttonPin1, HIGH);
}

void loop() {

  buttonState = digitalRead(buttonPin2);

  // get the sensor value
  // int val = analogRead(0);
  if (buttonState == HIGH) {
    // turn LED on:
    // digitalWrite(ledPin, HIGH);
    // Serial.println("HH");
    if (preState != buttonState) {
      // Serial.println("Faster");
      // stepper.setSpeed(200);
        // set the motor speed:
      stepper.setSpeed(1000);
      // step 1/100 of a revolution:
      // myStepper.step(stepsPerRevolution / 100);
    }
    
  } else {
    // turn LED off:
    // digitalWrite(ledPin, LOW);
    // Serial.println("LL");
    if (preState != buttonState) {
      // Serial.println("Slower");
      // stepper.setSpeed(100);
      stepper.setSpeed(300);
      // step 1/100 of a revolution:
      // myStepper.step(stepsPerRevolution / 100);
    }
  }

  // move a number of steps equal to the change in the
  // sensor reading
  stepper.step(1);

  // // remember the previous value of the sensor
  // previous = val;

  preState = buttonState;
}