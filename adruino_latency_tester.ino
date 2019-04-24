#include <Keyboard.h> // Import keyboard library
int ldrVal = 0; //stores value LDR inputs (brightness reading)
const int analogInPin = A1; // Analog input pin the module is attached to
int timerStartMic = 0; // Creating an empty start time variable for mic
int currentTimeMic = 0; // Creating an empty variable for "if" statement mic
int timerStartLdr = 0; // Creating an empty start time variable for LDR
int currentTimeLdr = 0; // Creating an empty variable for "if" statement LDR

void setup() {
  // put your setup code here, to run once:

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

if(outputValue > 10){// Sets the sound value threshold to 224 (max is 255)

  timerStartMic = micros(); // Start time in microseconds after mic detects loud noise
  Keyboard.write((char) 32); // Press spacebar
  currentTimeMic = micros()-timerStartMic; //Gives the time of the "if" statement - a measure of latency
  Serial.print("mic = ");  // Label
  Serial.println(currentTimeMic); //Print the time it took from the mic sensing audio to pressing the space key
}
delay(1);

// Loop for LDR Sensor

ldrVal=analogRead(0); //Reads data from A0 pin (LDR input) and stores it in "val" variable  
  
// Set the levels of brightness for "if" statement
  
if(ldrVal < 800){ //Sets brightness level threshold to 800 (Arduino reads values to a max of 1023)
  timerStartLdr = micros(); //Start time in microseconds after LDR reads flash
  Keyboard.write((char) 32); // Presses Spacebar
  currentTimeLdr = micros() - timerStartLdr; //This gives me the time of the "if" statement 
  Serial.print("\t ldr = "); // Label  
  Serial.println(currentTimeLdr); //Print the time it took from LDR reading Flash to pressing Space key
  }
  delay(1); //Perform loop every 10 millisecond


}
