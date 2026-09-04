const int red_led = 11;
const int yellow_led = 12;
const int green_led = 13;
const int button = 10;
bool button_down;
int count = 0;

uint32_t blink_time;

const int interval = 500;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(button, INPUT);
  blink_time = millis();
  count = 0;
  Serial.begin(9600);
}



void loop() {
  uint32_t t;
  t = millis();
  //Serial.println(t);
  if (digitalRead(button) == HIGH && button_down == false){
    button_down = true;
    count = count +1;
    Serial.println(count);
  }
  else if (digitalRead(button) == LOW){
    button_down = false;
  }
  // put your main code here, to run repeatedly:
  if (count >= 5) {
      count = 0;
  }
  else if (count == 0) {
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
  }
  else if (count == 1) {
    /*
    digitalWrite(green_led, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
    digitalWrite(red_led, HIGH);   // change state of the LED by setting the pin to the LOW voltage level
    digitalWrite(yellow_led, HIGH);
    delay(1000);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, LOW);
    delay(1000);
    */
      if (t >= blink_time + interval){
        digitalWrite(yellow_led, !digitalRead(yellow_led));
        digitalWrite(green_led, !digitalRead(green_led));
        digitalWrite(red_led, !digitalRead(red_led));
        blink_time = t;
      }

    }
  else if (count == 2) {
    digitalWrite(green_led, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level

    digitalWrite(red_led, HIGH);   // change state of the LED by setting the pin to the LOW voltage level

    digitalWrite(yellow_led, HIGH);
  }
  else if (count == 3){
    digitalWrite(green_led, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
    delay(500);                      // wait for a second
    digitalWrite(green_led, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);                      // wait for a second
    digitalWrite(yellow_led, HIGH);
    delay(500);
    digitalWrite(yellow_led, LOW);
    delay(500);
    digitalWrite(red_led, HIGH);
    delay(500);
    digitalWrite(red_led, LOW);
    delay(500);
  }
  else if (count == 4){
    digitalWrite(green_led, HIGH);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);
    digitalWrite(green_led, HIGH);   // change state of the LED by setting the pin to the LOW voltage level
    digitalWrite(yellow_led, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);
    digitalWrite(red_led, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);
    digitalWrite(green_led, LOW);   // change state of the LED by setting the pin to the LOW voltage level
    delay(500);                            
  }

}
