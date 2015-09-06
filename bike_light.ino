// set pins for button and LEDs
const int buttonPin = 8;
const int greenPin = 9;
const int yellowPin = 10;
const int redPin = 11;

int lightState = 0; // set initial light state to off
int buttonState; // initialize button state
int lastButtonState = 0; // set intial button state to off

int reading = 0; // initialize button reading as low
int prevReading = 0; // initialize previous button reading as low

void setup() {
  Serial.begin(9600); 
  
  // set LEDs to output
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  // set button to input
  pinMode(buttonPin, INPUT);
}

void loop() {

  reading = digitalRead(buttonPin); // read the state of the pushbutton value
  
  // if reading has changed from the previous reading, increment lightState by 1
  if (prevReading && !reading) {
    Serial.println("increment lightState");
    lightState++; 
  }
  
  switch (lightState) {
    case 0:
      Serial.println("case 0");
      allOff();
      break;
    case 1:
      Serial.println("case 1");
      allOn();
      break;
    case 2:
      Serial.println("case 2");
      allOn();
      delay(1000);
      allOff();
      delay(1000);
      break;
    case 3:
      Serial.println("case 3");
      bouncing();
      break;
  }

  // if lightState is greater than 3, reset lightState to off
  if (lightState > 3) {
    Serial.println("reset lightState");
    lightState = 0;
  }

  Serial.println("reset reading");
  
  prevReading = reading;
}

void allOff() {
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    return;
}

void allOn() {
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, HIGH);
    return;
}

void bouncing() {
   allOff();
   digitalWrite(greenPin, HIGH);
   delay(1000);
   digitalWrite(greenPin, LOW);
   digitalWrite(yellowPin, HIGH);
   delay(1000);
   digitalWrite(yellowPin, LOW);
   digitalWrite(redPin, HIGH);
   delay(1000);
   return;
}