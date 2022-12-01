#include <PIDController.h>
volatile long int encoder_pos = 0;
PIDController pos_pid;
int motor_value = 255;

void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(2), encoder, RISING);
    pos_pid.begin();
    pos_pid.tune(15,0,2000);
    pos_pid.limit(-255,255);
}

void loop() {
    pos_pid.setpoint((int)(((float)analogRead(A0)/1023)*3740.0));
    motor_value = pos_pid.compute(encoder_pos);
    if(motor_value > 0){
        MotorCounterClockwise(motor_value);
    }
    else{
        MotorClockWise(abs(motor_value));
    }
    Serial.println(encoder_pos);
}

void encoder(){
    if(digitalRead(3) == HIGH){
        encoder_pos++;
    }
    else{
        encoder_pos--;
    }
}

void MotorClockWise(int power){
    if(power>100){
        analogWrite(9, power);
        analogWrite(10, LOW);
    }else{
        digitalWrite(0, LOW);
        digitalWrite(10, LOW);
    }
}

void MotorCounterClockwise(int power){
    if(power>100){
        analogWrite(10, power);
        analogWrite(9, LOW);
    }else{
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
    }
}