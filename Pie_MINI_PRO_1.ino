const int red_led = 11;
const int yellow_led = 13;
const int green_led = 12;
const int button = 10;

int potPin = A0; // Potentiometer output connected to analog pin 3


// Things to debounce button
bool lastButtonReading; // HIGH = released, LOW = pressed
unsigned long lastButtonChange = 0;
const int buttonDebounce = 50;
bool buttonState = HIGH;

int count = 0;
int num = 0;
uint32_t blink_time;

//const int interval = 500;

int lights[3] = {red_led, yellow_led, green_led};
int lightnum = 0;

void setup() {
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  blink_time = millis();
  count = 0;

  lastButtonReading = digitalRead(button);
  Serial.print("Initial reading: ");
  Serial.println(lastButtonReading);
}


void loop() {
  unsigned long now = millis();
  int interval = analogRead(potPin); // 0-1024
  // Button debounce 
  bool buttonReading = digitalRead(button);
  if (buttonReading != lastButtonReading) {
    lastButtonChange = now;              // reset debounce timer
    lastButtonReading = buttonReading;   // record last reading
  }

  // Check if button reading has been stable for long enough
  if (now - lastButtonChange >= buttonDebounce) {
    if (buttonState != buttonReading) {
      buttonState = buttonReading; // accept new button state
      if (buttonState == LOW) {
        count++;
        Serial.println("Button pressed");
        Serial.print("Current mode: ");
        Serial.println(count);
      }
      else {
        //Serial.println("Button released");
      }
    }
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
    if (now >= blink_time + interval){
      digitalWrite(yellow_led, !digitalRead(yellow_led));
      digitalWrite(green_led, !digitalRead(green_led));
      digitalWrite(red_led, !digitalRead(red_led));
      blink_time = now;
     }

    }
  else if (count == 2) {
    digitalWrite(green_led, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level

    digitalWrite(red_led, HIGH);   // change state of the LED by setting the pin to the LOW voltage level

    digitalWrite(yellow_led, HIGH);
  }
  else if (count == 3){
    /*digitalWrite(green_led, HIGH);  
    delay(500);                      
    digitalWrite(green_led, LOW);   
    delay(500);                      
    digitalWrite(yellow_led, HIGH);
    delay(500);
    digitalWrite(yellow_led, LOW);
    delay(500);
    digitalWrite(red_led, HIGH);
    delay(500);
    digitalWrite(red_led, LOW);
    delay(500);
    */

    
    if ( now >= blink_time + interval ){
      digitalWrite(green_led, LOW);
      digitalWrite(yellow_led, LOW);
      digitalWrite(red_led, LOW);
      digitalWrite(lights[lightnum], HIGH);
      lightnum = lightnum+1;
      if (lightnum >= 3){
        lightnum = 0;
      
      }

      blink_time = now;
      //Serial.println(lights[lightnum]);
    }
  }
  else if (count == 4){
    /*digitalWrite(green_led, HIGH);   
    delay(500);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, LOW);   
    delay(500);
    digitalWrite(green_led, HIGH);   
    digitalWrite(yellow_led, LOW);   
    delay(500);
    digitalWrite(red_led, LOW);   
    delay(500);
    digitalWrite(green_led, LOW);   
    delay(500);   
    */

      if (now >= blink_time + interval){
        //digitalWrite(lights[lightnum], !lights[lightnum]);
        /*if (num >= 4){
            digitalWrite(red_led, HIGH);
          }
          else {
            digitalWrite(red_led, LOW);
          }
        */
        if (num == 0){
          for (int led : lights){
            digitalWrite(led, LOW);
          }
          num=num+1;
        }
        else if (num == 7){
          digitalWrite(green_led, HIGH);
          num = 0;
        }
        else if (num == 6){
          digitalWrite(green_led, LOW);
          digitalWrite(yellow_led, HIGH);
          num = num+1;
        }
        else if (num == 5){
          digitalWrite(green_led, HIGH);
          num = num+1;
        }        
        else if (num == 4){
          for (int led : lights){
            digitalWrite(led, LOW);
          }
          digitalWrite(red_led, HIGH);
          num = num+1;
        }
        else if (num == 3){
          digitalWrite(green_led, HIGH);
          num = num+1;
        }
        else if (num == 2){
          digitalWrite(green_led, LOW);
          digitalWrite(yellow_led, HIGH);
          num = num+1;
        }
        else if (num == 1){
          digitalWrite(green_led, HIGH);
          num = num+1;
        }
        
        blink_time = now;
        Serial.println(num);
    }                       
  }
}
