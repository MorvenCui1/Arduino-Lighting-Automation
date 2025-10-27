int lightInput; // photoresistor input
bool buttonInput; // push button input
int movingArray[5] = {0, 0, 0, 0, 0}; // array for storing photoresistor inputs
int average; // average recent photoresistor inputs
double output; // output for PWM
bool lightState = false; // state of light in surrounding environment

// upper and lower boundaries for detecting amount of light in surrounding area, can be modified depending on the surrounding area
int upperBoundary = 200;
int lowerBoundary = 100;


void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT); // photoresistor input
  pinMode(2, INPUT); // button input
  pinMode(6, OUTPUT); // red LED
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // take inputs from circuit
  buttonInput = digitalRead(2);
  lightInput = analogRead(A0);

  // move array values down by one spot and change first to new input value
  for (int i = 4; i > 0; i--) {
    movingArray[i] = movingArray[i - 1];
  }
  movingArray[0] = lightInput;

  // calculate average of array
  for (int i = 0; i < 5; i++) {
    average = movingArray[i];
  }
  average = average/5;

  // check for red LED to be on completely, off completely, or to calculate output lighting
  if (average <= lowerBoundary) {
    analogWrite(6, 255);
    lightState = true;
  }
  else if (average >= upperBoundary) {
    analogWrite(6, 0);
    lightState = false;
  }
  else {
    output = 255 - 255*(average - lowerBoundary)/(upperBoundary - lowerBoundary);
    analogWrite(6, output);
    lightState = true;
  }

  // check if button has been pushed
  if (buttonInput == LOW) {
    // check state of light in surroudings
    if (lightState == true) {
      digitalWrite(6, LOW);
    }
    else{
      digitalWrite(6, HIGH);
    }
  }

  // output inputs from button and light detection to serial monitor
  Serial.println(buttonInput);
  Serial.println(average);
}
