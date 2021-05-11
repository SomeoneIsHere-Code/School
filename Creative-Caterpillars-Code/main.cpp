void setup() {
  //setting up all of the (placeholder) pins
  pinMode(2,OUTPUT);

  

}

void loop() {
  // put your main code here, to run repeatedly:

}

/* 
Since I can't actually code in our arduino and don't know 
what the inputs and outputs are I'm going to create as much of the
logic today as I can while making it easy on myself to add in the pins
and everything once we have that set in stone
In my usual style I'm going to probably over comment and use way too 
many variables and functions but it's how I code
I'm going to use alt to refer to altitude and to use the altimiter
whereas I will use dist to refer to distance using the ultrasonic
sensor
*/

//First I need to declare all of my variables

//the altitude at which we take the frst picture
int firstPicAlt = 100;

//the space between each picture after the first
int picDist = 10;

//the number of pictures that have been taken
int numPics = 0;

//the maximum amount of pictures that we are going to take
int targetPics = 0;

//maximum height for the drone to be considedered "on the ground"
int distToGround = 0;

//a temporary variable to represent the input from the altimiter
int altTemp = 110;

//same but for the ultrasonic sensor
int ultTemp = 0;

//a variable to see of 
bool descending = false;

//a temporary variable that will be replaced with a check to 
//see if the button has been pressed
int button = 0;

//the delay between pictures being taken
int picDelay = 0;

//checks to see if the button has been pressed at all
if (button == 1){

  //if the descent has started and it is on the ground then it resets the button and exits the loop
  if(descending == true && ultTemp<=distToGround){
    //flash LED
    button = 0;
    break
  } 

  //if the drone has reached the first picture height it takes a picture. It also has a small buffer area
  if(altTemp == firstPicAlt){
    digitalWrite(2,HIGH);
    delay(picDelay);
    digitalWrite(2,LOW);
    numPics++;
  }

  //This one is a doozy. Essentially if the remainder from the distance after the firstPicAlt 
  //divided by the picDist is zero then it takes a picture
    if((altTemp - firstPicALt)%picdist == 0){
    digitalWrite(2,HIGH);
    delay(picDelay);
    digitalWrite(2,LOW); 
    numPics++;
  }
  
  //if the drone has taken a target amount of pictures then it starts the descent
  if(numPics >= targetPics){
    descending = true ; 
  }


}
