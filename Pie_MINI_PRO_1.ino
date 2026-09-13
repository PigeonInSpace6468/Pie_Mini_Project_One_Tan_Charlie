// Turn signals (LEDs)
const int red_led = 11;
const int yellow_led = 13;
const int green_led = 12;

// Turn signal modes (button)
const int button = 10;

// Turn signal flash speed (potentiometer)
int potentiometer = A0;


// Button debounce
bool lastButtonReading;          // HIGH = pressed, LOW = unpressed/released
uint32_t lastButtonChange = 0;   // The last time the button reading changed
const int buttonDebounce = 50;   // Button reading must remain stable for >= 50 ms
bool buttonState = LOW;          // Initial buttons state

int mode = 0;                   // Keeps track of the current turn signal mode
int binary_state = 0;            // Used for binary blinking mode; keeps track of binary state
uint32_t blink_time;             // Timer for LED blinking
uint32_t blink_interval = 0;     // Period between blinks - determines frequency

int lights[3] = {red_led, yellow_led, green_led}; // Used for sequential blinking mode
int light_num = 0; // Used for looping through lights


void setup() {
  Serial.begin(9600);
  
  // Initialize LEDs as outputs
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  // Initialize button as input
  pinMode(button, INPUT);
  blink_time = millis(); // Start blink timer
  lastButtonReading = digitalRead(button); // Record initial button reading

  Serial.print("Initial reading: "); // For testing: confirm button reading
  Serial.println(lastButtonReading); 
}


void loop() {
  unsigned long now = millis(); // Current program time
  blink_interval = analogRead(potentiometer); // Raw analog reading: 0-1024

  // Button debounce 
  bool buttonReading = digitalRead(button); // Records button reading 

  if (buttonReading != lastButtonReading) { // Checks if button reading is unstable (changing)
    lastButtonChange = now;                 // Reset debounce timer
    lastButtonReading = buttonReading;      // Update last button reading
  }

  // Check if button reading has been stable for long enough
  if (now - lastButtonChange >= buttonDebounce) {

    if (buttonState != buttonReading) {
      buttonState = buttonReading; // Accept stable button state
      
      if (buttonState == HIGH) {
        mode++; // Increment to new mode

        Serial.println("Button pressed"); // For testing: confirm button pressed
        Serial.print("Current mode: ");
        Serial.println(mode);
      }
    }
  }

  // Reset after final mode
  if (mode >= 5) {
    mode = 0; 
  }

  // Mode 0: All off
  else if (mode == 0) {
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
  }

  // Mode 1: All blinking
  else if (mode == 1) { 
    
    // Checks if enough time has passed before the last blink
    if (now >= blink_time + interval) { 
      digitalWrite(yellow_led, !digitalRead(yellow_led)); // Invert LED state
      digitalWrite(green_led, !digitalRead(green_led));
      digitalWrite(red_led, !digitalRead(red_led));

      blink_time = now; // Record the last blink time
    }
  }

  // Mode 2: All on
  else if (mode == 2) {
    digitalWrite(green_led, HIGH);
    digitalWrite(red_led, HIGH);
    digitalWrite(yellow_led, HIGH);
  }

  // Mode 3: Sequential blinking
  else if (mode == 3){

    // Checks if enough time has passed before the last blink
    if (now >= blink_time + interval) {
      digitalWrite(green_led, LOW);
      digitalWrite(yellow_led, LOW);
      digitalWrite(red_led, LOW);

      digitalWrite(lights[light_num], HIGH); // Set first LED in the blink cycle HIGH
      light_num = light_num + 1; // Increment to next LED
      
      // Reset LED counter
      if (light_num >= 3) { 
        light_num = 0;
      }

      blink_time = now; // Record the last blink time
    }
  }

  // Mode 4: Binary blinking
  else if (mode == 4){

      // Checks if enough time has passed before the last blink
      if (now >= blink_time + interval){

        // [R][G][B] = [0][0][0]
        if (binary_state == 0) { 
          for (int led : lights){
            digitalWrite(led, LOW);
          }
          binary_state = binary_state + 1;
        }

        // [R][G][B] = [1][1][1]
        else if (binary_state == 7) {
          digitalWrite(green_led, HIGH);
          binary_state = 0; // Return to first binary state
        }

        // [R][G][B] = [1][1][0]
        else if (binary_state == 6) {
          digitalWrite(green_led, LOW);
          digitalWrite(yellow_led, HIGH);
          binary_state = binary_state + 1;
        }

        // [R][G][B] = [1][0][1]
        else if (binary_state == 5) {
          digitalWrite(green_led, HIGH);
          binary_state = binary_state + 1;
        }

        // [R][G][B] = [1][0][0]
        else if (binary_state == 4) {
          for (int led : lights){
            digitalWrite(led, LOW);
          }
          digitalWrite(red_led, HIGH);
          binary_state = binary_state + 1;
        }

        // [R][G][B] = [0][1][1]
        else if (binary_state == 3) {
          digitalWrite(green_led, HIGH);
          binary_state = binary_state + 1;
        }

        // [R][G][B] = [0][1][0]
        else if (binary_state == 2) { 
          digitalWrite(green_led, LOW);
          digitalWrite(yellow_led, HIGH);
          binary_state = binary_state + 1;
        }

        // [R][G][B] = [0][0][1]
        else if (binary_state == 1) {
          digitalWrite(green_led, HIGH);
          binary_state = binary_state + 1;
        }
        
        blink_time = now; // Record the last blink time
        Serial.println(binary_state); // For testing: print current step in binary cycle
    }                       
  }

  // End of loop()
}