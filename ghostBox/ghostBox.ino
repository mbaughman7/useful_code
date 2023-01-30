#include <Servo.h>

int lights[] = { 2, 3, 4, 5 };
int button = 8;
int lightCount = 4;
bool openState = false;
int counter = 0;
int servoPin1 = 10;
int servoPin2 = 11;


Servo servo1;
Servo servo2;

void setup() {

  for (int i = 0; i < lightCount; i++) {
    pinMode(lights[i], OUTPUT);
  }
  pinMode(button, INPUT_PULLUP);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(0);
  servo2.write(0);

}

void loop() {
  if (digitalRead(button) == LOW && counter == 0){
    openState = !openState;
    counter = 1;
    lightToggle();
  }
  
  if (digitalRead(button) == HIGH){
  counter = 0;
  }
}


void lightToggle(){

  for (int i = 0; i < lightCount; i++) {
    digitalWrite(lights[i], openState);
  }

  if (openState == true){
    servo1.write(90);
    servo2.write(90);
  }
  else{
    servo1.write(0);
    servo2.write(0);
  }
  delay(800);

}
