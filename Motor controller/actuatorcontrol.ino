#include <Arduino.h>


// Motor controller pins for four actuators
const int motorPins[8] = {33, 32, 19, 21, 25, 26, 27, 14};

// Joystick pins
const int joyX = 2; // X-axis connected to D2
const int joyY = 4; // Y-axis connected to D4
const int joyButton = 15; // Button pin

// Counter for actuator position
int actuatorCounter[4] = {0, 0, 0, 0}; // Four counters for four actuators
const int counterMin = 0;  // Adjust these based on your tests
const int counterMax = 40;  // Estimate this value through experimentation 150 full range

bool middle[4] = {false,false,false,false};
void setup() {
  // Initialize motor pins 1-8 as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(motorPins[i], OUTPUT); 
  }

  // Initialize the joystick pins
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(joyButton, INPUT_PULLUP);
  // Start serial communication for debugging purposes
  Serial.begin(9600);
}

void loop() {

  // Read joystick X-axis value
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int buttonState = digitalRead(joyButton);
actuator1(xValue);
actuator2(yValue);
actuator3(xValue);
actuator4(yValue);


if (buttonState == LOW) {
 // Check if the button is pressed
    // Reverse motors for 7 seconds
    reverseMotors();
    delay(7000);
    actuatorCounter[0]=0;
    actuatorCounter[1]=0;
    actuatorCounter[2]=0;
    actuatorCounter[3]=0;
    // Extend actuators until they reach counterMax
    extendActuators();
  }

   // digitalWrite(motorPins[0], LOW);
    //digitalWrite(motorPins[1], HIGH);
   // digitalWrite(motorPins[2], LOW);
   // digitalWrite(motorPins[3], HIGH);
   // digitalWrite(motorPins[4], LOW);
   // digitalWrite(motorPins[5], HIGH);
   // digitalWrite(motorPins[6], LOW);
   // digitalWrite(motorPins[7], HIGH);
   // for (int i = 0; i < 4; i++) {
   //   if (actuatorCounter[i] > 0){
   // actuatorCounter[i]--;
   //   }
  //}
 // delay(7000);

  //  digitalWrite(motorPins[1], LOW);
   // digitalWrite(motorPins[0], HIGH);
   // digitalWrite(motorPins[3], LOW);
   // digitalWrite(motorPins[2], HIGH);
  //  digitalWrite(motorPins[5], LOW);
  //  digitalWrite(motorPins[4], HIGH);
  //  digitalWrite(motorPins[7], LOW);
  //  digitalWrite(motorPins[6], HIGH);

//for (int i = 0; i < 4; i++) {
//if(actuatorCounter[i] > counterMax/2)

  
 //  while(!allTrue(middle)){
  //for (int j = 0; j < 4; j++){
   //     if(actuatorCounter[j] > counterMax/2){
   // digitalWrite(motorPins[j*2], LOW);
   // digitalWrite(motorPins[j*2+1], LOW);
   // middle[j]=true;
        //}
  //}
  //}
//}



  // Print the current joystick values and actuator counters to the Serial Monitor
  Serial.print("Joystick X Value: ");
  Serial.print(xValue);
  Serial.print(", Joystick Y Value: ");
  Serial.print(yValue);
  for (int i = 0; i < 4; i++) {
    Serial.print(", Actuator ");
    Serial.print(i + 1);
    Serial.print(" Counter: ");
    Serial.println(actuatorCounter[i]);
  }

  delay(100); // Small delay to prevent reading noise from the joystick
}

void actuator1(int xValue) {
//standby
  if (xValue < 3800 && xValue > 200) {
    digitalWrite(motorPins[0], LOW); 
    digitalWrite(motorPins[1], LOW);
  }
//Forward
 else if ( xValue > 1500 && actuatorCounter[0] <= counterMax) {
    digitalWrite(motorPins[0], HIGH);
    digitalWrite(motorPins[1], LOW);
      actuatorCounter[0]++;
  }
//Reverse
  else if (xValue < 1300 && actuatorCounter[0] >= counterMin) {
    digitalWrite(motorPins[0], LOW);
    digitalWrite(motorPins[1], HIGH);
      actuatorCounter[0]--;
  }
  //BRAKE
if (actuatorCounter[0] >= counterMax || actuatorCounter[0] <= counterMin) {
    //Stop the actuator if at limits
    digitalWrite(motorPins[0], HIGH);
    digitalWrite(motorPins[1], HIGH);  // Stop the motor
}
}

void actuator2(int yValue) {
  //standby
  if (yValue < 3800 && yValue > 200) {
    digitalWrite(motorPins[2], LOW); 
    digitalWrite(motorPins[3], LOW);
  }
//Forward
 else if (yValue > 2000 && actuatorCounter[1] <= counterMax) {
    digitalWrite(motorPins[2], HIGH);
    digitalWrite(motorPins[3], LOW);
      actuatorCounter[1]++;
  }
//Reverse
  else if (yValue < 1800 && actuatorCounter[1] >= counterMin) {
    digitalWrite(motorPins[2], LOW);
    digitalWrite(motorPins[3], HIGH);
      actuatorCounter[1]--;
  }
  //BRAKE
if (actuatorCounter[1] >= counterMax || actuatorCounter[1] <= counterMin) {
    //Stop the actuator if at limits
    digitalWrite(motorPins[2], HIGH);
    digitalWrite(motorPins[3], HIGH);  // Stop the motor
}
}

void actuator3(int xValue) {
  //standby
  if (xValue < 3800 && xValue > 200) {
    digitalWrite(motorPins[4], LOW); 
    digitalWrite(motorPins[5], LOW);
  }
//Forward
 else if ( xValue < 1300 && actuatorCounter[2] <= counterMax) {
    digitalWrite(motorPins[4], HIGH);
    digitalWrite(motorPins[5], LOW);
      actuatorCounter[2]++;
  }
//Reverse
  else if (xValue > 1500 && actuatorCounter[2] >= counterMin) {
    digitalWrite(motorPins[4], LOW);
    digitalWrite(motorPins[5], HIGH);
      actuatorCounter[2]--;
  }
  //BRAKE
if (actuatorCounter[2] >= counterMax || actuatorCounter[2] <= counterMin) {
    //Stop the actuator if at limits
    digitalWrite(motorPins[4], HIGH);
    digitalWrite(motorPins[5], HIGH);  // Stop the motor
}
}

void actuator4(int yValue) {
    //standby
  if (yValue < 3800 && yValue > 200) {
    digitalWrite(motorPins[6], LOW); 
    digitalWrite(motorPins[7], LOW);
  }
//Forward
 else if (yValue < 1800 && actuatorCounter[3] <= counterMax) {
    digitalWrite(motorPins[6], HIGH);
    digitalWrite(motorPins[7], LOW);
      actuatorCounter[3]++;
  }
//Reverse
  else if (yValue > 2000 && actuatorCounter[3] >= counterMin) {
    digitalWrite(motorPins[6], LOW);
    digitalWrite(motorPins[7], HIGH);
      actuatorCounter[3]--;
  }
  //BRAKE
if (actuatorCounter[3] >= counterMax || actuatorCounter[3] <= counterMin) {
    //Stop the actuator if at limits
    digitalWrite(motorPins[6], HIGH);
    digitalWrite(motorPins[7], HIGH);  // Stop the motor
}
}


void reverseMotors() {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], HIGH);
  digitalWrite(motorPins[4], LOW);
  digitalWrite(motorPins[5], HIGH);
  digitalWrite(motorPins[6], LOW);
  digitalWrite(motorPins[7], HIGH);

  // Decrement actuator counters
  for (int i = 0; i < 4; i++) {
    if (actuatorCounter[i] > 0) {
      actuatorCounter[i]--;
    }
  }
}

void extendActuators() {
  while (!allActuatorsAtMax()) {
    for (int i = 0; i < 4; i++) {
      if (actuatorCounter[i] < counterMax/2) {
        digitalWrite(motorPins[i * 2], HIGH);
        digitalWrite(motorPins[i * 2 + 1], LOW);
        actuatorCounter[i]++;
      } else {
        digitalWrite(motorPins[i * 2], LOW);
        digitalWrite(motorPins[i * 2 + 1], LOW);
      }
    }
    delay(250); // Small delay to allow for motor updates
  }
}

bool allActuatorsAtMax() {
  for (int i = 0; i < 4; i++) {
    if (actuatorCounter[i] < counterMax/2) {
      return false;
    }
  }
  return true;
}
