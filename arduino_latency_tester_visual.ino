#include <Keyboard.h> // Import keyboard library
int ldrVal = 0; //stores LDR input values from A0 pin
int timerStartLdr = 0; // Creating an empty start time variable for LDR
int currentTimeLdr = 0; // Creating an empty variable for "if" statement LDR
int ledPin = 13; // LED connected to digital 13 pin 

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT); // Setting LED pin as an output
  
// initialize serial communications at 9600 bps
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // LDR sensor with LED Loop
                                                               
ldrVal=analogRead(0); //Reads data from A0 pin (LDR input) and stores it in "ldrVal" variable  
  
// Set brightness threshold for "if" statement
// Arduino only reads values from 0 to 1023
  
if(ldrVal < 1000){ //Set threshold value
  timerStartLdr = micros(); //Start timer in microseconds after LDR input is received 
  Keyboard.write((char) 32); // Computer presses the space key
  currentTimeLdr = micros() - timerStartLdr; // Time elapsed from LDR input to space key press 
  Serial.print("\t ldr = "); // Labels serial monitor output  
  Serial.println(currentTimeLdr); // Prints the time elapsed
  digitalWrite(ledPin, HIGH); //Turns on LED
  delay(10); //AI samples at 10 ms
  }
  else {
  digitalWrite(ledPin, LOW); //Turns off LED
}
  delay(10); //Perform loop every 10 millisecond


}
