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
	endgameLeft.set_value(false);

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

void moveTime(okapi::QLength distance, int timeout) {
    //  chassis->moveDistanceAsync(distance); // move to the target asynchronously (without waiting)
    //  long endTime = pros::millis() + timeout; // determine when to stop if it hasnt settled
    //  while(!chassis->isSettled()) { // loop if not settled
    //       if(pros::millis() >= endTime) { // if not settled and time has ran out
    //            chassis->stop();
    //            break; // break the loop and continue with autonomous
    //       }
    //       pros::delay(20);
    //  }
}

//helper simplifying functions
void hardCodeLateral(int inches, int speed){
	//double inchestoTicks = M_PI*4.125 / 360;
  fleft.move_relative(inches, speed); // Moves 100 units forward
  bleft.move_relative(inches, speed);
  fright.move_relative(inches, speed);
  bright.move_relative(inches, speed);
  
  while (!((fleft.get_position() < inches+5) && (fleft.get_position() > inches-5))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }

}

void hcTimeTurn(int speed, int time){
  fleft.move_voltage(-1*speed); // Moves 100 units forward
  bleft.move_voltage(-1*speed);
  fright.move_voltage(speed);
  bright.move_voltage(speed);
  
  pros::delay(time);

  fleft.brake();
  bleft.brake();
  fright.brake();
  bright.brake();
}

void move(int speed, int time){
  fleft.move_voltage(speed); // Moves 100 units forward
  bleft.move_voltage(speed);
  fright.move_voltage(speed);
  bright.move_voltage(speed);
  
  pros::delay(time);

  fleft.brake();
  bleft.brake();
  fright.brake();
  bright.brake();
}

void roll(int speed, int time, int rollVolt, int rollTime){
  fleft.move_voltage(speed); // Moves 100 units forward
  bleft.move_voltage(speed);
  fright.move_voltage(speed);
  bright.move_voltage(speed);

  rollerMotor.moveVoltage(rollVolt);

  pros::delay(rollTime);

    rollerMotor.moveVoltage(0);
  
pros::delay(time);

  fleft.brake();
  bleft.brake();
  fright.brake();
  bright.brake();

}

void intake(int speed, int time, int intakeTime){
  fleft.move_voltage(speed); // Moves 100 units forward
  bleft.move_voltage(speed);
  fright.move_voltage(speed);
  bright.move_voltage(speed);

  intakeMotor.moveVoltage(-12000);

  pros::delay(intakeTime);

    intakeMotor.moveVoltage(0);

  fleft.brake();
  bleft.brake();
  fright.brake();
  bright.brake();
}

void setBrakeMode(pros::motor_brake_mode_e b){
	fleft.set_brake_mode(b);
	bleft.set_brake_mode(b);
	fright.set_brake_mode(b);
	bright.set_brake_mode(b);
}

void flywheel(int speed, int time, int shootTimes){

    fly1.moveVoltage(speed*120);
    fly2.moveVoltage(speed*120);

	pros::delay(time);

	for(int x = 0; x < shootTimes; x++){
		setFlywheelPiston(true);
        pros::delay(80);
        setFlywheelPiston(false);
		pros::delay(700);
	}

	pros::delay(500);
	fly1.moveVoltage(0);
	fly2.moveVoltage(0);
}

///actual autons

void leftAuton(){
	roll(4000, 430, -6500, 350);
	move(-5000, 150);
}

void rightAuton(){
//pos # = left, neg# = right
	setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	//starts with flywheel aimed towards low goal; shoots two preloads into alliance low goal
	flywheel(70, 1500, 2);
	//move forwards, turn, and then changes roller to correct color
	move(8000, 865);
	hcTimeTurn(-5500, 930);
	move(8000, 200);
	roll(4000, 430, -6500, 350);

	//backs up and turn to align with diagonal line of discs
	move(-5000, 200);
	hcTimeTurn(-5000, 1180);

	//intakes discs while going down the line
	intake(8300, 100, 2700);
	intakeMotor.moveVoltage(-12000);
	move(9000, 380);
	pros::delay(200);
	//backs up until more centered with low goal, turns, and shoots 3 more discs into low goal
	move(-12000, 850);
	hcTimeTurn(-5400, 870);
	flywheel(70, 800, 3);
	intakeMotor.moveVoltage(0);	
}

void skills(){
	setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	//starts with the robot intake at the auton edge line, flywheel faced towards goal
	//robot drives backwards and turns a bit to aim towards high goal
	move(-7000, 1100);
	hcTimeTurn(-3000, 75);
	//shoot preloads into high goal; moves backwards until aligned with roller
	flywheel(6, 1500, 2);
	hcTimeTurn(3000, 100);
	move(8000, 1600);
	//turns 90 degrees and do the roller
	hcTimeTurn(-5000, 860);
	roll(4000, 430, -12000, 680);
	//back up, turn, and then move down to intake the diagonal line of discs
	move(-4500, 170);
	hcTimeTurn(5000, 1600);
	intake(6500, 100, 3500);
	intakeMotor.moveVoltage(-12000);
	pros::delay(3000);
	//back up and keep on intaking to fully drop off discs in the hopper
	move(-7000, 700);
	intakeMotor.moveVoltage(0);
	//line up against the angler; shoot 3 times into the high goal
	hcTimeTurn(-5400, 820);
	move(-10000, 1000);
	flywheel(64, 1000, 3);
	//move forwards, release endgame
	move(9000, 380);
	endgameLeft.set_value(false);
	intakeMotor.moveVoltage(0);
}

void disasterControlSkills(){
	roll(5000, 430, -12000, 600);
	move(-5000, 1200);
	hcTimeTurn(-5000, 950);
	move(5000, 1500);
	roll(5000, 430, -12000, 600);
	endgameLeft.set_value(true);
}

void autonomous() {
	rightAuton();

// chassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::hold); 
// 	chassis->setMaxVelocity(100);
// 	chassis->moveDistance(24_in); // Drive backwards 12 inches
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
	int power = 75;

	bool pistonPrevious = false;

	//buttons
	ControllerButton intakeButton(ControllerDigital::R1);
    ControllerButton revIntakeButton(ControllerDigital::R2);
    ControllerButton rollerButton(ControllerDigital::L1);
	ControllerButton rollerReverseButton(ControllerDigital::L2);
	ControllerButton endButton(ControllerDigital::B);

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
                intakeMotor.moveVoltage(12000);
             } else if (revIntakeButton.isPressed()) {
                 intakeMotor.moveVoltage(-12000);
        	 } 
			else {
                intakeMotor.moveVoltage(0);
            }
	//Roller Drive Control--------------------------------------------------------------------------------------------------
			if (rollerReverseButton.isPressed()) {
                rollerMotor.moveVoltage(12000);
            } else if (rollerButton.isPressed()) {
                rollerMotor.moveVoltage(-12000);
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
		if(endButton.isPressed()){
			endgameLeft.set_value(true);
			// pros::delay(80);
			// endgameLeft.set_value(true);
			//endgameRight.set_value(true);
		}




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
			power  = 80;
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

