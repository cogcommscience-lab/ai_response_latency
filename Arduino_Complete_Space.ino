#include <Keyboard.h> //importing Keyboard library
int ldrVal = 0; //stores value LDR inputs (brightness reading) 
int timerStart = 0; //creating empty start time variable
int currentTime = 0; //creating empty variable for "if" statement 

void setup() {           
  // put your setup code here, to run once:
  Serial.begin(9800); //for setting output to the computer (monitor)
}

void loop() {  
  // put your main code here  , to run repeatedly:

  ldrVal=analogRead(0); //Reads data from A0 pin (LDR input) and stores it in "val" variable  
  
  //Set the levels of brightness for "if" statement
  
  if(ldrVal < 800){ //Sets brightness level threshold to 800 (Arduino reads values to a max of 1023)
    timerStart = micros(); //Start time in microseconds after LDR reads flash
    Keyboard.write((char) 32); // Presses Spacebar
    currentTime = micros() - timerStart; //This gives me the time of the "if" statement 
    Serial.println(currentTime); //Print the time it took from LDR reading Flash to pressing Space key
  }
  delay(10); //Perform loop every second
 }
