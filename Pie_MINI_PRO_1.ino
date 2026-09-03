void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  count = 0
}

void loop() {
  // put your main code here, to run repeatedly:
  if (count >= 5) {
      count = 0
  }
  else if (count == 0) {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else if (count == 1) {
    digitalWrite(13, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level

    digitalWrite(11, HIGH);   // change state of the LED by setting the pin to the LOW voltage level

    digitalWrite(12, HIGH);

    delay(1000);

    digitalWrite(12, LOW);

    digitalWrite(13, LOW);
    
    digitalWrite(11, LOW);
    
    }
  }
  else if (count == 2) {
    digitalWrite(13, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level

    digitalWrite(11, HIGH);   // change state of the LED by setting the pin to the LOW voltage level

    digitalWrite(12, HIGH);
  }
  else if (count == 3){
    digitalWrite(13, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
    delay(500);                      // wait for a second
    digitalWrite(13, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);                      // wait for a second
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12, LOW);
    delay(500);
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(11, LOW);
    delay(500);
  }
  else if (count == 4){
    digitalWrite(13, HIGH);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);
    digitalWrite(13, HIGH);   // change state of the LED by setting the pin to the LOW voltage level
    digitalWrite(12, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);
    digitalWrite(11, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);
    digitalWrite(13, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);                            
  }

}
