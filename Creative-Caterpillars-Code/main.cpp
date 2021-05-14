#include <EYW.h>

EYW::Camera cameraservo;

EYW::RangeFinder proximity; 

//the stand in for the button, 1 is on, 0 is off
int button = 1;

//the pin that the button will connect to
int buttonPin = 2;

//the pin that the buzzer will connect to
int buzzPin = 5;

//the altitude at which we take the frst picture
int firstPicAlt = 0;

//the space between each picture after the first
int picDist = 0;

//the number of pictures that have been taken
int numPics = 0;

//the maximum amount of pictures that we are going to take
int targetPics = 0;

//maximum height for the drone to be considedered "on the ground"
int Ground = 0;

//a temporary variable to represent the input from the altimiter
int altTemp = 0;

//the readout from the ultrasonic sensor, ie the distance to the ground
int Dist = 0;

void setup() {
  //setting up all of the pins
  
  pinMode(buttonPin, INPUT);
  
  //creating a serial monitor aka reading the values that come in the serial port
  Serial.begin(9600);
    
  //Starting the servo
  cameraservo.begin();

  //starting the ultrasonic sensor
  proximity.begin();

  proximity.alarm();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //checks to see if the button has been pressed at all
  if(digitalRead(button) == HIGH){
  button = 1;
  }
  
  if (button == 1){

    //if the descent has started and it is on the ground then it resets the button and exits the loop
    if(Dist<=Ground){
    cameraservo.alarm(buzzPin, 600, 100);
  } 

    //if the drone has reached the first picture height it takes a picture. It also has a small buffer area
    if(altTemp == firstPicAlt){
    caneraservo.getPicture();
    numPics++;
  }

    //This one is a doozy. Essentially if the remainder from the distance after the firstPicAlt 
    //divided by the picDist is zero then it takes a picture
    if((altTemp - firstPicALt)%picdist == 0){
    cameraservo.getPicture();
    numPics++;
  }

}
  
}



