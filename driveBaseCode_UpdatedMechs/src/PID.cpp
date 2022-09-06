#include "vex.h"
#include "vex_units.h"
#include "PID.h"
#include "robot-config.h" //instantiate motors
//not using anything in PID file, you don't need to care about this
namespace PID1{
  double kp,ki,kd;
  double p,i,d;

  double error;
  double prevError;
  double totalError; //not necesssarily needed right now since we're not using integral

  double circumference;
  double target;

  bool enabled;
  double powerValue;
  double averageDistance;

  void PIDOn(double tgt);
  void PID(void);
}

void PID1::PIDOn(double tgt){
  PID1::target = tgt;
  PID1::enabled = true;
}

double degPerInch =(4.25 * M_PI) / 360.0;

extern void PID1::PID(){
  voltageUnits voltUnit = volt;

  //to tune kp i suggest starting with 1.0 and working from there, you are looking for the robot to move forward past the target
  //and then to move back and stop directly on top of the target, when tuning i suggest moving 48inches (2 tiles) and lining
  //the back of your wheels with the edge of a tile (not the edge of the field)
  //if the root is constantly going back and forth aggressively then the kp is to high
  //if the robot isnt making it too or past the target then the kp is to low

  //tuning kd you are looking for the robt to stop directly where you want it to
  //to tune kd start with 1 and go from there
  //if the robot isnt making it far enough then its to high
  //if the robot is going too far then its too low

  PID1::kp = 1.0;
  kd = 0;
  
  
  // LFront.setBrake(hold);
  // LBack.setBrake(hold);
  // RFront.setBrake(hold);
  // RBack.setBrake(hold);

  /*
  LFront.setBrake(coast);
  LBack.setBrake(coast);
  RFront.setBrake(coast);
  RBack.setBrake(coast);
  */

  while(true){
   
    // LEnc.setRotation(0, deg);
    // REnc.setRotation(0, deg);

  while(PID1::enabled){
    
    //averageDistance = (((-1 * LEnc.rotation(deg)/2) + (-1 * REnc.rotation(deg)/2))/2)*degPerInch;
    error = target - averageDistance;
    p = kp*error;
    d = kd * (error-prevError);
    powerValue = p + d;
  

  //cap
    if(powerValue > 9){
      powerValue = 9;
    }
    if(powerValue < -9){
      powerValue = -9;
    }

    if(abs(error) < 0.1 && abs(powerValue) < 0.5){//power 0.75 before, try later and if it's bad, change it back
      //leftWheel.stop(brake);
      //rightWheel.stop(brake);
      enabled = false;
    } //else if((LEnc.velocity(dps)+REnc.velocity(dps))/2 < 180){

    //}
    
    else{
      //leftWheel.spin(fwd, powerValue, voltUnit);
      //rightWheel.spin(fwd, powerValue, voltUnit);
    }
    
    wait(10, msec);
    prevError = error;


  }
  
  PID1::error = 0.0;
  PID1::totalError = 0.0;
  PID1::powerValue = 0.0;
  PID1::target = 0.0;
  }
}