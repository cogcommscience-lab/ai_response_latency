#include <Keyboard.h> // Import keyboard library
const int analogInPin = A1; // Analog input pin the module is attached to
int timerStartMic = 0; // Creating an empty start time variable for Mic
int currentTimeMic = 0; // Creating an empty variable for "if" statement Mic
int ledPin = 13; // LED connected to digital 13 pin 

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT); // Setting LED pin as an output
  
// initialize serial communications at 9600 bps
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Loop for mic sensor

//read the analog in value
int sensorValue = analogRead(analogInPin);

// map it to the range of the analog out, decreased a bit and constrain the value
int outputValue = constrain(255 - map(sensorValue, 0, 1023, 0, 255) - 5, 0, 255);

if(outputValue < 208){// Sets the sound value threshold to 224 (max is 255) 
  timerStartMic = micros(); //Start timer in microseconds after Mic input is received 
  Keyboard.write((char) 98); // Computer presses the "b" key
  currentTimeMic = micros() - timerStartMic; // Time elapsed from Mic input to space key press 
  Serial.print("\t ldr = "); // Labels serial monitor output  
  Serial.println(currentTimeMic); // Prints the time elapsed
  digitalWrite(ledPin, HIGH); //Turns on LED
  delay(100); //AI samples at 100 ms
  }
  else {
  digitalWrite(ledPin, LOW); //Turns off LED
}
  delay(1); //Perform loop every 1 millisecond


}
