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
//Configuration
MotorGroup leftChassis({fleft.get_port(), bleft.get_port()});
MotorGroup rightChassis({fright.get_port(), bright.get_port()});

//pid db setup ChassisController---------------------------------------------------------------------------------
std::shared_ptr<ChassisController> chassis =
  ChassisControllerBuilder()
    .withMotors(leftChassis, rightChassis)
    // Green gearset, 4 in wheel diam, 11.5 in wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 15.5_in}, imev5GreenTPR})
    .build();
//AsynchController setups----------------------------------------------------------------------------------------
	//roller
	// std::shared_ptr<AsyncPositionController<double, double>> rollerController = 
	// AsyncPosControllerBuilder()
	// 	.withMotor(rollerMotor)
	// 	.build();

	//intake
	
	//actual autonomous functions------------------------------------------------------------------------------------    
	chassis->moveDistance(2_ft); // Drive forward 12 inches
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

/*//todo list
	- check okapi isnt overheating motors
	- once things are fixed, start PID
	
	future features
	- normal shot + three shots in a row flywheel
	- safety lock for endgame
*/


void opcontrol() {
	//variables
	bool toggle = false;
	bool latch = false;
	int power = 62;

	bool pistonPrevious = false;

	//buttons
	ControllerButton intakeButton(ControllerDigital::R1);
    ControllerButton revIntakeButton(ControllerDigital::R2);
    ControllerButton rollerButton(ControllerDigital::L1);
	ControllerButton rollerReverseButton(ControllerDigital::L2);

	ControllerButton shift(ControllerDigital::Y);

	//sets brakeModes
	fleft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    bleft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    fright.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    bright.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	while(true) {
	//Drive Base Control--------------------------------------------------------------------------------------------------------

	if(abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) <= 8 && abs(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)) <= 8){
	
	int pow = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		// if(pow < -40){
		// 	turn = -turn;
		// }

		int Left = pow + turn;
		int Right = pow - turn;

		if(abs(pow) < 5)
			pow = 0;

		if(abs(turn) < 5)
			turn = 0;

		fleft.move(Left*0.5);
		bleft.move(Left*0.5);

		fright.move(Right*0.5);
		bright.move(Right*0.5);

	} else{
			
		int pow = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

		int Left = pow + turn;
		int Right = pow - turn;

		if(abs(pow) < 5)
			pow = 0;

		if(abs(turn) < 5)
			turn = 0;

		fleft.move(Left*1.2);
		bleft.move(Left*1.2);

		fright.move(Right*1.2);
		bright.move(Right*1.2);
	}


	//Intake Drive Control--------------------------------------------------------------------------------------------------
			if (intakeButton.isPressed()) {
                intakeMotor.moveVoltage(-12000);
             } else if (revIntakeButton.isPressed()) {
                 intakeMotor.moveVoltage(12000);
        	 } 
			else {
                intakeMotor.moveVoltage(0);
            }
	//Roller Drive Control--------------------------------------------------------------------------------------------------
			if (rollerButton.isPressed()) {
                rollerMotor.moveVoltage(0.7*12000);
            } else if (rollerReverseButton.isPressed()) {
                rollerMotor.moveVoltage(0.7*-12000);
            }else {
                rollerMotor.moveVoltage(0);
            }
			
	//flywheel piston drive control-----------------------------------------------------------------------------------------

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			if(pistonPrevious == false){
				flywheelPiston.set_value(true);
				pros::delay(50);
				flywheelPiston.set_value(false);
				pistonPrevious = true;
			}
		} else{
			pistonPrevious = false;
		}
		
	//endgame
		// if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
		// 	endgameLeft.set_value(true);
		// 	endgameRight.set_value(true);
		// }



	//adjustable flywheel speed----------------------------------------------------------------------------------------------
		controller.print(1,1,"Power: %d", power);

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			power += 5;
			pros::delay(100);
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			power -= 5;
			pros::delay(100);
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			power -= 1;
			pros::delay(100);
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			power += 1;
			pros::delay(100);
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
			power = 100;
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
			power  = 62;
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			power = 93;
		} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			power = 75;
		}

		//sets flywheel speed to the variable "power"
		if(power >= 100){
			power = 100;
		} else if(power <= 0){
			power = 0;
		}

		//button toggling for flywheel
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

		//setRollerMotors();		
		pros::delay(10);
	}
}

