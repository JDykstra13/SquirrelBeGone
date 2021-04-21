//------------------IMPORTS-------------------------------
#include <Servo.h> //include the servo library
#include <SPI.h>
#include <Pixy.h>

//------------------VARIABLES-------------------------------
const int trigPin = 11; //connects to the trigger pin on the distance sensor
const int echoPin = 12; //connects to the echo pin on the distance sensor
boolean sighted; //if true there is movement
int minDistance;
boolean squirrel; //if true there is squirrel
float distance = 0; //stores the distance measured by the distance sensor
Servo servo1; //create a servo object called servo1 
Pixy pixy; //global instance of pixy

//------------------SETUP-------------------------------
void setup()
{
  Serial.begin (9600); //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT); //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT); //the echo pin will measure the duration of pulses coming back from the distance sensor

  sighted = false;
  squirrel = false;
  minDistance = 20;
  
  servo1.attach(2); //attach servo 1 to pin 2
}

//------------------WHERE THE ACTION HAPPENS-------------------------------
void loop()
{ 
  
 checkMovement(); //if the ultrasonics sense movement, sighted becomes true

 if(sighted){
  rotate(); //top rotates to where movement was sighted
  checkcolor(); //if signiture is spotted, squirrel becomes true
 }
 
  if(sighted && squirrel){ //if signiture and squirrel are true
      turnPumpOn(); //then the pump is turned on
  } 
  
}

//------------------CHECKS MOVEMENT------------------------------- 
void senseMovement(){
  distance = getDistance();   //variable to store the distance measured by the sensor

  Serial.print(distance);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance
  
  if(distance <= minDistance){
    sighted = true;
  }
  sighted = false;
}

//------------------ROTATE TOP-------------------------------
void rotate(){
  
}

//------------------CHECK COLOR WITH CAMERA-------------------------------
void checkColor(){
  
}

//------------------TURNS THE PUMP ON-------------------------------
void turnPumpOn(){
   int position; //create a local variable to store the servo's position.
   servo1.write(180); // Tell servo to go to 90 degrees(turn on)
   delay(1000); // Pause to get it time to move 
}


//------------------RETURNS THE DISTANCE MEASURED-------------------------------
float getDistance()
{
  float echoTime; //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance; //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH); //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0; //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance; //send back the distance that was calculated
}
