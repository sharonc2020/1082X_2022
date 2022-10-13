#include "main.h"
#include "pros/misc.h"
#include <chrono>
#include <string>

//sets the flywheel motor power
void setFlywheel(int power){
    fly1.moveVoltage(power*120);
    fly2.moveVoltage(power*120);
}

//flywheel piston
void setFlywheelPiston(bool set){
    flywheelPiston.set_value(set);
}

//conditions for the flywheel piston - uses Button A & B
// void setFlywheelPistonValue(){
//     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
//         setFlywheelPiston(true);
//         pros::delay(80);
//         setFlywheelPiston(false);
        
//     } 
// }


