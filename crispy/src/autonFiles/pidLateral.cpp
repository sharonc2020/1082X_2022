#include "main.h" 
#include "../include/pros/misc.h" 
//This is a commented test text for commit.

namespace pidLateral{
const double DEG_PER_INCHES = (4.25 * M_PI) / 360.0; //4.25 = wheel diameter, M_PI*4.25 = circumference of wheel

    double kp;
    double kd;
    
    double target;
    double position; //unsure yet
    double power;

    double error;
    double lastError;

    bool enabled;
}




