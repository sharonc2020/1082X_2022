/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "PID.h"

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
bool swtch = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
 
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



//auton functions/methods set up//////////////////////////////////////////////////////





/////////Functions end here//////

//You guys dont need to touch the autonomous unless you're trying to code a new auton
void autonomous(void) {
 
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

//ANYTHING WRONG WITH USERCONTROL WILL BE IN THIS SECTION/////////////

int flywheelSpeed = 100; 
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    if(Controller1.Axis3.value() < 5 && Controller1.Axis3.value() > -5 && Controller1.Axis1.value() > -5 && Controller1.Axis1.value() < 5){
      //driving brake mode is here, change to brake if you feel like it's gliding too much
      LTop.stop(coast);
      RTop.stop(coast);
      RFront.stop(coast);
      LFront.stop(coast);
    }
    else{
      //if you see the direction of controls messed up again, try messing with the true/false of the motors in robot-config.cpp (LTop top motor, LFront bottom motor)
      LTop.spin(fwd, (Controller1.Axis3.value() + Controller1.Axis4.value()), pct);
      LFront.spin(fwd, (Controller1.Axis3.value() + Controller1.Axis4.value()), pct);
      RFront.spin(fwd, (Controller1.Axis3.value() - Controller1.Axis4.value()), pct);
      RTop.spin(fwd, (Controller1.Axis3.value() - Controller1.Axis4.value()), pct);
    }

//adjusts speeds/presets for flywheel here
         if(Controller1.ButtonUp.pressing()){
           flywheelSpeed = 100;
         }
         if(Controller1.ButtonRight.pressing()){
           flywheelSpeed = 80;
         }
         if(Controller1.ButtonDown.pressing()){
           flywheelSpeed = 65;
         } 
         if(Controller1.ButtonLeft.pressing()){
           flywheelSpeed = 50;
         } 

//toggle flywheel buttons: X spin and Y stop
       bool motorStateFW;
        if(Controller1.ButtonX.pressing()){
          motorStateFW = true;
        }
        if(Controller1.ButtonY.pressing()){
          motorStateFW = false;
        }

        if(motorStateFW == true){
          flywheelGroup.spin(fwd,flywheelSpeed,pct);
        } else{
          flywheelGroup.stop();
        }

//toggle intake buttons, R1 spin R2 stop
        bool motorStateI;
        if(Controller1.ButtonR1.pressing()){
          motorStateI = true;
        }
        if(Controller1.ButtonR2.pressing()){
          motorStateI = false;
        }

        if(motorStateI == true){
          intake.spin(fwd,100,pct);
        } else{
          intake.stop();
        }

//toggle roller buttons, L1 spin L2 stop
        bool motorStateR;
        if(Controller1.ButtonL1.pressing()){
          motorStateR = true;
        }
        if(Controller1.ButtonL2.pressing()){
          motorStateR = false;
        }

        if(motorStateR == true){
          roller.spin(fwd,100,pct);
        } else{
          roller.stop();
        }

//toggles pneumatics
        if(Controller1.ButtonA.pressing()){
          pneu.set(true);
        }else if(Controller1.ButtonB.pressing()){
          pneu.set(false);
        }
   
    
   //print statements to test what current flywheel speed is 
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearScreen();
    Controller1.Screen.print(flywheelSpeed);
    wait(20, msec); 
    
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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
