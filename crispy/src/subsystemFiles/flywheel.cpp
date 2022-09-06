#include "main.h"
#include "pros/misc.h"
#include <string>

//sets the flywheel motor power
void setFlywheel(int power){
    flywheel1 = power;
    flywheel2 = power;
}

//flywheel motors, currently only press, no toggle
//checks condition for flywheel button
void setFlywheelMotors(){
    bool state;
    bool last;
    int power;

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) && !last){
        state = !state;
        last = true;
    } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
        last = false;
    }

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
        power += 5;
    } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
        power -= 5;
    } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
        power -= 1;
    } else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        power += 1;
    }

    if(power >= 100){
        power = 100;
    } else if(power <= 0){
        power = 0;
    }
    std::string pPower = std::to_string(power);
    //controller.print(0, 0, ""+pPower);
    
    if (state){
        setFlywheel(power);
    } else{
        setFlywheel(0);
    }
}

//flywheel piston
void setFlywheelPiston(bool set){
    flywheelPiston.set_value(set);
}

void setFlywheelPistonValue(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        setFlywheelPiston(true);
    } else if(!controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        setFlywheelPiston(false);
    }    
}