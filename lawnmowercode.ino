//Motor A
int enAPin1 = D8;
int motorPinA1 = D3;
int motorPinA2 = D2;

//Motor B
int enBPin2 = D16;
int motorPinB3 = D15;
int motorPinB4 = D13;


void setup() {

    Particle.function("Control", btnMovement);
    //setup Motor A and Motor B
    pinMode(enAPin1, OUTPUT);
    pinMode(enBPin2, OUTPUT);
    pinMode(motorPinA1, OUTPUT);
    pinMode(motorPinA2, OUTPUT);
    pinMode(motorPinB3, OUTPUT);
    pinMode(motorPinB4, OUTPUT);
    digitalWrite(enAPin1, 0);
    digitalWrite(enBPin2, 0);
}

void loop() {

    
}


int btnMovement(String command) {
    if (command == "start")
    {
        digitalWrite(enAPin1, 255);
        digitalWrite(enBPin2, 255);
        digitalWrite(motorPinA1, HIGH); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, HIGH); 
        digitalWrite(motorPinB4, LOW); 
        return 1;
    }
     else if (command == "stop")
    {
        digitalWrite(enAPin1, 0);
        digitalWrite(enBPin2, 0);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, LOW); 
        return 1;
    }
    return 0;
}
