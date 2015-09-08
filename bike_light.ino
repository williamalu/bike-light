// set pins for button, LEDs, and pot
const int buttonPin = 2;
const int greenPin = 9;
const int yellowPin = 10;
const int redPin = 11;
const int potPin = 0;

int lightState = 0; // set initial light state to off
int buttonTime = 0; // initialize most recent time button was pressed
int lastButtonTime = 0; // initialize last time button was pressed
int potVal = 500; // initialize potentiometer value

void setup() {
  // if button is pressed, interrupt loop and run increment function
  attachInterrupt(0, increment, RISING);

  // set LEDs to output
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  // set button to input
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600); 
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
    allOff();
    delay(500);
    allOn();
    delay(500);
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
    Serial.println("reset lightState");
    lightState = 0;
  }

  Serial.println(lightState);
}

void increment() {
  // when button is pressed, record time button was pressed
  buttonTime = millis();

  // if button has not been pressed within the last 250ms, 
  // increment lightState
  if (millis() - lastButtonTime > 250) {
    Serial.println("increment lightState");
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
  allOff();
  digitalWrite(greenPin, HIGH);
  delay(500);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  delay(500);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  delay(500);
  return;
}

void turnSignal() {
  potVal = analogRead(potPin); // read the potentiometer

  if (potVal > 1000) {
    // if potentiometer is turned to the right, flash light on the right
    allOff();
    delay(250);
    digitalWrite(greenPin, HIGH);
    delay(250);
  }
  else if (potVal < 23) {
    // if potentiometer is turned to the left, flash light on the left
    allOff();
    delay(250);
    digitalWrite(redPin, HIGH);
    delay(250);
  }
  else {
    // in all other cases, just flash the middle light
    allOff();
    delay(250);
    digitalWrite(yellowPin, HIGH);
    delay(250);
  }
}