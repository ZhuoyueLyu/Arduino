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

//////////////////////////////////////////////////////////////////
/// Use these  if you want to move a specific number of steps
//  This example moves a full rotation clockwise and then a full rotation counter-clockwise. Repeats.

int position = 2048; // this is the number of steps of a full rotation

void setup()
{
  //  stepper1.setMaxSpeed(600); // Sets the maximum permitted speed.  If your motors starts behaving erratically, lower this number. 600 seemed to be the limit for me.
  //  stepper1.setSpeed(400);    // Sets the speed. Positive numbers rotate clockwise. Negative numbers rotate counter-clockwise.
   Serial.begin(9600);
}
void loop()
{
   if (Serial.available() > 0)
   {
      int x_mid, y_mid;
      if (Serial.read() == 'X')
      {
         x_mid = Serial.parseInt(); // read center x-coordinate
         if (Serial.read() == 'Y')
            y_mid = Serial.parseInt(); // read center y-coordinate
      }
      Serial.print("\t");
      Serial.print(x_mid);
      Serial.print("\t");
      Serial.println(y_mid);
   }
   // stepper1.runSpeed();
}

// void loop() {

//   buttonState = digitalRead(buttonPin2);

//   // get the sensor value
//   // int val = analogRead(0);
//   if (buttonState == HIGH) {
//     // turn LED on:
//     // digitalWrite(ledPin, HIGH);
//     Serial.println("HH");
//     if (preState != buttonState) {
//       Serial.println("Faster");
//       // stepper.setSpeed(200);
//         // set the motor speed:
//       stepper1.setSpeed(100);
//       // step 1/100 of a revolution:
//       // myStepper.step(stepsPerRevolution / 100);
//     }

//   } else {
//     // turn LED off:
//     // digitalWrite(ledPin, LOW);
//     Serial.println("LL");
//     if (preState != buttonState) {
//       Serial.println("Slower");
//       // stepper.setSpeed(100);
//       stepper1.setSpeed(10);
//       // step 1/100 of a revolution:
//       // myStepper.step(stepsPerRevolution / 100);
//     }
//   }
//   stepper1.runSpeed();
// }