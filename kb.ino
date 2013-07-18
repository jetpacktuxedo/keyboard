#include <stdlib.h>

// Declare LED ports.
// On the Teensy 3.0 the board LED is port 13. This may not be true on other versions of the teensy. Check your documentation.
int led = 13;

// I used these ports because they were easilly accesable at the time. Ideally you should use ports that support PWM.
// In the case of the Teensy 3.0 it should be 3-6, 9, 10, and 20-23
int r = 3;
int g = 5;
int b = 4;

// Declare the keys. I was using the old WASD sample pack, so no clear. :(
int black = 1;
int red = 21;
int blue = 19;
int brown = 15;

// Declare an empty array to hold the key buffer until it gets sent.
// This will allow the teensy to send multiple simultaneous keypresses.
int key[] = {0,0,0,0,0,0};
int mod = 0;

//declare variables to hold the current values of the LEDs
int curRed = 0, curGreen = 0, curBlue = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the LED pins as output.
  // This allows them to be written to
  pinMode(led, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  
  // initialize the switch pins as input.
  // This allows the switches to be read
  pinMode(black, INPUT);
  pinMode(blue, INPUT); 
  pinMode(brown, INPUT);
  pinMode(red, INPUT); 
}

// This function will take keypresses passed to it (in the form of a char, for no particular reason)
// and add them to set of six keys that will be passed to the computer when Keyboard.send_now() is called.

// Basically, this collects the currently pressed keys and stores them until they cand be passed to the computer.
void setKey(char keypress){
  // Loops through until it finds a blank slot.
  int i;
  for(i = 0; key[i] != 0; i++){}
  
  key[i] = keypress;
  
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
  for(int i = 0; i < 6; i++){ key[i] = 0; }
  mod = 0;
}

void quickFade(int red, int green, int blue){
  boolean br=false, bg=false, bb=false;
  
  while(!br || !bg || !bb){
   if(curRed < red) curRed ++;
   else if(curRed > red) curRed --;
   else br = true;
   if(curGreen < green) curGreen ++;
   else if(curGreen > green) curGreen --;
   else bg = true;
   if(curBlue < blue) curBlue ++;
   else if(curBlue > blue) curBlue --;
   else bb = true;
   
   delay(5);
   
   LEDSet();
  } 
}

void LEDSet(){
  analogWrite(r, curRed);
  analogWrite(g, curGreen);
  analogWrite(b, curBlue);
}

// the loop routine runs over and over again forever:
void loop() {
  
  // There is probably a better way to do this, but fuck it. 
  // I gave every key its own if/else block.
  
  // Black switch
  if (digitalRead(black) == HIGH) {     // If black key is depressed
    digitalWrite(led, HIGH);            // Set pin 13 (on board LED) to high (turning it on)
    setKey(KEY_A);                      // Push KEY_A into the buffer using the setKey() method
  } 
  else {                                // If the key is not pressed
    digitalWrite(led, LOW);             // Set pin 13 (on board LED) to low (turning it off)
    setKey(0);                          // Push 0 into the buffer using the setKey() method, effectively clearing it.
  }
  
  // Blue switch
  if (digitalRead(blue) == HIGH) {
    digitalWrite(b, HIGH);
    setKey(KEY_SPACE);
  }
  else {
    digitalWrite(b, LOW);
    setKey(0);
  }
  
  // Brown switch
  if (digitalRead(brown) == HIGH) {
    digitalWrite(g, HIGH);
    setKey(KEY_W);
  }
  else{
    digitalWrite(g, LOW);
    setKey(0);
  }
  
  // Red switch
  if (digitalRead(red) == HIGH){
    digitalWrite(r, HIGH);
    setKey(KEY_D);
  }
  else{
    digitalWrite(r, LOW);
    setKey(0);
  }
  
  //Now that all of the keys have been polled it is time to send them out!
  sendKey();
  
  int randR, randG, randB;
  
  randR = rand() % 255;
  randG = rand() % 255;
  randB = rand() % 255;
  
  quickFade(randR, randG, randB);
}

