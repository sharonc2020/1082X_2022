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
    fleft = left;
    bleft = left;
    fright = right;
    bright = right;

    fleft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    bleft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    fright.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    bright.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
//////////////////OKAPI TESTS BEGIN HERE/////////////////////////////
void okapiChassisSetup(){
        std::shared_ptr<okapi::ChassisController> drive =
        ChassisControllerBuilder()
            .withMotors({1, -11}, {-10,20})
            // Green gearset, 4 in wheel diam, 11.5 in wheel track  //UPDATE THIS IN A BIT
            //ADD WITH SENSORS//////////////////////////////////////////////////////////////////////////////////////////////////
            .withSensors(
        RotationSensor{1}, // Left encoder in V5 port 1
        RotationSensor{2, true}  // Right encoder in V5 port 2 (reversed)
            )
            .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
            .build();
}