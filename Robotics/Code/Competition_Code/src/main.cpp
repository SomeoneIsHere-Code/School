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
