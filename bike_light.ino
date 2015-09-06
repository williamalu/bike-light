// set pins for button and LEDs
const int buttonPin = 2;
const int greenPin = 9;
const int yellowPin = 10;
const int redPin = 11;

int lightState = 0; // set initial light state to off
int buttonTime = 0; // initialize most recent time button was pressed
int lastButtonTime = 0; // initialize last time button was pressed

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
  }

  // if lightState is greater than 3, reset lightState to off
  if (lightState > 3) {
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