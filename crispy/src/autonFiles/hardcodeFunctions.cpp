#include "main.h"
#include "pros/misc.h"

//with motors hardcode functions

void resetDriveEncoders(){
    fleft.tare_position();
    fright.tare_position();
    bleft.tare_position();
    bright.tare_position();
}

void translate(int units, int voltage){
    // resetDriveEncoders();

    // while(fleft.get_position() < units){
    //     setDrive(voltage, voltage);
    //     pros::delay(10);
    // }

    // setDrive(-10,-10);
    
}

//with encoders hardcode functions (if time only)