//A test for the servo to make sure that your electronics work
//feel free to chop this to pieces and use it how you want
#include <EYW.h>

//ONE IMPORTANT NOTE: The default input for the servo is pin 3
//I can't change it without overwriting the function of the pin.
//If engineer your world had open documentation this wouldn't be
//a problem, so yeah. Your servo's signal pin has to be pin 3


//setting the camera part of the library to "cameraservo"
//in short, don't change this
EYW::Camera cameraservo;

void setup() {
  //Enables anything with the "cameraservo" tag
  //another one of the things that you shouldn't touch
  cameraservo.begin();


}

void loop() {
  //this is just going to make the servo wiggle back and fourth a lot
  cameraservo.calibrate();


}
