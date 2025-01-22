#include <Servo.h>
#define BUTTON_PIN 14

Servo servo1;
Servo servo2;

byte lastButtonState = LOW;
byte candleState = LOW;

void setup() {

  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(5, LOW);

}

void loop() {
  byte buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    if (buttonState == LOW) {
      candleState = (candleState == HIGH) ? LOW: HIGH;
      servo1.attach(4);
      servo1.write(1);    //iris opening
      delay(100);
      servo1.detach();
      delay(400);
      servo2.attach(12);  //gas opening
      servo2.write(55);
      delay(100);
      delay(250);
      digitalWrite(5, HIGH);
      delay(100);            
      digitalWrite(5, LOW);  
      delay(100);
      digitalWrite(5, HIGH);
      delay(100);            
      digitalWrite(5, LOW);  
    }
    else if(buttonState == HIGH) {
      servo2.attach(12);
      servo2.write(90);    //gas closing
      delay(100);
      servo2.detach();
      delay(100);
      servo1.attach(4);
      servo1.write(180);   //iris closing
      delay(100);
      servo1.detach();
    }
  }
}
