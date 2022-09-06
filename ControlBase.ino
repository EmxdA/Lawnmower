// This #include statement was automatically added by the Particle IDE.
#include <LiquidCrystal_I2C_Spark.h>

// Create lcd variable of the type of library to use its functions
LiquidCrystal_I2C *lcd;

//Declaring pins and variables
int onLED = D5;
int offLED = D6;
int stopBtn = D3;
int startBtn = D4;
int startButtonState = 0;
int stopButtonState = 0;
int status = 0;

void setup() {
    //Subscribing to event that is being pushed to the cloud
    Particle.subscribe("botstatus",webStatus,MY_DEVICES);
    
    //Setup buttons and LEDs
    pinMode(stopBtn, INPUT_PULLUP);
    pinMode(startBtn, INPUT_PULLUP);
    pinMode(onLED, OUTPUT);
    pinMode(offLED, OUTPUT);
    
    // Initialise 16x2 lcd with its i2c address and turn on backlight then clear screen
    lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    lcd->init();
    lcd->backlight();
    lcd->clear();
}

//This is the event handler for "botstatus" event and the data it receives
void webStatus(const char *event, const char *data) {
    //If "startbot" is received as input then change status to 1
    if (strcmp (data,"startbot") == 0)
    {
        status = 1;
    }
    //If "startbot" is received as input then change status to 0
    if (strcmp (data,"stopbot") == 0)
    {
        status = 0;
    }
}

void loop() {
    //Clear lcd and call functions to show time and status of bot
    lcd->clear();
    timer();
    printStatus();
    delay(1000);
    
    //Read the pin values of the buttons
    startButtonState = digitalRead(startBtn);
    stopButtonState = digitalRead(stopBtn);
    
    //If start button is pressed publish "botstatus" event and the data "startbot" to the cloud
    if (startButtonState == HIGH){
        status = 1;
        Particle.publish("botstatus","startbot");
    }
    //If stop button is pressed publish "botstatus" event and the data "stopbot" to the cloud
    else if (stopButtonState == HIGH){
        status = 0;
        Particle.publish("botstatus","stopbot");
    }
}

//This function prints the time on lcd screen
void timer(){
    //clear lcd and set writing position to top of screen
    lcd->setCursor(1,0);
    //print the time with the hour, minute and seconds
    lcd->print(Time.hour() < 10? "   0" : "    ");
    lcd->print(Time.hour());
    lcd->print(Time.minute() < 10? ":0": ":");
    lcd->print(Time.minute());
    lcd->print(Time.second()< 10? ":0": ":");
    lcd->print(Time.second());

}

//This function pritns the bot status on lcd screen
void printStatus(){
    //If the status is 1 then add the active text to lcd and turn green LED on
    if (status == 1)
    {
        lcd->setCursor(2,1);
        lcd->print("Bot---Active");
        digitalWrite(onLED, HIGH);
        digitalWrite(offLED, LOW);
    }
    //If the status is 0 then add the inactive text to lcd and turn red LED on
    else if (status == 0){
        lcd->setCursor(2,1);
        lcd->print("Bot-Inactive");
        digitalWrite(offLED, HIGH);
        digitalWrite(onLED, LOW);
    }
}
