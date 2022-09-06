#include "main.h"
#include "pros/misc.h"

//calculates power for the motors
void setDriveMotors() {
    int power = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

    int Left = power + turn;
    int Right = power - turn;

    if(abs(power) < 5)
        power = 0;

    if(abs(turn) < 5)
        turn = 0;
    
    //takes calculated values and send to setDrive
    setDrive(Left, Right);

}

//sets the motors to the speed that was calculated
void setDrive(int left, int right) {
    fleft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    bleft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    fright.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    bright.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    fleft = left;
    bleft = left;
    fright = right;
    bright = right;
}

