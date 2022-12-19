char mystr[5] = "300"; //String data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}

void loop() {
  Serial.write(mystr,5); //Write the serial data
  // digitalWrite(4, HIGH);
  delay(1000);
  // digitalWrite(4, LOW);
  delay(1000);
}