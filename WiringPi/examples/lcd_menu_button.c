#include <wiringPi.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <lcd.h>

#define ARR_IN 56
#define ABA_IN 66
#define ENTER_IN 26
#define ESC_IN 25
#define LED_OUT 15

#define LCD_RS  20               //Register select pin
#define LCD_E   22               //Enable Pin
#define LCD_D0  0               //Data pin D0
#define LCD_D1  0               //Data pin D1
#define LCD_D2  0               //Data pin D2
#define LCD_D3  0               //Data pin D3
#define LCD_D4  30               //Data pin D4
#define LCD_D5  29               //Data pin D5
#define LCD_D6  28               //Data pin D6
#define LCD_D7  27               //Data pin D7



#define bits 4
#define rows 2
#define cols 16


// Global lcd handle:

static int lcdHandle ;

/*
 * usage:
 *********************************************************************************
 */

int usage (const char *progName)
{
  fprintf (stderr, "Usage: %s bits cols rows\n", progName) ;
  return EXIT_FAILURE ;
}

/*
 * waitForEnter:
 *********************************************************************************
 */

static void waitForEnter (void)
{
  printf ("Press ENTER to continue: ") ;
  (void)fgetc (stdin) ;
}

//limpieza antes de salir
void cleanup(int signo) {
	printf ("limpieza\n");
    lcdClear    (lcdHandle) ;
    digitalWrite(LED_OUT, LOW);
    exit(0);
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


/// @brief 
/// @param  
/// @return 
int main(void)
{

    char buf [32] ;

	signal(SIGINT, cleanup); 
	signal(SIGTERM, cleanup);
	signal(SIGHUP, cleanup);

wiringPiSetup();			// Setup the library
pinMode(LED_OUT, OUTPUT);		// Configure GPIO0 as an output
pinMode(ARR_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ABA_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ENTER_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ESC_IN, INPUT);		// Configure GPIO1 as an input

//seteo pines de LCD
pinMode(LCD_RS,  OUTPUT);
pinMode(LCD_RS,  OUTPUT);
pinMode(LCD_D0,  OUTPUT);
pinMode(LCD_D1,  OUTPUT);
pinMode(LCD_D2,  OUTPUT);
pinMode(LCD_D3,  OUTPUT);
pinMode(LCD_D4,  OUTPUT);
pinMode(LCD_D5,  OUTPUT);
pinMode(LCD_D6,  OUTPUT);
pinMode(LCD_D7,  OUTPUT);

if (bits == 4){
  //USE WIRINGPI PIN NUMBERS
    //lcdHandle = lcdInit (rows, cols, 4, 11,10, 4,5,6,7,0,0,0,0) ;
    //lcdHandle = lcdInit (rows, cols, 4, 20,22, 30,29,28,27,0,0,0,0) ;
    lcdHandle = lcdInit (rows, cols, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
   }
   else
    lcdHandle = lcdInit (rows, cols, 8, LCD_RS, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
/*
  if (lcdHandle < 0)
  {
    fprintf (stderr, "%s: lcdInit failed\n", argv [0]) ;
    return -1 ;
  }
*/

  lcdPosition (lcdHandle, 0, 0) ; lcdPuts (lcdHandle, "Prueba") ;
  lcdPosition (lcdHandle, 0, 1) ; lcdPuts (lcdHandle, "  Menu  ") ;

  waitForEnter () ;

  if (rows > 1)
  {
    lcdClear    (lcdHandle) ;
    lcdPosition (lcdHandle, 0, 1) ; lcdPuts (lcdHandle, "  presiona un boton  ") ;

/*
    if (rows == 4)
    {
      lcdPosition (lcdHandle, 0, 2) ;
      for (i = 0 ; i < ((cols - 1) / 2) ; ++i)
        lcdPuts (lcdHandle, "=-") ;
      lcdPuts (lcdHandle, "=3") ;

      lcdPosition (lcdHandle, 0, 3) ;
      for (i = 0 ; i < ((cols - 1) / 2) ; ++i)
        lcdPuts (lcdHandle, "-=") ;
      lcdPuts (lcdHandle, "-4") ;
    }
*/
  }




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

    lcdClear    (lcdHandle) ;
    lcdPosition (lcdHandle, 0, 0) ; lcdPuts (lcdHandle, "Prueba") ;
    lcdPosition (lcdHandle, 0, 1) ;
    sprintf (buf, "led pin %d", digitalRead(LED_OUT)) ;
    lcdPuts (lcdHandle, buf) ;
//delay(500); 	// Delay 500ms
        }
}
}

	return 0;
}
