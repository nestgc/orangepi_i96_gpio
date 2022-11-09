#include <wiringPi.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define ARR_IN 56
#define ABA_IN 66
#define ENTER_IN 26
#define ESC_IN 25
#define LED_OUT 15

void cleanup(int signo) {
    printf ("/n%i",signo);
}

void ledOn(){
    printf("led ON/OFF");
    digitalWrite(LED_OUT, !digitalRead(LED_OUT));
    delay(500); 
}

unsigned short int isPressed(unsigned short int button){
    static struct timespec lastCall;
    struct timespec thisCall;
    float timeDiff;

    clock_gettime(CLOCK_REALTIME, &thisCall);
    timeDiff = (thisCall.tv_sec + thisCall.tv_nsec/1E9 - lastCall.tv_sec - lastCall.tv_nsec/1E9)*5;
    lastCall = thisCall;
    return timeDiff > 1 ? 1 : 0;
     
}


int main(void)
{

	signal(SIGINT, cleanup); 
	signal(SIGTERM, cleanup);
	signal(SIGHUP, cleanup);

wiringPiSetup();			// Setup the library
pinMode(LED_OUT, OUTPUT);		// Configure GPIO0 as an output
pinMode(ARR_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ABA_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ENTER_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ESC_IN, INPUT);		// Configure GPIO1 as an input

/*
//interruption mode no funciona
wiringPiISR(ENTER_IN, INT_EDGE_BOTH, ledOn);

pause();
*/

// Main program loop
while(1)
{
	// Button is pressed if digitalRead returns 0
	if(digitalRead(ENTER_IN) == 0){
    //            printf("\ndigitalRead %d", digitalRead(LED_OUT));
        
        if(isPressed(ENTER_IN)){
	// Toggle the LED
	digitalWrite(LED_OUT, !digitalRead(LED_OUT));
    printf("\ndigitalWrite %d", !digitalRead(LED_OUT));
//delay(500); 	// Delay 500ms
        }
}
}

	return 0;
}
