

// Assign each led a pin on the ardunio 
const int red_led = 11;
const int yellow_led = 13;
const int green_led = 12;
// Assign the button a pin on the ardunio
const int button = 10;

int potPin = A0; // Potentiometer output connected to analog pin 3


// Tools we used to debounce button
bool lastButtonReading; // HIGH = released, LOW = pressed
unsigned long lastButtonChange = 0; 
const int buttonDebounce = 50; // 
bool buttonState = HIGH; // Set the button to high just in case

int count = 0; // Creation of varible used for keeping count of the current mode of the button
int num = 0; // Used for counting in binary to keep track of what step on
uint32_t blink_time; // Sets a 32 bit lim for the blink time

//const int interval = 500;

int lights[3] = {red_led, yellow_led, green_led}; // A list containg the leds
int lightnum = 0; // Used for looping through lights

void setup() {
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(button, INPUT_PULLUP); // Intialz digital buttin pin
  blink_time = millis(); // intilize time
  count = 0; // just incase count did a silly happended at one point somehow

  lastButtonReading = digitalRead(button); // sets up a fucntion
  Serial.print("Initial reading: "); // Used for testing to make sure button was being pressed
  Serial.println(lastButtonReading); 
}

// intilizes loop
void loop() {
  unsigned long now = millis(); // intilizes another time from when we merged code
  int interval = analogRead(potPin); // 0-1024 Reads the potionameter and sets the time interval based off it
  // Button debounce 
  bool buttonReading = digitalRead(button); // Checks button postion 
  if (buttonReading != lastButtonReading) { // Checks if the button is infact in a diffrent then last time
    lastButtonChange = now;              // reset debounce timer
    lastButtonReading = buttonReading;   // record last reading
  }

  // Check if button reading has been stable for long enough
  if (now - lastButtonChange >= buttonDebounce) {
    if (buttonState != buttonReading) {
      buttonState = buttonReading; // accept new button state
      if (buttonState == LOW) {
        count++;
        Serial.println("Button pressed"); // Prints that we infact did press the button
        Serial.print("Current mode: ");
        Serial.println(count);
      }
      //else {
        //Serial.println("Button released"); // old
      //}
    }
  }

  //Makes sure that count doesnt escape and resets it if gets to our past our final mode

  if (count >= 5) {
      count = 0; 
  }

  else if (count == 0) { // Checks if in mode one
    digitalWrite(red_led, LOW); // turns everyone off
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
  }
  else if (count == 1) { // Checks if in mode two
    if (now >= blink_time + interval){ // Takes the previus tiem it blinked and adds it to the interval to make sure the the apporet time had passed
      digitalWrite(yellow_led, !digitalRead(yellow_led)); //Flips the led to what ever it was in the oppsite mode
      digitalWrite(green_led, !digitalRead(green_led));
      digitalWrite(red_led, !digitalRead(red_led));
      blink_time = now; // sets blink time to current now time 
     }


    }
  else if (count == 2) { // checks if in mode three
    digitalWrite(green_led, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level

    digitalWrite(red_led, HIGH);

    digitalWrite(yellow_led, HIGH);
  }
  else if (count == 3){ // checks if in mode four

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

    
    if ( now >= blink_time + interval ){// Takes the previus tiem it blinked and adds it to the interval to make sure the the apporet time had passed
      digitalWrite(green_led, LOW);
      digitalWrite(yellow_led, LOW);
      digitalWrite(red_led, LOW); // Turns everyone off 
      digitalWrite(lights[lightnum], HIGH); //turns the led in the blink cylce on
      lightnum = lightnum+1; // Primes the next led to turn on
      if (lightnum >= 3){ // Makes sure that we dont leave the list boundry
        lightnum = 0;
      
      }

      blink_time = now; // remebers the last blink time
      //Serial.println(lights[lightnum]);
    }
  }
  else if (count == 4){ // checks if in mode five
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

      if (now >= blink_time + interval){// Takes the previus tiem it blinked and adds it to the interval to make sure the the apporet time had passed
        //digitalWrite(lights[lightnum], !lights[lightnum]);
        /*if (num >= 4){
            digitalWrite(red_led, HIGH);
          }
          else {
            digitalWrite(red_led, LOW);
          }
        */
        if (num == 0){ // if num is zero turn off all the leds
          for (int led : lights){
            digitalWrite(led, LOW);
          }
          num=num+1;
        }
        else if (num == 7){ // if num is 7 turn on green
          digitalWrite(green_led, HIGH);
          num = 0; // reset num
        }
        else if (num == 6){ // if num is 6 turn on yellow turn off green
          digitalWrite(green_led, LOW);
          digitalWrite(yellow_led, HIGH);
          num = num+1; // advance num
        }
        else if (num == 5){ // if num is 5 turn on green
          digitalWrite(green_led, HIGH);
          num = num+1; // advance num
        }        
        else if (num == 4){ // if num is four turn of leds and turn on red
          for (int led : lights){
            digitalWrite(led, LOW);
          }
          digitalWrite(red_led, HIGH);
          num = num+1; // advance num
        }
        else if (num == 3){ // if num is 3 turn on green
          digitalWrite(green_led, HIGH);
          num = num+1; // advance num
        }
        else if (num == 2){ // if num is two turn on yellow turn off green
          digitalWrite(green_led, LOW);
          digitalWrite(yellow_led, HIGH);
          num = num+1; // advance num
        }
        else if (num == 1){ // if num is 1 turn on green
          digitalWrite(green_led, HIGH);
          num = num+1; // advance num
        }
        
        blink_time = now; // blink time equals new current time
        Serial.println(num);// print current step in num
    }                       
  }
}
