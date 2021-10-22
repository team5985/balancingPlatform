
#include <Servo.h> //This just imports the Servo library


/** 
 *  @param int value the input value
 *  @param int minValue the minimum limit
 *  @param int maxValue the maximum limit
 *  
 *  @return the new constrained value
 */
int constrainCheck(int value, int minValue, int maxValue) {
  if(value > maxValue) {
    value = maxValue;
  } else if (value < minValue) {
    value = minValue;
  }
  return value;
}

  //Define gyro pins
  
  #define sensorXPin A0 //Analog pin 0
  #define sensorYPin A1 //Analog pin 1

  //Set sensor defaults

  int sensorValX = 500; //These two variables will be used for the gyro
  int sensorValY = 500;

  //define variables

  int minAcceptableThresholdX = 480;
  int maxAcceptableThresholdX = 520;
  int minAcceptableThresholdY = 480;
  int maxAcceptableThresholdY = 520;

  int xStepAmmount = 1;
  int yStepAmmount = 1;
  int stepDelay = 10;

  //Create the 'Servo' objects

  Servo servoX;
  Servo servoY;
  
void setup() {

  Serial.begin(9600); //for debugging
 
  servoX.attach(11); //digital 11
  servoY.attach(10); //digital 10

  //Sensor zeros on startup

  int xGyroZero = 500;
  int yGyroZero = 560;

  //Set thresholds

  minAcceptableThresholdX = (xGyroZero - 20);
  maxAcceptableThresholdX = (xGyroZero + 20);
  minAcceptableThresholdY = (yGyroZero - 20);
  maxAcceptableThresholdY = (yGyroZero + 20);

  //Set default gyro sensor values

  sensorValX = xGyroZero;
  sensorValX = xGyroZero;

}

void loop() {

  //update the sensor variables

  sensorValY = analogRead(A1);
  sensorValX = analogRead(A0);

  //Adjust servo position based on 

  //X

  if(sensorValX > maxAcceptableThresholdX) {

    servoX.write(constrainCheck(servoX.read() + xStepAmmount, 0, 180));
    
  }else if(sensorValX < minAcceptableThresholdX) {
    
    servoX.write(constrainCheck(servoX.read() - xStepAmmount, 0, 180));
 
  } 

  //Y

  if(sensorValY > maxAcceptableThresholdY) {

    servoY.write(constrainCheck(servoY.read() - yStepAmmount, 0, 180));
    
  }else if(sensorValY < minAcceptableThresholdY) {
    
    servoY.write(constrainCheck(servoY.read() + yStepAmmount, 0, 180));
 
  }

  //Delay
  
  delay(stepDelay);
  
  Serial.println(sensorValY);

}
