//#include <iostream.h>		// Include all needed libraries here
#include <wiringPi.h>
#define LCD_IN 56
#define LCD_OUT 15
//using namespace std;		// No need to keep using “std”

int main()
{
wiringPiSetup();			// Setup the library
pinMode(LCD_OUT, OUTPUT);		// Configure GPIO0 as an output
pinMode(LCD_IN, INPUT);		// Configure GPIO1 as an input

// Main program loop
while(1)
{
	// Button is pressed if digitalRead returns 0
	if(digitalRead(LCD_OUT) == 1)
{	
	// Toggle the LED
	digitalWrite(LCD_OUT, !digitalRead(LCD_OUT));
delay(500); 	// Delay 500ms
}
}
	return 0;
}