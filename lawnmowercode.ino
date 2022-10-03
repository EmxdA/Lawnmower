// This #include statement was automatically added by the Particle IDE.
#include <HC_SR04.h>

//IR sensors
#define IRSensorLeft    D1
#define IRSensorRight   D9

//Ultrasonic sensors
#define  trigPin      D10
#define  echoPin      D11

//Motor A
int enAPin1 = D8;
int motorPinA1 = D3;
int motorPinA2 = D2;

//Motor B
int enBPin2 = D16;
int motorPinB3 = D15;
int motorPinB4 = D13;
int cm , leftDist, rightDist;

int enBPinBlade = D12;
int bladeMotor = D5;

int status = 0;

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);

void setup() 
{
    //Subscribing to event that is being pushed to the cloud
    Particle.subscribe("botstatus",btnMovement,MY_DEVICES);
    //Sending gui function to cloud
    Particle.function("guimovement", guiMovement);

    //Setup Motor A and Motor B declaring their pin mode
    pinMode(IRSensorLeft, INPUT);
    pinMode(IRSensorRight, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(enAPin1, OUTPUT);
	pinMode(enBPin2, OUTPUT);
	pinMode(enBPinBlade, OUTPUT);
	pinMode(bladeMotor, OUTPUT);
	pinMode(motorPinA1, OUTPUT);
	pinMode(motorPinA2, OUTPUT);
	pinMode(motorPinB3, OUTPUT);
	pinMode(motorPinB4, OUTPUT);
	digitalWrite(enAPin1, 0);
    digitalWrite(enBPin2, 0);
    digitalWrite(enBPinBlade, 0);
}

//This is the event handler for "botstatus" event and the data it receives
void btnMovement(const char *event, const char *data)
{
    //If "startbot" is received as input then turn both motors on so robot can move
    if (strcmp (data,"startbot") == 0)
    {
        status = 1;
    }
    //If "stopbot" is received as input then turn both motors off so robot can stop
    if (strcmp (data,"stopbot") == 0)
    {
        digitalWrite(enAPin1, 0);
        digitalWrite(enBPin2, 0);
        digitalWrite(enBPinBlade, 0);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, LOW); 
        status = 0;
    }
}

void loop() {
    if (status == 1){
        automatedMowing();
    }
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
        turnLeft();
    }
    else if (strcmp (data,"Right") == 0)
    {   
        //This allows the rover to turn right
        turnRight();
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
        automatedMowing();
    }
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, LOW);
        
    return 1;
}


void automatedMowing(){
    cm = rangefinder.getDistanceCM();
    int statusSensorLeft = digitalRead(IRSensorLeft);
    int statusSensorRight = digitalRead(IRSensorRight);
    
    digitalWrite(enBPinBlade, 185);
    digitalWrite(bladeMotor, HIGH);
    
    digitalWrite(enAPin1, 185);
    digitalWrite(enBPin2, 185);
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, HIGH); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, HIGH);
    
    
    if (statusSensorLeft == LOW){
        turnRight();
    }
    
    if (statusSensorRight == LOW){
        turnLeft();
    }
    
    if (cm > 20){
        digitalWrite(enAPin1, 185);
        digitalWrite(enBPin2, 185);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, HIGH); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, HIGH);
    }
    else if (cm < 20){ 
       
        changeDirection();
    }
    
    
}

void changeDirection(){
    
    Particle.publish("motion detected");
     
    digitalWrite(enAPin1, 100);
    digitalWrite(enBPin2, 100);
    digitalWrite(motorPinA1, HIGH); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, HIGH);
    delay(300);
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, LOW);
    leftDist = rangefinder.getDistanceCM();
    delay(1000);
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, HIGH); 
    digitalWrite(motorPinB3, HIGH); 
    digitalWrite(motorPinB4, LOW);
    delay(600);
    rightDist = rangefinder.getDistanceCM();
    delay(1000);
    digitalWrite(motorPinA1, HIGH); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, HIGH);
    delay(300);
    
    if (rightDist > leftDist)
    {
        turnRight();
    }
    else {
        turnLeft();
    }
}


void turnRight(){
    digitalWrite(enAPin1, 255);
    digitalWrite(enBPin2, 255);
    digitalWrite(motorPinA1, HIGH); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, HIGH);
    delay(1000);
}

void turnLeft(){
    delay(1000);
    digitalWrite(enAPin1, 255);
    digitalWrite(enBPin2, 255);
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, HIGH); 
    digitalWrite(motorPinB3, HIGH); 
    digitalWrite(motorPinB4, LOW);
    delay(1000);
}

