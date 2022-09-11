#include "main.h"

//drivebase motors
pros::Motor fleft(11, pros::E_MOTOR_GEARSET_18, true); //11 at home true //1 at school true
pros::Motor bleft(19, pros::E_MOTOR_GEARSET_18, true); //19 at home true //11 at school false

pros::Motor fright(1, pros::E_MOTOR_GEARSET_18, false); //12 at home false //10 at school false 
pros::Motor bright(2, pros::E_MOTOR_GEARSET_18, false); //13 at home false //20 at school true

//subsystem motors
pros::Motor intake(3, pros::E_MOTOR_GEARSET_06, true); //__ at school
pros::Motor roller(9, pros::E_MOTOR_GEARSET_18, false); //__ at school
pros::Motor flywheel1(12, pros::E_MOTOR_GEARSET_06, false);
pros::Motor flywheel2(13, pros::E_MOTOR_GEARSET_06, false);

//pneumatics
pros::ADIDigitalOut flywheelPiston('A');

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

