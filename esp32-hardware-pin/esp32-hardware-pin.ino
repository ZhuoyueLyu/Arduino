#include <HardwareSerial.h>
char mystr[10] = "Hello"; //String data

HardwareSerial mySerial(1);


void setup() {
  // Begin the Serial at 9600 Baud
  mySerial.begin(115200, SERIAL_8N1, 33, 2); // RX, TX
}

void loop() {
  mySerial.write(mystr,10); //Write the serial data
  delay(1000);
}