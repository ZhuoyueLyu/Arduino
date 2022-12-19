char mystr[10]; //Initialized variable to store recieved data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // if (Serial.available() ) {

  // }
        
      // Serial1.readBytes(mystr,5); //
      // int speed = atoi(mystr);
      // // sscanf(mystr, "%d", &speed);
      // // int speed = mystr.parseInt()
      // int speedNew = speed + 200;
      // Serial.println(mystr);
      int speed = Serial1.parseInt();
      int speedNew = speed + 200;
      Serial.println(speedNew);
      delay(1000);

}