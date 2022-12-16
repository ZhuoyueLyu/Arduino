#include <AccelStepper.h>
#define STEP 4  // 4 for full step, 8 for half step, explanation here: https://www.motioncontrolonline.org/content-detail.cfm/Motion-Control-Application-Case-Studies/
#define motorPin1  12     // IN1 on the ULN2003 driver 1
#define motorPin2  13     // IN2 on the ULN2003 driver 1
#define motorPin3  15     // IN3 on the ULN2003 driver 1
#define motorPin4  16     // IN4 on the ULN2003 driver 1

AccelStepper stepper1(STEP, motorPin1, motorPin2, motorPin3, motorPin4);

void setup()
{  
   stepper1.setMaxSpeed(400);       // Sets the maximum permitted speed.  If your motors starts behaving erratically, lower this number. 600 seemed to be the limit for me.
   stepper1.setSpeed(100);          // Sets the speed. Positive numbers rotate clockwise. Negative numbers rotate counter-clockwise.
}
void loop()
{  
   stepper1.runSpeed();
}