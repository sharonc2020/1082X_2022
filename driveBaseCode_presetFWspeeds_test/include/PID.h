#include "vex.h"
#include <math.h>

namespace PID1{
  extern double kp,ki,kd;
  extern double p,i,d;

  extern double error;
  extern double prevError;
  extern double totalError; //not necesssarily needed right now

  extern double circumference;
  extern double target;

  extern bool enabled;
  extern double powerValue;
  extern double averageDistance;

  extern void PIDOn(double tgt);
  extern void PID();
}
