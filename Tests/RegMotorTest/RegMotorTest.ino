#define enA 9
#define rB 8
#define rF 7
#define enB 11
#define lB 12
#define lF 13

void setup() {
    pinMode(enA, OUTPUT);
    pinMode(rF, OUTPUT);
    pinMode(rB, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(lF, OUTPUT);
    pinMode(lB, OUTPUT);

}

void loop() {
    moveMotor(1, 255, enA, rF, rB);
    moveMotor(1, 255, enB, lF, lB);
    delay(50);
}

void moveMotor(int dir, int vel, int pwa, int in1, int in2){
    analogWrite(pwa, vel);
    if(dir == 1){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    }
    else if(dir == -1){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    }
}
