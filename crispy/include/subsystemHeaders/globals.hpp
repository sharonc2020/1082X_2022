#pragma once
#include "main.h"
#include "pros/adi.hpp"

//drivebase motors
extern pros::Motor fleft;
extern pros::Motor fright;
extern pros::Motor bleft;
extern pros::Motor bright;

//okapi db motors///////////////////////////////////
// extern okapi::Motor okfleft;
// extern okapi::Motor okfright;
// extern okapi::Motor okbleft;
// extern okapi::Motor okbright;

// extern std::shared_ptr<ChassisController> chassis;
// extern std::shared_ptr<AsyncPositionController<double, double>> rollerController;
// extern std::shared_ptr<AsyncPositionController<double, double>> intakeController;
// extern std::shared_ptr<AsyncPositionController<double, double>> flywheelController;

///////////////////////////////////////////////////////

//subsystem motors
extern Motor intakeMotor;
extern Motor rollerMotor;
extern Motor fly1;
extern Motor fly2;

//pistons
extern pros::ADIDigitalOut flywheelPiston;
extern pros::ADIDigitalOut endgameLeft;
//extern pros::ADIDigitalOut endgameRight;

//sensors
extern okapi::RotationSensor rotLeft;
extern okapi::RotationSensor rotRight;

//Controller
extern pros::Controller controller;


