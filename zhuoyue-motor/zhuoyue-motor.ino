// ********************************************************************
//
// Don't forget to install the AccelStepper library for this example to work
// Library documentation here: https://www.airspayce.com/mikem/arduino/AccelStepper/
// Function reference here: https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#adfb19e3cd2a028a1fe78131787604fd1
// Video that explains how the stepper works: https://www.youtube.com/watch?v=avrdDZD7qEQ&ab_channel=NikodemBartnik
//
// ********************************************************************

#include <AccelStepper.h>

// (Step, Pin1, Pin2, Pin3, Pin4 )
// 4 for full step, 8 for half step, explanation here: https://www.motioncontrolonline.org/content-detail.cfm/Motion-Control-Application-Case-Studies/What-is-the-difference-between-full-stepping-the-half-stepping-and-the-micro-drive/content_id/3192
AccelStepper stepper1(4, 9, 10, 11, 12);

int speed_1 = 10;
int speed_2 = 100;
int speed_3 = 400;
int curr_speed = 400;
int max_speed = 400;

void setup()
{
   stepper1.setMaxSpeed(max_speed);
   stepper1.setSpeed(curr_speed);
   Serial.begin(9600);
}

void loop()
{
   int num_faces = 0;
   // On the server side (python), we only send info
   // when there is changes. I tried to handle that on this side
   // but for some reason, whenever the board receive data
   // it stop spinning, so it makes the board very laggy
   if (Serial.available() > 0)
   {
      num_faces = Serial.parseInt();
      switch (num_faces)
      {
      case 0:
         update_motor_speed(speed_3);
         break;
      case 1:
         update_motor_speed(speed_2);
         break;
      }
   }
   // We can't use if/else to provide value because the frequency
   // of python sending value is probably smaller than the frequency of loop()
   // therefore, it may jump back and forth between two speeds
   stepper1.runSpeed();
}

void update_motor_speed(int new_speed)
{
   if (curr_speed != new_speed)
   {
      stepper1.setSpeed(new_speed);
      curr_speed = new_speed;
   }
}
