#include "main.h"
#include "pros/misc.h"
#include <string>

//sets the flywheel motor power
void setFlywheel(int power){
    flywheel1 = power;
    flywheel2 = power;
}

//flywheel piston
void setFlywheelPiston(bool set){
    flywheelPiston.set_value(set);
}

//conditions for the flywheel piston - uses Button A & B
void setFlywheelPistonValue(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        setFlywheelPiston(true);
        
    } else if(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        setFlywheelPiston(false);
    }    
}


