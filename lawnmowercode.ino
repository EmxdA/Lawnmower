// This #include statement was automatically added by the Particle IDE.
#include <HC_SR04.h>

//IR sensors
#define IRSensorLeft    D1
#define IRSensorRight   D9

//Ultrasonic pins
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

//Distance variables
int cm , leftDist, rightDist;

//Blade motor
int enBPinBlade = D12;
int bladeMotor = D5;

//Initiating status variable for bot
int status = 0;

//Initialising ultrasonic pins
HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);

void setup() 
{
    //Subscribing to event that is being pushed to the cloud
    Particle.subscribe("botstatus",btnMovement,MY_DEVICES);
    //Sending gui function to cloud
    Particle.function("guimovement", guiMovement);

    //Setup Motor A, Motor B, Blade motor and declaring their pin mode
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
    //If "startbot" is received as input then turn both motors and blade on so robot can move
    if (strcmp (data,"startbot") == 0)
    {
        status = 1;
    }
    //If "stopbot" is received as input then turn both motors and blade off so robot can stop
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
    //If the status is 1 then call the mowing function
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
        digitalWrite(enBPinBlade, 0);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, LOW); 
        status = 0;
    }
    else if (strcmp (data,"Start") == 0)
    {
        //This starts the rover
	status = 1;
    }
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, LOW);
        
    return 1;
}

//This function moves the rover automatically and has object avoidance and boundary detection
void automatedMowing(){
    //Initialising varaiables
    cm = rangefinder.getDistanceCM();
    int statusSensorLeft = digitalRead(IRSensorLeft);
    int statusSensorRight = digitalRead(IRSensorRight);
    
    //Initiating blade
    digitalWrite(enBPinBlade, 185);
    digitalWrite(bladeMotor, HIGH);
    
    //Moving rover
    digitalWrite(enAPin1, 185);
    digitalWrite(enBPin2, 185);
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, HIGH); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, HIGH);
    
    //Changing direction based on IR sensor detection
    if (statusSensorLeft == LOW){
        turnRight();
    }
    
    if (statusSensorRight == LOW){
        turnLeft();
    }
    
    //If nothing is withing 20cm of the rover keep it moving
    if (cm > 20){
        digitalWrite(enAPin1, 185);
        digitalWrite(enBPin2, 185);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, HIGH); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, HIGH);
    }
    //If something is within 20cm then change the direction of the rover
    else if (cm < 20){ 
       
        changeDirection();
    }
    
    
}

//This function checks the left and right of the rover and moves in the direction where there is nothing
void changeDirection(){
    
    //Publishing an event
    Particle.publish("motion detected");
     
    //Turns left and right and records the distance
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
    
    //Compares the left and right distance and moves in the direction with the greater value
    if (rightDist > leftDist)
    {
        turnRight();
    }
    else {
        turnLeft();
    }
}

//This function turns the rover right
void turnRight(){
    digitalWrite(enAPin1, 255);
    digitalWrite(enBPin2, 255);
    digitalWrite(motorPinA1, HIGH); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, HIGH);
    delay(1000);
}

//This function turns the rover left
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

