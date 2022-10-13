#include "main.h"

//drivebase motors
pros::Motor fleft(1, pros::E_MOTOR_GEARSET_18, true); //11 at home true //1 at school true
pros::Motor bleft(11, pros::E_MOTOR_GEARSET_18, false); //19 at home true //11 at school false

pros::Motor fright(10, pros::E_MOTOR_GEARSET_18, false); //12 at home false //10 at school false 
pros::Motor bright(20, pros::E_MOTOR_GEARSET_18, true); //13 at home false //20 at school true

//okapi db///////////////////////////////////////////
// okapi::Motor okfleft(11);
// okapi::Motor okbleft(19);
// okapi::Motor okfright(-12);
// okapi::Motor okbright(-13);
//okapi db/////////////////////////////////////////////////////


//subsystem motors
Motor intakeMotor(3);
Motor rollerMotor(9);
Motor fly1(7);
Motor fly2(8);

//pneumatics
pros::ADIDigitalOut flywheelPiston('C');
pros::ADIDigitalOut endgameLeft('A');
pros::ADIDigitalOut endGameRight('E');

//Sensors
okapi::RotationSensor rotLeft(14);
okapi::RotationSensor rotRight(17);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

