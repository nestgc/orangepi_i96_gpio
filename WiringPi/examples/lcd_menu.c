//#include <iostream.h>		// Include all needed libraries here
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <lcd.h>
#include <pthread.h>


#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif

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

int main (int argc, char *argv[])
{
  int i ;
  int lcd ;
  //int bits, rows, cols ;

  struct tm *t ;
  time_t tim ;

  char buf [32] ;

  //if (argc != 4)
  //  return usage (argv [0]) ;

  printf ("Raspberry Pi LCD test\n") ;
  printf ("=====================\n") ;

  //bits = atoi (argv [1]) ;
  //cols = atoi (argv [2]) ;
  //rows = atoi (argv [3]) ;

  if (!((rows == 1) || (rows == 2) || (rows == 4)))
  {
    fprintf (stderr, "%s: rows must be 1, 2 or 4\n", argv [0]) ;
    return EXIT_FAILURE ;
  }

  if (!((cols == 16) || (cols == 20)))
  {
    fprintf (stderr, "%s: cols must be 16 or 20\n", argv [0]) ;
    return EXIT_FAILURE ;
  }

  wiringPiSetup () ;

pinMode(LED_OUT, OUTPUT);		// Configure GPIO0 as an output
pinMode(ARR_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ABA_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ENTER_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ESC_IN, INPUT);		// Configure GPIO1 as an input

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
	//pinMode(27,  OUTPUT);
	//pinMode(28,  OUTPUT);
	//pinMode(29,  OUTPUT);
	//pinMode(30,  OUTPUT);
	//pinMode(22,  OUTPUT);
	//pinMode(20,  OUTPUT);
	//pinMode(26, OUTPUT);
  //USE WIRINGPI PIN NUMBERS
    //lcdHandle = lcdInit (rows, cols, 4, 11,10, 4,5,6,7,0,0,0,0) ;
    //lcdHandle = lcdInit (rows, cols, 4, 20,22, 30,29,28,27,0,0,0,0) ;
    lcdHandle = lcdInit (rows, cols, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
   }
   else
    lcdHandle = lcdInit (rows, cols, 8, LCD_RS, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

  if (lcdHandle < 0)
  {
    fprintf (stderr, "%s: lcdInit failed\n", argv [0]) ;
    return -1 ;
  }

  lcdPosition (lcdHandle, 0, 0) ; lcdPuts (lcdHandle, "Nestor G") ;
  lcdPosition (lcdHandle, 0, 1) ; lcdPuts (lcdHandle, "  casita  ") ;

  waitForEnter () ;

  if (rows > 1)
  {
    lcdPosition (lcdHandle, 0, 1) ; lcdPuts (lcdHandle, "  wiringpi.com  ") ;

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
  }


}
/*
String menu_items[] = {"Schedule 1", "Schedule 2", "Start Pump", "Stop Pump"};
//using namespace std;		// No need to keep using “std”

int main()
{
wiringPiSetup();			// Setup the library
pinMode(LCD_OUT, OUTPUT);		// Configure GPIO0 as an output
pinMode(ARR_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ABA_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ENTER_IN, INPUT);		// Configure GPIO1 as an input
pinMode(ESC_IN, INPUT);		// Configure GPIO1 as an input

// Main program loop
while(1)
{
	// Button is pressed if digitalRead returns 0
	if(digitalRead(ENTER_IN) == 0){
        printf("digitalRead 1");
    
	
	// Toggle the LED
	digitalWrite(LED_OUT, !digitalRead(LED_OUT));
    printf("digitalWrite %d", !digitalRead(LED_OUT));
delay(500); 	// Delay 500ms
}
}
	return 0;
}









// PIN DEFINITIONS
//const int LED_PIN = 56;
//const int LCD_BKL_PIN = 6;
//const int PUMP_PIN = 5;

// LCD
// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(8, 9, 13, 12, 11, 10);
//const int LCD_BKL_PWM = 170; // (255 * 3.3)/5 = 168.3 But measured 170 is 3.1V
//const int LCD_ROWS = 2;
//const int LCD_COLS = 16;
const int NUM_MENUS = 4;

int current_menu = 0;
int frame = 0;
int cursor_pos = 0;
String menu_items[] = {"Schedule 1", "Schedule 2", "Start Pump", "Stop Pump"};

// Keypad
//const byte ROWS = 4; // four rows
//const byte COLS = 4; // four columns
//define the two-dimensional array on the buttons of the keypads
//char hexa_keys[ROWS][COLS] = {{'1','2','3','A'},
//                             {'4','5','6','B'},
//                             {'7','8','9','C'},
//                             {'*','0','#','D'}
//                             };

//byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad
//byte colPins[COLS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad

//Keypad_I2C key_pad(makeKeymap(hexa_keys), rowPins, colPins, ROWS, COLS, I2C_PFC8574_ADDR); 


const char UP = 'ARR_IN';
const char DOWN = 'ABA_IN';
const char CONFIRM = 'ENTER_IN';
const char BACK = 'ESC_IN';

// As opposed to Python, % of negative numbers is, welp, negative.
int mod(int x, int y) {
   return x<0 ? ((x + 1) % y) + y - 1 : x % y;
}

void displayMenu() {
  for (int i=0; i < LCD_ROWS; i++) {
    lcd.setCursor(1,i);
    lcd.print(menu_items[(i + frame) % NUM_MENUS]);
  }
}

void displayCursor() {
  printCursor((cursor_pos + frame) % LCD_ROWS);
}

void printCursor(int row) {
  for (int i=0; i < LCD_ROWS; i++) {
    if (i != row) {
      lcd.setCursor(0, i);
      lcd.print(" ");
    }
  }
  lcd.setCursor(0, row);
  lcd.print(">");
}

void updateTimeMenu(int start_pos, int sched) {
  int idx = 0;
  lcd.setCursor(start_pos, 0);
  lcd.blink();
  char key_press = NULL;
  while ((idx < DATE_LENGTH) && !(key_press == BACK || key_press == CONFIRM)) {
    key_press = key_pad.getKey();
    if (key_press < '9' && key_press > '0') {
      if ((idx == 0 && key_press > '2') ||
          (idx == 1 && key_press > '3' && schedules[sched].date[idx - 1] == '2') ||
          (idx == 2 && key_press > '5')) {
        continue;
      }
      schedules[sched].date[idx] = key_press;
      lcd.print(key_press);
      if (idx == 1) 
        lcd.print(":");
      idx++;
    }
  }
  lcd.noBlink();
}

void updateDurationMenu(int start_pos, int sch) {
  char duration[2];
  String d = String(schedules[sch].duration);
  int idx = 0;
  char key_press = NULL;
  
  lcd.setCursor(start_pos, 1);
  lcd.blink();
  
  while ((idx < DURATION_LENGTH) && !(key_press == BACK || key_press == CONFIRM)) {
    key_press = key_pad.getKey();
    if (key_press <= '9' && key_press >= '0') {
      duration[idx] = key_press;
      lcd.print(key_press);
      idx++;
    }
  }
  if (idx == 1) { // only first digit entered
    duration[1] = d.charAt(d.length() - 1);
  }
  schedules[sch].duration = String(duration).toInt();
  lcd.noBlink();
}

void updateScheduleMenu(int sch) {
  int cur = 0;
  printCursor(cur);
  lcd.setCursor(1,0);
  lcd.print("Time: ");
  printTime(schedules[sch].date);
  lcd.setCursor(1,1);
  lcd.print("Duration: ");
  printDuration(schedules[sch].duration);
  lcd.print("min");
  
  char key_press = NULL;
  while (key_press != BACK) {
    key_press = key_pad.getKey();
    switch(key_press) {
      case CONFIRM:
        if (cur == 0) {
          updateTimeMenu(7, sch);
        } else{
          updateDurationMenu(11, sch);
        }
        break;
      case DOWN:
        cur = (cur + 1) % LCD_ROWS;
        printCursor(cur);
        break;
    } 
  }
}

void startPumpMenu() {
  lcd.setCursor(0,0);
  lcd.print(" Pump is now on");
  digitalWrite(LED_PIN, HIGH);
  analogWrite(PUMP_PIN, 255);
  // Wait for a key press
  char key_press = NULL;
  while (!(key_press = key_pad.getKey())) {
    if (key_press == BACK) break;
  }
}

void stopPumpMenu() {
  lcd.setCursor(0,0);
  lcd.print(" Pump is now off");
  digitalWrite(LED_PIN, LOW);
  analogWrite(PUMP_PIN, 0);
  // Wait for a key press
  char key_press = NULL;
  while (!(BACK == key_pad.getKey()));
}

void goIntoMenu() {
  lcd.clear();
  switch(cursor_pos) {
    case 0:
    case 1:
      updateScheduleMenu(cursor_pos);
      break;
    case 2:
      startPumpMenu();
      break;
    case 3:
      stopPumpMenu();
      break;
  }
  lcd.clear();
}

char mainMenu() {
  char key_press = key_pad.getKey();
  if (key_press) {
    lcd.clear();
    lcdOn();
  }
  switch(key_press) {
    case BACK:
      break;
    case CONFIRM:
      goIntoMenu();
      break;
    case DOWN:
      cursor_pos = mod((cursor_pos + 1), NUM_MENUS);
      if ((cursor_pos + frame) % 2 == 0)
        frame = mod((frame + 1), NUM_MENUS);
      break;
    case UP:
      cursor_pos = mod((cursor_pos - 1), NUM_MENUS);
      if ((cursor_pos + frame) % 2 != 0)
        frame = mod((frame - 1), NUM_MENUS);
      break;
    default:
      if (key_press != NO_KEY) {
        Serial.print("Pressed: ");
        Serial.println(key_press);
      }
  }
  return key_press;
}

void setup() {
  // Serial for debugging
  Serial.begin(9600);
  
  // Configure in/out pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(LCD_BKL_PIN, OUTPUT);  // The LCD Backlight control

  // Init the I2C bus
  Wire.begin();
  // Init the Keypad library
  key_pad.begin();
  // End of Keypad init
  // We have a 16x2 (column/row) LCD
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcdOff();
  lcd.clear();
}

void loop() {
  displayMenu();
  displayCursor();
  mainMenu();
}
*/