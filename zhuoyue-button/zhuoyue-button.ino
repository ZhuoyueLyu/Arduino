// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 2;  
const int buttonPin2 = 4;    

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  // // initialize the LED pin as an output:
  // pinMode(buttonPin2, OUTPUT);
  // // initialize the pushbutton pin as an input:
  // pinMode(buttonPin1, INPUT);
  digitalWrite(buttonPin1, HIGH);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin2);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    // digitalWrite(ledPin, HIGH);
    Serial.println("HH");
  } else {
    // turn LED off:
    // digitalWrite(ledPin, LOW);
    Serial.println("LL");
  }
}