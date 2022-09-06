//Declaring pins that will be used for Motor A
int enAPin1 = D8;
int motorPinA1 = D3;
int motorPinA2 = D2;

//Declaring pins that will be used for Motor b
int enBPin2 = D16;
int motorPinB3 = D15;
int motorPinB4 = D13;

void setup() {
    //Subscribing to event that is being pushed to the cloud
    Particle.subscribe("botstatus",btnMovement,MY_DEVICES);

    //Setup Motor A and Motor B declaring their pin mode
    pinMode(enAPin1, OUTPUT);
    pinMode(enBPin2, OUTPUT);
    pinMode(motorPinA1, OUTPUT);
    pinMode(motorPinA2, OUTPUT);
    pinMode(motorPinB3, OUTPUT);
    pinMode(motorPinB4, OUTPUT);
    digitalWrite(enAPin1, 0);
    digitalWrite(enBPin2, 0);
}

void loop() {}

//This is the event handler for "botstatus" event and the data it receives
void btnMovement(const char event, const char *data)
{   
    //If "startbot" is received as input then turn both motors on so robot can move
    if (strcmp (data,"startbot") == 0)
    {
        digitalWrite(enAPin1, 255);
        digitalWrite(enBPin2, 255);
        digitalWrite(motorPinA1, HIGH); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, HIGH); 
        digitalWrite(motorPinB4, LOW); 
    }
    //If "stopbot" is received as input then turn both motors off so robot can stop
    if (strcmp (data,"stopbot") == 0)
    {
        digitalWrite(enAPin1, 0);
        digitalWrite(enBPin2, 0);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, LOW); 
    }
}
