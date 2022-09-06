#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

//if you see the direction of controls messed up again, try messing with the true/false of the motors in robot-config.cpp (LTop top motor, LFront bottom motor)
  //common scenarios:
        //Forwards backwards flipped: turn all true/false to the opposites
        //One/Two sides not running: try changing only one of the side's motors, they might be spinning in opposite directions and conflicting
        
motor LFront = motor(PORT11, ratio6_1, false);
motor LTop = motor(PORT1, ratio6_1, true);
motor RFront = motor(PORT10, ratio6_1, true);
motor RTop = motor(PORT20, ratio6_1, false);

/////////////////////////////////////////////////////////////////////////////
digital_out pneu = digital_out(Brain.ThreeWirePort.A);

motor flywheelMotor1 = motor(PORT8, ratio6_1, false);
motor flywheelMotor2 = motor(PORT7, ratio6_1, false);
motor_group flywheelGroup = motor_group(flywheelMotor1, flywheelMotor2);

motor intake = motor(PORT3, ratio6_1, false);
motor roller = motor(PORT9, ratio6_1, false);

controller Controller1 = controller(primary);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}