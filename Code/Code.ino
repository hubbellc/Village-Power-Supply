// Tyler La-Brie and Caleb Hubbell

// We will make use of the servo control library to set the speed of the motors
#include <Servo.h> 

//STATES
int currentState = 1;

int DAWN_STATE = 1;
int MORNING_STATE = 2;
int AFTERNOON_STATE = 3;
int EVENING_STATE = 4;
int NIGHT_STATE = 5;

int DAWN_CORRECT_STATE = 6;
int MORNING_CORRECT_STATE = 7;
int AFTERNOON_CORRECT_STATE = 8;
int EVENING_CORRECT_STATE = 9;
int NIGHT_CORRECT_STATE = 10;

//Set up the State Change Button
int STATE_CHANGE_BUTTON = A7;
int stateButtonVal = LOW;
int lastChangeButtonState = LOW;
int stateButtonState = LOW;

//Set up the Correction Button
int CORRECTION_BUTTON = A6;
int correctionButtonVal = LOW;
int lastCorrectionButtonState = LOW;
int correctionButtonState = LOW;

//Debounce Variables
long lastDebounce;
long debounceDelay = 50;

Servo myservo; 

void arm(){
 // arm the speed controller, modify as necessary for your ESC  
 setSpeed(0); 
 delay(1000); //delay 1 second,  some speed controllers may need longer
}

void setSpeed(int speed){
 // speed is from 0 to 100 where 0 is off and 100 is maximum speed
 // the following maps speed values of 0-100 to angles from 0-180,
 // some speed controllers may need different values, see the ESC instructions
 //int angle = map(speed, 0, 100, 0, 180);
 //myservo.write(angle);    

// Servo controls use pulse widths to set the angle from 0 to 180 degrees
// Maps speed values of 0-100 to pulse widths of 1000 uS to 2000 uS
 
 int pulse_width = map(speed, 0, 100, 1000, 2000);
 myservo.writeMicroseconds(pulse_width);
}

// Give the 8 channel relays a name, and match them with the Arduino pins
int Relay8 = 45;
int Relay7 = 43;
int Relay6 = 41;
int Relay5 = 39;
int Relay4 = 37;
int Relay3 = 35;
int Relay2 = 33;
int Relay1 = 31; 

int Relay9 = 44;
int Relay10 = 42;
int Relay11 = 40;
int Relay12 = 38;
int Relay13 = 36;
int Relay14 = 34;
int Relay15 = 32;
int Relay16 = 30;


void setup()
{
  Serial.begin(115200);
  
 // Tell the Arduino our relay pins are outputs
 pinMode(Relay1, OUTPUT);
 pinMode(Relay2, OUTPUT);
 pinMode(Relay3, OUTPUT);
 pinMode(Relay4, OUTPUT);
 pinMode(Relay5, OUTPUT);
 pinMode(Relay6, OUTPUT);
 pinMode(Relay7, OUTPUT);
 pinMode(Relay8, OUTPUT);

 pinMode(Relay9, OUTPUT);
 pinMode(Relay10, OUTPUT);
 pinMode(Relay11, OUTPUT);
 pinMode(Relay12, OUTPUT);
 pinMode(Relay13, OUTPUT);
 pinMode(Relay14, OUTPUT);
 pinMode(Relay15, OUTPUT);
 pinMode(Relay16, OUTPUT);
 
 pinMode(STATE_CHANGE_BUTTON, INPUT);
 pinMode(CORRECTION_BUTTON, INPUT);
 
 // Setting up pin 9 for the motor control and arm the controller
 myservo.attach(9); // PWM Pin 9
 arm();  

 // Relay Pins are Active LOW
 // Set the pins to HIGH to start in the OFF position
 digitalWrite(Relay1, HIGH);
 digitalWrite(Relay2, HIGH);
 digitalWrite(Relay3, HIGH);
 digitalWrite(Relay4, HIGH);
 digitalWrite(Relay5, HIGH);
 digitalWrite(Relay6, HIGH);
 digitalWrite(Relay7, HIGH);
 digitalWrite(Relay8, HIGH);

 digitalWrite(Relay9, HIGH);
 digitalWrite(Relay10, HIGH);
 digitalWrite(Relay11, HIGH);
 digitalWrite(Relay12, HIGH);
 digitalWrite(Relay13, HIGH);
 digitalWrite(Relay14, HIGH);
 digitalWrite(Relay15, HIGH);
 digitalWrite(Relay16, HIGH);

 // Start yo engines
 setSpeed(36);
}

// Main loop for running the motor
void loop()
{
// Relay Pins are Active LOW
 // Set the pins to HIGH to start in the OFF position
// digitalWrite(Relay1, LOW);
// digitalWrite(Relay2, LOW);
// digitalWrite(Relay3, LOW);
// digitalWrite(Relay4, LOW);
// digitalWrite(Relay5, LOW);
// digitalWrite(Relay6, LOW);
// digitalWrite(Relay7, LOW);
// digitalWrite(Relay8, LOW);
//
// digitalWrite(Relay9, LOW);
// digitalWrite(Relay10, LOW);
// digitalWrite(Relay11, LOW);
// digitalWrite(Relay12, LOW);
// digitalWrite(Relay13, LOW);
// digitalWrite(Relay14, LOW);
// digitalWrite(Relay15, LOW);
// digitalWrite(Relay16, LOW);
 setSpeed(36);

  // read both buttons
  int stateButtonVal = digitalRead(STATE_CHANGE_BUTTON);
  int correctionButtonVal = digitalRead(CORRECTION_BUTTON);

  if (stateButtonVal != lastChangeButtonState) 
  {
    // reset the debouncing timer
//    Serial.println("bad button");
    lastDebounce = millis();
  }
  
  if (correctionButtonVal != lastCorrectionButtonState) 
  {
    // reset the debouncing timer
    Serial.println("bad button");
    lastDebounce = millis();
  }

 //State Changing input checker
 if((millis() - lastDebounce) > debounceDelay)//Start of Debounce Delay If Loop
 {
  Serial.println("button change");
  Serial.println(stateButtonVal);

  if(stateButtonVal != stateButtonState)//Start of Button Change If Loop
  {
    // reset
    stateButtonState = stateButtonVal;
    lastChangeButtonState = stateButtonVal;
    
    // turn off relays
   digitalWrite(Relay1, HIGH);
   digitalWrite(Relay2, HIGH);
   digitalWrite(Relay3, HIGH);
   digitalWrite(Relay4, HIGH);
   digitalWrite(Relay5, HIGH);
   digitalWrite(Relay6, HIGH);
   digitalWrite(Relay7, HIGH);
   digitalWrite(Relay8, HIGH);
  
   digitalWrite(Relay9, HIGH);
   digitalWrite(Relay10, HIGH);
   digitalWrite(Relay11, HIGH);
   digitalWrite(Relay12, HIGH);
   digitalWrite(Relay13, HIGH);
   digitalWrite(Relay14, HIGH);
   digitalWrite(Relay15, HIGH);
   digitalWrite(Relay16, HIGH);
    
    //change state
    if (currentState < 5)
    {
      currentState++;
    }
    else if (currentState == 5)
    {
      currentState = 1;
    }
    
    lastDebounce = millis();
  }// End of Button Press If Loop

  //Power Factor Correction Button
  else if(correctionButtonVal != correctionButtonState)
  {
    // reset
    correctionButtonState = correctionButtonVal;
    lastCorrectionButtonState = correctionButtonVal;
    
    // go to corrected state
    if ((currentState + 5) < 11)
    {
      currentState = currentState + 5;
    }
    // go back to uncorrected
    else
    {
       // turn off all relays
       digitalWrite(Relay1, HIGH);
       digitalWrite(Relay2, HIGH);
       digitalWrite(Relay3, HIGH);
       digitalWrite(Relay4, HIGH);
       digitalWrite(Relay5, HIGH);
       digitalWrite(Relay6, HIGH);
       digitalWrite(Relay7, HIGH);
       digitalWrite(Relay8, HIGH);
      
       digitalWrite(Relay9, HIGH);
       digitalWrite(Relay10, HIGH);
       digitalWrite(Relay11, HIGH);
       digitalWrite(Relay12, HIGH);
       digitalWrite(Relay13, HIGH);
       digitalWrite(Relay14, HIGH);
       digitalWrite(Relay15, HIGH);
       digitalWrite(Relay16, HIGH);

       // go back to normal
       currentState = currentState - 5;
    }

    lastDebounce = millis();
  }//End of Power Factor Correction Button
 }//End of Debounce If Loop

 //Testing/Idle state
 if(currentState == 0)
 {
   /*// Switch each Relay ON and OFF to verify operation
   digitalWrite(Relay8, LOW);
   delay(500); // delay half-second between transitions
   digitalWrite(Relay8, HIGH);
   delay(500);
   digitalWrite(Relay7, LOW);
   delay(500);
   digitalWrite(Relay7, HIGH);
   delay(500);
   digitalWrite(Relay6, LOW);
   delay(500);
   digitalWrite(Relay6, HIGH);
   delay(500);
   digitalWrite(Relay5, LOW);
   delay(500);
   digitalWrite(Relay5, HIGH);
   delay(500); 
   digitalWrite(Relay4, LOW);
   delay(500);
   digitalWrite(Relay4, HIGH);
   delay(500); 
   digitalWrite(Relay3, LOW);
   delay(500);
   digitalWrite(Relay3, HIGH);
   delay(500);
   digitalWrite(Relay2, LOW);
   delay(500);
   digitalWrite(Relay2, HIGH);
   delay(500);
   digitalWrite(Relay1, LOW);
   delay(500);
   digitalWrite(Relay1 , HIGH);
   delay(500);
  
   digitalWrite(Relay16, LOW);
   delay(500);
   digitalWrite(Relay16, HIGH);
   delay(500);
   digitalWrite(Relay15, LOW);
   delay(500);
   digitalWrite(Relay15, HIGH);
   delay(500);
   digitalWrite(Relay14, LOW);
   delay(500);
   digitalWrite(Relay14, HIGH);
   delay(500);
   digitalWrite(Relay13, LOW);
   delay(500);
   digitalWrite(Relay13, HIGH);
   delay(500); 
   digitalWrite(Relay12, LOW);
   delay(500);
   digitalWrite(Relay12, HIGH);
   delay(500);
   digitalWrite(Relay11, LOW);
   delay(500);
   digitalWrite(Relay11, HIGH);
   delay(500);
   digitalWrite(Relay10, LOW);
   delay(500);
   digitalWrite(Relay10, HIGH);
   delay(500);
   digitalWrite(Relay9, LOW);
   delay(500);
   digitalWrite(Relay9 , HIGH);
   delay(500);*/

   // wait patiently
 }

 //DAWN
 else if (currentState == 1)
 {
  // relay stuff
  digitalWrite(Relay9, LOW);
  digitalWrite(Relay5, LOW);
  digitalWrite(Relay1, LOW);
  
 }

 //MORNING
 else if (currentState == 2)
 {
  // relay stuff
  digitalWrite(Relay10, LOW);
  digitalWrite(Relay6, LOW);
  digitalWrite(Relay2, LOW);
  
 }

 //AFTERNOON
 else if (currentState == 3)
 {
  //Everything off  
 }

 //EVENING
 else if (currentState == 4)
 {
  // relay stuff
  digitalWrite(Relay11, LOW);
  digitalWrite(Relay7, LOW);
  digitalWrite(Relay3, LOW);
 }

 //NIGHT
 else if (currentState == 5)
 {
  // relay stuff
  digitalWrite(Relay12, LOW);
  digitalWrite(Relay7, LOW);
  digitalWrite(Relay4, LOW);
 }

 //DAWN CORRECT
 else if (currentState == 6)
 {
  // turn on ONLY relays that correct
  
 }

 //MORNING CORRECT
 else if (currentState == 7)
 {
   // turn on ONLY relays that correct
  
 }

 //Skip the correcting state for afternoon (8)

 //EVENING CORRECT
 else if (currentState == 9)
 {
   // turn on ONLY relays that correct
  
 }

 //NIGHT CORRECT
 else if (currentState == 10)
 {
   // turn on ONLY relays that correct
  
 }


// The code in the comment block below gives an idea of
// how a sweep from min to max or max to min could be
// done across the range of motor speeds
 /*
 // sweep up to half speed
 for(speed = 0; speed < 50; speed += 5) {
   setSpeed(speed);
   delay(1000);
 }
 // sweep back down to 0 speed.
 for(speed = 45; speed > 0; speed -= 5) {
   setSpeed(speed);
   delay(1000);
 }
 setSpeed(0);  
 delay(3000); // stop the motor for 3 seconds*/

} // end of main loop
