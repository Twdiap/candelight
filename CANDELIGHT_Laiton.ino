#include <Servo.h>

byte button;
byte oldbutton = 0;
byte buttonpin = 14;
byte state = 0;

Servo servo1;

void setup()
{
  pinMode(buttonpin, INPUT);
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(5, LOW);
}

void loop()
{
  button = digitalRead(buttonpin);
  if(button && !oldbutton) // same as if(button == high && oldbutton == low)
  {
    //we have a new button press
    if(state == 0) // if the state is off, turn it on
    {
      digitalWrite(5, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
      servo1.attach(12);  //gas opening
      servo1.write(40);
      delay(250);
      digitalWrite(5, HIGH);
      delay(100);            
      digitalWrite(5, LOW);  
      delay(100);
      digitalWrite(5, HIGH);
      delay(100);            
      digitalWrite(5, LOW);
      delay(100); 
      digitalWrite(5, HIGH);
      delay(100);            
      digitalWrite(5, LOW);  
      state = 1;
    }
    else // if the state is on, turn it off
    {
      digitalWrite(LED_BUILTIN, LOW);
      servo1.attach(12);
      servo1.write(90);    //gas closing
      delay(100);
      servo1.detach();
      delay(100);
      state = 0; 
    }
    oldbutton = 1;
  }
  else if(!button && oldbutton) // same as if(button == low && oldbutton == high)
  {
    // the button was released
    oldbutton = 0;
  }
}