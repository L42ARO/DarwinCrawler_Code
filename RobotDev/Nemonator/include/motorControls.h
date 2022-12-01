#ifndef MOTOR_CONTROLS_H
#define MOTOR_CONTROLS_H

#define lMotor 13 //enA
#define lMotorFwd 25 //in1
#define lMotorRev 26 //in2
#define rMotor 12
#define rMotorFwd 27
#define rMotorRev 14
#define rMax 255
#define lMax 200

void MotorSetup();
void moveMotor(int dir, double vel, char side);

#endif