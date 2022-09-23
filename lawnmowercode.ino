// This #include statement was automatically added by the Particle IDE.
#include <HC_SR04.h>

//Motor A
int enAPin1 = D8;
int motorPinA1 = D3;
int motorPinA2 = D2;

//Motor B
int enBPin2 = D16;
int motorPinB3 = D15;
int motorPinB4 = D13;

void setup() {
    //Subscribing to event that is being pushed to the cloud
    Particle.subscribe("botstatus",btnMovement,MY_DEVICES);
    //Sending gui function to cloud
    Particle.function("guimovement", guiMovement);

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

//This is the event handler for "botstatus" event and the data it receives
void btnMovement(const char *event, const char *data)
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

void loop() {

}

//Below are the directional movement functions for the rover
int guiMovement(String data)
{
    if (strcmp (data,"Forward") == 0)
    {
         //This allows the rover to move forward
        digitalWrite(enAPin1, 255);
        digitalWrite(enBPin2, 255);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, HIGH); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, HIGH);
        delay(1250);
    }
    else if (strcmp (data,"Backward") == 0)
    {
        
        //This allows the rover to move backward
        digitalWrite(enAPin1, 255);
        digitalWrite(enBPin2, 255);
        digitalWrite(motorPinA1, HIGH); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, HIGH); 
        digitalWrite(motorPinB4, LOW);
        delay(1250);
    }
    else if (strcmp (data,"Left") == 0)
    {
        //This allows the rover to turn left
        digitalWrite(enAPin1, 255);
        digitalWrite(enBPin2, 255);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, HIGH); 
        digitalWrite(motorPinB3, HIGH); 
        digitalWrite(motorPinB4, LOW);
        delay(500);
    }
    else if (strcmp (data,"Right") == 0)
    {   
        //This allows the rover to turn right
        digitalWrite(enAPin1, 255);
        digitalWrite(enBPin2, 255);
        digitalWrite(motorPinA1, HIGH); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, HIGH);
        delay(500);
    }
    else if (strcmp (data,"Stop") == 0)
    {
        // This stops the rover
        digitalWrite(enAPin1, 0);
        digitalWrite(enBPin2, 0);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, LOW);
    }
    else if (strcmp (data,"Start") == 0)
    {
        //This starts the rover
        digitalWrite(enAPin1, 255);
        digitalWrite(enBPin2, 255);
        digitalWrite(motorPinA1, HIGH); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, HIGH); 
        digitalWrite(motorPinB4, LOW);
    }
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, LOW);
        
    return 1;
}
