int led = 13; // led that we will toggle
char inChar;  // character we will use for messages from the RPi

int button = 2;
int buttonState;

int potVal = 0; // potentiometer value
int newVal = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // read the character we recieve on the serial port from the RPi
  if(Serial.available()) {
    inChar = (char)Serial.read();
  }

  // if we get a 'H', turn the LED on, else turn it off
  if(inChar == 'H'){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }

  // Button event checker - if pressed, send message to RPi
  int newState = digitalRead(button);
  if (buttonState != newState) {
    buttonState = newState;
    if(buttonState == HIGH){
      Serial.println("light"); //note println put a /r/n at the end of a line
      delay(1000); //this button has been effecting the pot value
    }
    else{
      Serial.println("dark");
      delay(1000);
    }
  }

  // Transmit new pot value if it has changed
  newVal = analogRead(A1);
  if (potVal >= (newVal+10) || potVal <= (newVal-10)) {
    potVal = newVal;
    Serial.println("pot"+String(map(potVal,0,1023,0,300)));
    delay(1);
  }
}
