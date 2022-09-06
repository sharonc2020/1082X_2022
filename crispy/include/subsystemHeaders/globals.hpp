#pragma once
#include "main.h"
#include "pros/adi.hpp"

//drivebase motors
extern pros::Motor fleft;
extern pros::Motor fright;
extern pros::Motor bleft;
extern pros::Motor bright;

//subsystem motors
extern pros::Motor intake;
extern pros::Motor roller;
extern pros::Motor flywheel1;
extern pros::Motor flywheel2;

//pistons
extern pros::ADIDigitalOut flywheelPiston;

//Controller
extern pros::Controller controller;


