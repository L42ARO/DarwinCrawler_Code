#include "motorControls.h"
#include "Arduino.h"


void MotorSetup(){
    pinMode(rMotor, OUTPUT);
    pinMode(rMotorFwd, OUTPUT);
    pinMode(rMotorRev, OUTPUT);
    pinMode(lMotor, OUTPUT);
    pinMode(lMotorFwd, OUTPUT);
    pinMode(lMotorRev, OUTPUT);
}

void moveMotor(int dir, double vel, char side){
    int actualVel;
    if(side == 'l'){
        actualVel = int(lMax * vel);
        if(dir == 1){
            analogWrite(lMotor, actualVel);
            digitalWrite(lMotorFwd, HIGH);
            digitalWrite(lMotorRev, LOW);
        }
        else if(dir == -1){
            analogWrite(lMotor, actualVel);
            digitalWrite(lMotorFwd, LOW);
            digitalWrite(lMotorRev, HIGH);
        }
        else if(dir == 0){
            analogWrite(lMotor, 0);
            digitalWrite(lMotorFwd, LOW);
            digitalWrite(lMotorRev, LOW);
        }
    }
    else if(side == 'r'){
        actualVel = int(rMax * vel);
        if(dir == 1){
            analogWrite(rMotor, actualVel);
            digitalWrite(rMotorFwd, HIGH);
            digitalWrite(rMotorRev, LOW);
        }
        else if(dir == -1){
            analogWrite(rMotor, actualVel);
            digitalWrite(rMotorFwd, LOW);
            digitalWrite(rMotorRev, HIGH);
        }
        else if(dir == 0){
            analogWrite(rMotor, 0);
            digitalWrite(rMotorFwd, LOW);
            digitalWrite(rMotorRev, LOW);
        }
    }
}
