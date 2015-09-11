// set pins for button, LEDs, and pot
const int buttonPin = 2;
const int greenPin = 9;
const int yellowPin = 10;
const int redPin = 11;
const int pot1Pin = 0;
const int pot2Pin = 1;

int lightState = 0; // set initial light state to off
int buttonTime = 0; // initialize most recent time button was pressed
int lastButtonTime = 0; // initialize last time button was pressed
int pot1Val = 500; // initialize first potentiometer value
int pot2Val = 500; // initialize second potentiometer value

void setup() {
  // if button is pressed, interrupt loop and run increment function
  attachInterrupt(0, increment, RISING);

  // set LEDs to output
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  // set button to input
  pinMode(buttonPin, INPUT);
}

void loop() {
  // depending on the lightState, flash different light patterns
  switch (lightState) {
    case 0:
    // all LEDs off
    allOff();
    break;
    case 1:
    // all LEDs on
    allOn();
    break;
    case 2:
    // LEDs flash on and off
    pot2Val = analogRead(pot2Pin); // read the potentiometer
    allOff();
    delay(pot2Val);
    allOn();
    delay(pot2Val);
    break;
    case 3:
    // LEDs light up in sequence
    bouncing();
    break;
    case 4:
    // green or red LEDs light up depending on pot
    turnSignal();
    break;
  }

  // if lightState is greater than 3, reset lightState to off
  if (lightState > 4) {
    lightState = 0;
  }
}

void increment() {
  // when button is pressed, record time button was pressed
  buttonTime = millis();

  // if button has not been pressed within the last 250ms, 
  // increment lightState
  if (millis() - lastButtonTime > 250) {
    lightState++;
    lastButtonTime = buttonTime;
  }
}

void allOff() {
  // turn all LEDs off
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  return;
}

void allOn() {
  // turn all LEDs on
  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, HIGH);
  return;
}

void bouncing() {
  // flash each LED once
  pot2Val = analogRead(pot2Pin); // read the potentiometer
  allOff();
  digitalWrite(greenPin, HIGH);
  delay(pot2Val);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  delay(pot2Val);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  delay(pot2Val);
  return;
}

void turnSignal() {
  pot1Val = analogRead(pot1Pin); // read the potentiometer
  pot2Val = analogRead(pot2Pin); // read the potentiometer

  if (pot1Val > 1000) {
    // if potentiometer is turned to the right, flash light on the right
    allOff();
    delay(pot2Val);
    digitalWrite(greenPin, HIGH);
    delay(pot2Val);
  }
  else if (pot1Val < 23) {
    // if potentiometer is turned to the left, flash light on the left
    allOff();
    delay(pot2Val);
    digitalWrite(redPin, HIGH);
    delay(pot2Val);
  }
  else {
    // in all other cases, just flash the middle light
    allOff();
    delay(pot2Val);
    digitalWrite(yellowPin, HIGH);
    delay(pot2Val);
  }
}