//A test for the Ultrasonic sensor to make sure that your electronics work
//feel free to chop this to pieces and use it how you want
#include <EYW.h>

//setting the RangeFinder part of the library to "proximity"
//in short, don't change this
EYW::RangeFinder proximity;

//(a double is just an int that can store decimals) 
//The variable for distance from the ultrasonic sensor
double Dist = 0;

void setup() {
  //Creating a serial monitor. In short, it watches the values coming in from
  //the arduino. Your computer must be connected to the board by usb for this to work
  //No touch
  Serial.begin(9600);

  //Enables anything with the "proximity" tag
  //another one of the things that you shouldn't touch
  proximity.begin();
  proximity.alarm();
}

void loop() {

  //sets the variable "Dist" equal to the input from the ultrasonic sensor(cm)
  //and multiplies it by a number to convert it to feet
  //to have it output centimeters just remove anything between the ) and ;
  Dist = proximity.getDistance();

  //print what is in the parenthases to the serial monitor that we set up above
  Serial.print("Current Distance: ");

  //print the number Dist and then hit enter
  Serial.println(Dist);
}
