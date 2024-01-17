#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor MotorLeft = motor(PORT11, ratio18_1, false);

motor MotorRight = motor(PORT20, ratio18_1, false);

controller Controller1 = controller(primary);
motor MotorPickUp = motor(PORT17, ratio18_1, false);

motor MotorShoot = motor(PORT13, ratio18_1, false);

motor MotorExtend1 = motor(PORT18, ratio18_1, false);

motor MotorExtend2 = motor(PORT19, ratio18_1, false);




// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
#pragma endregion VEXcode Generated Robot Configuration

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;


void rotateRight(){
  MotorLeft.spin(reverse);
  MotorRight.spin(reverse);
}

void rotateLeft(){
  MotorLeft.spin(forward);
  MotorRight.spin(forward);
}

void moveForward(){
  MotorLeft.spin(reverse);
  MotorRight.spin(forward);
}

void moveBackward(){
  MotorLeft.spin(forward);
  MotorRight.spin(reverse);
}

void motorsStop(){
  MotorLeft.stop();
  MotorRight.stop();
}

void shoot(){
  MotorShoot.spin(forward);
  
  wait(1, seconds);

  wait(1, seconds);
  MotorShoot.stop();
}

void extend(){
  MotorExtend1.setVelocity(100, percent);
  MotorExtend2.setVelocity(10, percent);

  MotorExtend1.spin(forward);
  MotorExtend2.spin(forward);
  wait(2, seconds);
  MotorExtend2.stop();
  wait(5, seconds);
  MotorExtend1.stop();
}

void autonomousQ1(){
  moveForward();
  wait(750, msec);
  rotateRight();
  wait(450, msec);
  moveForward();
  wait(3000, msec);
  motorsStop();
}

bool shootingSet = false;

void shootSet(){
  shootingSet = !shootingSet;
}

int whenStarted1() {
  Controller1.ButtonR1.pressed(extend);
  Controller1.ButtonR2.pressed(shootSet);

  Controller1.ButtonUp.pressed(moveForward);
  Controller1.ButtonDown.pressed(moveBackward);
  Controller1.ButtonY.pressed(rotateLeft);
  Controller1.ButtonA.pressed(rotateRight);

  Controller1.ButtonUp.released(motorsStop);
  Controller1.ButtonDown.released(motorsStop);
  Controller1.ButtonY.released(motorsStop);
  Controller1.ButtonA.released(motorsStop);


  MotorLeft.setVelocity(50, percent);
  MotorRight.setVelocity(50, percent);
  MotorPickUp.setVelocity(50, percent);
  MotorShoot.setVelocity(100, percent);


  //autonomousQ1();

  /*
  rotateLeft();
  wait(1, seconds);
  rotateRight();
  wait(1, seconds);
  moveForward();
  wait(1, seconds);
  moveBackward();
  wait(1, seconds);*/

  while(true){
    if(shootingSet){
      MotorShoot.spin(forward);
    }else{
      MotorShoot.stop();
    }

    if(Controller1.ButtonL1.pressing()){
      MotorPickUp.spin(forward);
    }
    
    if(Controller1.ButtonL2.pressing()){
      MotorPickUp.spin(reverse);
    }

    if(!Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing()){
      MotorPickUp.stop();
    }

    

    vex::task::sleep(25);

    /*
    if(Controller1.ButtonUp.pressing()){
      MotorLeft.spin(reverse);
    }

    if(Controller1.ButtonDown.pressing()){
      MotorLeft.spin(forward);
    }

    if(!Controller1.ButtonUp.pressing() && !Controller1.ButtonDown.pressing()){
      MotorLeft.stop();
    }

    if(Controller1.ButtonX.pressing()){
      //MotorRight.setVelocity(50, percent);
      MotorRight.spin(forward);
    }

    if(Controller1.ButtonB.pressing()){
      //MotorRight.setVelocity(50, percent);
      MotorRight.spin(reverse);
    }

    if(!Controller1.ButtonX.pressing() && !Controller1.ButtonB.pressing()){
      MotorRight.stop();
    }*/
  }
  
}


int main() {

  printf("\033[30m");
  Brain.Screen.print("VEXcode");


  // wait for rotation sensor to fully initialize
  wait(30, msec);

  whenStarted1();
}
