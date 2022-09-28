#include "main.h" 
#include "../include/pros/misc.h" 

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
	
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Sharon was here");

	fleft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	fright.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	bleft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	bright.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	roller.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	fleft.move_relative(180.0, 80);
	
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	bool toggle = false;
	bool latch = false;
	int power = 93;

	while(true) {
		
		//control drive methods
		setDriveMotors();
		setIntakeMotorsPress();
		setRollerMotors();
		setFlywheelPistonValue();

		//adjustable flywheel speed
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			power = 100;
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			//power  = 50;
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			power = 93;
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			//power += 1;
		}
		//sets flywheel speed to the variable "power"
		// if(power >= 100){
		// 	power = 100;
		// } else if(power <= 0){
		// 	power = 0;
		// }

		//button toggling
		if(toggle){
			setFlywheel(power);
		} else{
			setFlywheel(0);
		}

	  	if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
			if(!latch){
				toggle = !toggle;
				latch = true;
			}
		}	else{
			latch = false;
		}

		controller.clear();
		controller.print(1, 1, "hello");
		
		pros::delay(20);
	}
}

