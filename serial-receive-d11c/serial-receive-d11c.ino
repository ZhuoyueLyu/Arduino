char mystr[10]; //Initialized variable to store recieved data

#define A        8                     // the pin connected to the wire A of the coil A (or to the H-bridge pin controlling the same wire) 
#define A_bar    14                     // the pin connected to the wire A- of the coil A (or to the H-bridge pin controlling the same wire)
#define B        9                     // the pin connected to the wire B of the coil A (or to the H-bridge pin controlling the same wire)
#define B_bar    15                     // the pin connected to the wire B- of the coil A (or to the H-bridge pin controlling the same wire)
          
#define stepsPerRevolution 200         // you can the number of steps required to make a complete revolution in the data sheet of your motor

// smaller values may make the motor produce more speed and less torque
int x  =   2065; // the smaller the number, the faster
// int currentSpeed = 2065;

void setup() {
  pinMode(A, OUTPUT);
  pinMode(A_bar, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(B_bar, OUTPUT);
  Serial1.begin(9600); // this is from the sender
  Serial.begin(9600); // this is the computer
}


void loop() {  


  if (Serial1.available()) {
    int speed = Serial1.parseInt();
    if (speed) {// incase we got empty string/int
    Serial.println(speed); 
    if (speed != 0) {
      x = speed;
    }
    }

  }
  //   if (Serial.available()) {
  //   int speed = Serial.parseInt();
  //   if (speed != 0) {
  //     x = speed;
  //   }
  // }

  for (int i = 0; i < (stepsPerRevolution/4) ; i++) {
    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, LOW);
    delayMicroseconds (x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    delayMicroseconds (x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, LOW);
    delayMicroseconds (x);

    digitalWrite(A, LOW);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, HIGH);
    delayMicroseconds (x);
  }
  // delay(1000);  // the motor will complete a full revolution then waits for a second
}




