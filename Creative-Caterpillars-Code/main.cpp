#include <EYW.h>

EYW::Camera cameraservo;

EYW::RangeFinder proximity; 

EYW::Altimeter myaltimeter;

//the stand in for the button, 1 is on, 0 is off
int button = 1;

//the pin that the button will connect to
int buttonPin = 2;

//the pin that the buzzer will connect to
int buzzPin = 5;

//the altitude at which we take the frst picture
int firstPicAlt = 10;

//the space between each picture after the first
int picDist = 1;

//maximum height for the drone to be considedered "on the ground"
int Ground = 10;

//a temporary variable to represent the input from the altimiter
int Alt = 0;

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
  
  //Setup for the Altimeter
  myaltimeter.begin();

  myaltimeter.calibrate(1000);

  myaltimeter.alarm();
}

void loop() {
  //checks to see if the button has been pressed at all
  if(digitalRead(button) == HIGH){
  button = 1;
  }
  
  if (button == 1){
    
    //sets the variable "Dist" equal to the input from the ultrasonic sensor(cm)
    //and multiplies it by a number to convert it to feet
    Dist = proximity.getDistance();
    
    //takes 25 measurements and sets "Alt" to the average
    Alt = myaltimeter.getHeightAvg(25)/100;
    
    
    //if the descent has started and it is on the ground then it resets the button and exits the loop
    if(Dist<=Ground)
        for(int i = 0; i== 10; i++){
          cameraservo.alarm(buzzPin, 600, 100);
        }
  } 

    //if the drone has reached the first picture height it takes a picture. It also has a small buffer area
    if(Alt == firstPicAlt){
    cameraservo.getPicture();
  }

    //This one is a doozy. Essentially if the remainder from the distance after the firstPicAlt 
    //divided by the picDist is zero then it takes a picture
    if((Alt - firstPicAlt)%picDist == 0){
    cameraservo.getPicture();
  }

}
  
