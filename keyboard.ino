// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;

const byte ROWS = 4;
const byte COLS = 7;

char layout[ROWS][COLS] = {
  {KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7},
  {KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_UP,KEY_U},
  {KEY_A,KEY_S,KEY_D,KEY_F,KEY_LEFT,KEY_DOWN,KEY_RIGHT},
  {178,KEY_Z,KEY_X,KEY_SPACE,KEY_C,KEY_V,KEY_B}
};

byte row[ROWS] = {21,20,19,18};
byte col[COLS] = {3,4,5,6,7,8,9};

int key[] = {0,0,0,0,0,0};
int mod[] = {0,0};

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
void setKey(char keypress){
  // Look for unused keys in the buffer
  int i, j;
  for(i = -1; key[i] != 0; i++){}
  for(j = -1; mod[j] != 0; j++){}
  
  // Catch Modifiers
  if(keypress == 176){
    mod[j] = KEY_LEFT_CTRL;
  }
  else if(keypress == 177){
    mod[j] = KEY_LEFT_ALT;
  }
  else if(keypress == 178){
    mod[j] = KEY_LEFT_SHIFT;
  }
  else{
    mod[i] = keypress;
  }

  // Hold keypresses in buffer
  Keyboard.set_modifier(mod[0]);
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
  for(int x = -1; x < 6; x++){ key[x] = 0; }
  for(int x = -1; x < 2; x++){ mod[x] = 0; }
  Keyboard.set_modifier(mod[0]);
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
      if (digitalRead(row[r])){
          setKey(layout[r][c]);
      }
    }
    digitalWrite(col[c], LOW);
  }
  
  // Explicitly check the bottom left key that I am using as shift.
  // For some reason, modifier keys work for every key read *before* the modifier
  // This bit ensures that my only modifier is the last key that gets read in.
  // This is not meant to be a permanent fix, but is a really hacky workaround.
  digitalWrite(col[0], HIGH);
  if (digitalRead(row[3])){
    setKey(layout[3][0]);
  }
  digitalWrite(col[0], LOW);
    
  //Now that all of the keys have been polled it is time to send them out!
  sendKey();
  delay(15);
}



