// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;

const byte ROWS = 4;
const byte COLS = 7;

char layout[ROWS][COLS] = {
  {KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_Y,KEY_U},
  {KEY_I,KEY_O,KEY_P,KEY_K,KEY_L,KEY_Z,KEY_M},
  {KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,KEY_H,KEY_J},
  {KEY_CAPS_LOCK,KEY_X,KEY_C,KEY_V,KEY_B,KEY_N,KEY_SPACE}
};

byte row[ROWS] = {21,20,19,18};
byte col[COLS] = {3,4,5,6,7,8,9};

int key[] = {0,0,0,0,0,0};

// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
  for (int c = 0; c < COLS; c++){
    pinMode(col[c], OUTPUT);
  }
  for (int r = 0; r < ROWS; r++){
    pinMode(row[r], INPUT);
  } 
}

// This function will take keypresses passed to it (in the form of a char, for no particular reason)
// and add them to set of six keys that will be passed to the computer when Keyboard.send_now() is called.

// Basically, this collects the currently pressed keys and stores them until they cand be passed to the computer.
void setKey(int keynum, char keypress){
  key[keynum] = keypress;

  // Hold keypresses in buffer
  Keyboard.set_key1(key[0]);
  Keyboard.set_key2(key[1]);
  Keyboard.set_key3(key[2]);
  Keyboard.set_key4(key[3]);
  Keyboard.set_key5(key[4]);
  Keyboard.set_key6(key[5]);
}

// This method sends the depressed keys and clears the buffer.
void sendKey(){
  Keyboard.send_now();
  for(int x = 0; x < 8; x++){ key[x] = 0; }
  Keyboard.set_key1(key[0]);
  Keyboard.set_key2(key[1]);
  Keyboard.set_key3(key[2]);
  Keyboard.set_key4(key[3]);
  Keyboard.set_key5(key[4]);
  Keyboard.set_key6(key[5]);
}

void loop() {
  int keycount = 0;
  for (int c = 0; c < COLS; c++) {
    digitalWrite(col[c], HIGH);
    for (int r = 0; r < ROWS; r++) {
      if (digitalRead(row[r]) && keycount < 8){
        setKey(keycount, layout[r][c]);
        keycount ++;
      }
    }
    digitalWrite(col[c], LOW);
  }
  //Now that all of the keys have been polled it is time to send them out!
  sendKey();
  delay(15);
}



