    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Particle.variable("dist", cm);
    //setup Motor A and Motor B
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(enAPin1, OUTPUT);
	pinMode(enBPin2, OUTPUT);
	pinMode(motorPinA1, OUTPUT);
	pinMode(motorPinA2, OUTPUT);
	pinMode(motorPinB3, OUTPUT);
	pinMode(motorPinB4, OUTPUT);
	digitalWrite(enAPin1, 0);
    digitalWrite(enBPin2, 0);
    
	Particle.subscribe("startmovement", StartAlarm);
}

void loop() {
    buttonState = digitalRead(buttonPin);
    Stopping();
}


void StartAlarm(const char *event, const char *data)
{
    if (strcmp(data, "alarmBot") == 0)
    {
        while (stop == false)
        {
            cm = rangefinder.getDistanceCM();
            buttonState = digitalRead(buttonPin);
            if(buttonState == LOW)
            {
                Particle.publish("startmovement", "endAlarm");
                stop = true;
            }
            if (cm > 25)
            {
                Accelerate();
            }
            if (cm <= 25)
            {
                ChangeDirection();
            }
        }
    }
    
}
void Stopping(){
    digitalWrite(enAPin1, 0);
    digitalWrite(enBPin2, 0);
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, LOW); 
    digitalWrite(motorPinB3, LOW); 
    digitalWrite(motorPinB4, LOW); 
    delay(1000);
}

void Accelerate() {
    digitalWrite(enAPin1, 75);
    digitalWrite(enBPin2, 75);
    digitalWrite(motorPinA1, LOW); 
    digitalWrite(motorPinA2, HIGH); 
    digitalWrite(motorPinB3, HIGH); 
    digitalWrite(motorPinB4, LOW); 
    delay(100);
}

void ChangeDirection() {
    int direction = rand()% 3+0;
    
    if (direction == 1)
   {
        digitalWrite(enAPin1, 75);
        digitalWrite(enBPin2, 75);
        digitalWrite(motorPinA1, HIGH); 
        digitalWrite(motorPinA2, LOW); 
        digitalWrite(motorPinB3, HIGH); 
        digitalWrite(motorPinB4, LOW); 
        delay(100);
    }
    else
    {
        digitalWrite(enAPin1, 75);
        digitalWrite(enBPin2, 75);
        digitalWrite(motorPinA1, LOW); 
        digitalWrite(motorPinA2, HIGH); 
        digitalWrite(motorPinB3, LOW); 
        digitalWrite(motorPinB4, HIGH); 
        delay(100);
    }
}
