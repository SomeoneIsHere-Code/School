/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    20, 3, 2, 10, 8 
// Front_Lift           motor         9               
// Back_Lift            motor         4               
// Ring                 motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

//Storage for the Autononous we will use
int   autonomousSelection = -1;

// collect data for on screen button and include off and on color feedback for button
// prc - instead of radio approach with one button on or off at a time, each button has a state.

typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *label;
} button;

// Button array definitions for each software button. The purpose of each button data structure
// is defined above.  The array size can be extended, so you can have as many buttons as you 
// wish as long as it fits.
button buttons[] = {
    {   30,  30, 60, 60,  false, 0xE00000, 0x0000E0, "Ally" },
    {  150,  30, 60, 60,  false, 0x303030, 0xD0D0D0, "Start" },
    {  270,  30, 60, 60,  false, 0x303030, 0xF700FF, "Park" },
    {  390,  30, 60, 60,  false, 0x303030, 0xDDDD00, "Shoot" },
    {   30, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "4-" },
    {  150, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "5-" },
    {  270, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "6-" },
    {  390, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "7-" }
};


// forward ref
void displayButtonControls( int index, bool pressed );

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int
findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void
initButtons() {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      buttons[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
    }

}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      // clear all buttons to false, ie. unselected
      //      initButtons(); 

      // now set this one as true
      if( buttons[index].state == true) {
      buttons[index].state = false; }
      else    {
      buttons[index].state = true;}

      // save as auton selection
      autonomousSelection = index;

      displayButtonControls( index, false );
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void
displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {

      if( buttons[i].state )
        c = buttons[i].onColor;
      else
        c = buttons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
      }
      else
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

      // outline
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );

// draw label
      if(  buttons[i].label != NULL )
        Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].label );
    }
}



// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //makin sure that the lift motors are moving at 100% speed during auton
  Front_Lift.setVelocity(100, percent);
  Back_Lift.setVelocity(100, percent);
  Ring.setVelocity(100, percent);


  //setting lift motors so they hold when braking, this makes our lift not slide
  Front_Lift.setBrake(hold);
  Back_Lift.setBrake(hold);
  
  Front_Lift.setPosition(0, degrees);
  Back_Lift.setPosition(0, degrees);
  

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // if the button in the first position (programmers start counting from 0)
  // then it executes the things in this if loop
  // if not, it moves on to the else loop
  if(buttons[0].state){

  }


//lower lift
Back_Lift.spinTo(-480, degrees, true);

//drive forward 12 inches
Drivetrain.driveFor(reverse, 16, inches);

//raise front lift to golden angle
Back_Lift.spinTo(-157, degrees, true);

//start spinning the Ring motor
Ring.setVelocity(100, percent);
Ring.spin(forward);

/*
//rotate 90 degrees left
Drivetrain.turnFor(-90, degrees);

//drive forward 12 inches
Drivetrain.driveFor(reverse, 12, inches);

//rotate 90 degrees right
Drivetrain.turnFor(90, degrees);

//start spinning the ring lift
Ring.spin(forward);

//drive forward 36 inches
Drivetrain.driveFor(reverse, 36, inches);

//stop spinning the ring lift
Ring.stop();

//drive forward 60 inches
Drivetrain.driveFor(forward, 60, inches);
*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
