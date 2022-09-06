using namespace vex;

extern brain Brain;

//done
extern motor LFront;
extern motor RFront;
extern motor LTop;
extern motor RTop;

extern motor flywheelMotor1;
extern motor flywheelMotor2;
extern motor_group flywheelGroup;

extern digital_out pneu;
extern motor intake;
extern motor roller;

extern controller Controller1;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
