/**************************Key Mapping ********************************/
#define BUTTON1_PRESS MEDIA_PLAY_PAUSE
#define BUTTON2_PRESS MEDIA_PREVIOUS
#define BUTTON3_PRESS MEDIA_NEXT
#define BUTTON4_PRESS KEY_F13
#define BUTTON5_PRESS KEY_F14

#define KNOB_PRESS MEDIA_VOLUME_MUTE
#define KNOB_CLOCKWISE MEDIA_VOLUME_UP
#define KNOB_COUNTER_CLOCKWISE MEDIA_VOLUME_DOWN

#define KNOB_SENSITIVITY 2 //1 - Very Sensitive by jittery | 2 - Best Performance | 3 - Very Slow | 4 - Even Slower (It takes 4 clicks to change the value ... etc)
/***********************************************************************/
#include "HID-Project.h"
#include <Bounce2.h>

#define BUTTON1_PIN 6
#define BUTTON2_PIN 5
#define BUTTON3_PIN 4
#define BUTTON4_PIN 3
#define BUTTON5_PIN 2
#define KNOB_PIN_A 7
#define KNOB_PIN_B 8
#define KNOB_BUTTON_PIN 9
#define DEBOUNCE_DELAY 50

/* Declare Buttons */
Bounce button1 = Bounce();
Bounce button2 = Bounce();
Bounce button3 = Bounce();
Bounce button4 = Bounce();
Bounce button5 = Bounce();
Bounce knobButton = Bounce();

/* Declare Rotary Encoder */
int knobCounter = 0; 
int knobState;
int knobLastState;  

void setup() {
  Serial.begin(9600);
  Consumer.begin();
  Keyboard.begin();
  
  button1.attach(BUTTON1_PIN, INPUT_PULLUP);
  button1.interval(DEBOUNCE_DELAY);

  button2.attach(BUTTON2_PIN, INPUT_PULLUP);
  button2.interval(DEBOUNCE_DELAY);

  button3.attach(BUTTON3_PIN, INPUT_PULLUP);
  button3.interval(DEBOUNCE_DELAY);

  button4.attach(BUTTON4_PIN, INPUT_PULLUP);
  button4.interval(DEBOUNCE_DELAY);

  button5.attach(BUTTON5_PIN, INPUT_PULLUP);
  button5.interval(DEBOUNCE_DELAY);

  knobButton.attach(KNOB_BUTTON_PIN, INPUT_PULLUP);
  knobButton.interval(DEBOUNCE_DELAY);

  pinMode (KNOB_PIN_A, INPUT_PULLUP);
  pinMode (KNOB_PIN_B, INPUT_PULLUP);
  knobLastState = digitalRead(KNOB_PIN_A);   
}

void loop() {

  //Button 1
  button1.update();
  if(button1.fell())
  {
      Consumer.write(BUTTON1_PRESS);
  }

  //Button 2
  button2.update();
  if(button2.fell())
  {
      Consumer.write(BUTTON2_PRESS);
  }

  //Button 3
  button3.update();
  if(button3.fell())
  {
      Consumer.write(BUTTON3_PRESS);
  }

  //Button 4
  button4.update();
  if(button4.fell())
  {
      //Consumer.write(BUTTON4_PRESS);
      Keyboard.write(BUTTON4_PRESS);
  }

  //Button 5
  button5.update();
  if(button5.fell())
  {
    //Consumer.write(BUTTON5_PRESS);
      Keyboard.write(BUTTON5_PRESS);
  }

  //Knob Button
  knobButton.update();
  if(knobButton.fell())
  {
      Consumer.write(KNOB_PRESS);
  }

  //Knob Rotation
  knobState = digitalRead(KNOB_PIN_A);
  if (knobState != knobLastState)
  {
    if (digitalRead(KNOB_PIN_B) != knobState) 
    {
      knobCounter ++;
      if(knobCounter >= KNOB_SENSITIVITY) 
      {
        knobCounter = 0;
        Consumer.write(KNOB_CLOCKWISE);
      }
    } else {
      knobCounter --;
      if(knobCounter <= -1 * KNOB_SENSITIVITY)
      {
        knobCounter = 0;  
        Consumer.write(KNOB_COUNTER_CLOCKWISE);
      }
    }
  }
  
  knobLastState = knobState;
}
