//A test for the altimeter to make sure that your electronics work
//feel free to chop this to pieces and use it how you want
#include <EYW.h>

//setting the Altimeter part of the library to "myaltimeter"
//in short, don't change this
EYW::Altimeter myaltimeter;

//(a double is just an int that can store decimals) 
//a variable to store the altitude
double Alt = 0;
void setup() {
  
  //Creating a serial monitor. In short, it watches the values coming in from
  //the arduino. Your computer must be connected to the board by usb for this to work
  //No touch
  Serial.begin(9600);

  //Enables anything with the "proximity" tag
  //don't touch
  myaltimeter.begin();

  //takes 1000 measurements and sets that value to be the 0
  myaltimeter.calibrate(1000);

  //this just needs to be here, idk why, I can't look at the documentation
  myaltimeter.alarm();
}

void loop() {
  //takes 50 measurements and sets "Alt" to the average
  Alt = myaltimeter.getHeightAvg(50);

  //Prints what's in the parentases to the serial monitor
  Serial.print("Current Height: ");

  //prints the value stored in the variable "Alt" and then hits enter
  Serial.println(Alt);

}
