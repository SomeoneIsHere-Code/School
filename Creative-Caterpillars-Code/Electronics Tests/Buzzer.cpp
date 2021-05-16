//A test for the buzzer to make sure that your electronics work
//feel free to chop this to pieces and use it how you want
#include <EYW.h>

//The pin that the button gets input into
int buttonPin = 2;

//the pin that goes to the positive leg of the buzzer
int buzzPin = 5; 

//setting the camera part of the library to "cameraservo"
//in short, don't change this
EYW::Camera cameraservo;

void setup() {
  //Setting the button pin to intake a signal
  pinMode(buttonPin, INPUT);

  //Enables anything with the "cameraservo" tag
  //another one of the things that you shouldn't touch
  cameraservo.begin();
}

void loop() {
  if (cameraservo.buttonPressed()==true||digitalRead(buttonPin)==HIGH) {
    cameraservo.alarm(buzzPin, 600, 100);
  }

}
