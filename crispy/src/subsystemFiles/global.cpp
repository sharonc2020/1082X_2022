#include "main.h"

//drivebase motors
pros::Motor fleft(1, pros::E_MOTOR_GEARSET_18, true); //11 at home true //1 at school true
pros::Motor bleft(11, pros::E_MOTOR_GEARSET_18, false); //19 at home true //11 at school false

pros::Motor fright(10, pros::E_MOTOR_GEARSET_18, false); //12 at home false //10 at school false 
pros::Motor bright(20, pros::E_MOTOR_GEARSET_18, true); //13 at home false //20 at school true

//okapi db///////////////////////////////////////////
// okapi::Motor okfleft(1);
// okapi::Motor okbleft(11);
// okapi::Motor okfright(10);
// okapi::Motor okbright(20);

// //Configuration
// MotorGroup leftChassis({fleft.get_port(), bleft.get_port()});
// MotorGroup rightChassis({fright.get_port(), bright.get_port()});

// //pid db setup ChassisController---------------------------------------------------------------------------------
// std::shared_ptr<ChassisController> chassis =
//   ChassisControllerBuilder()
//     .withMotors(leftChassis, rightChassis)
//     // Green gearset, 4 in wheel diam, 11.5 in wheel track
//     .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 15.5_in}, imev5GreenTPR})
//     .build();

// //intake
// std::shared_ptr<AsyncPositionController<double, double>> intakeController = 
// 	AsyncPosControllerBuilder()
// 		.withMotor(intakeMotor)
// 		.build();

// //roller
// std::shared_ptr<AsyncPositionController<double, double>> rollerController = 
// 	AsyncPosControllerBuilder()
// 		.withMotor(rollerMotor)
// 		.build();

// //flywheel
// 	std::shared_ptr<AsyncPositionController<double, double>> flywheelController = 
// 	AsyncPosControllerBuilder()
// 		.withMotor({fly1, fly2})
// 		.build();
// //okapi db/////////////////////////////////////////////////////


//subsystem motors
Motor intakeMotor(3);
Motor rollerMotor(9);
Motor fly1(7);
Motor fly2(8);

//pneumatics
pros::ADIDigitalOut flywheelPiston('A');
pros::ADIDigitalOut endgameLeft('B');
//pros::ADIDigitalOut endgameRight('B');

//Sensors
okapi::RotationSensor rotLeft(14);
okapi::RotationSensor rotRight(17);

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

