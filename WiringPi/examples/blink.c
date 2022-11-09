/*
 * blink.c:
 *	Standard "blink" program in wiringPi. Blinks an LED connected
 *	to the first GPIO pin.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>

int blink = 1;

#define	LED	          15

// limpiar la salida antes de salir
void cleanup(int signo) {
	blink = 0;
	printf ("limpieza\n");
}

int main (void)
{
	signal(SIGINT, cleanup);
	signal(SIGTERM, cleanup);
	signal(SIGHUP, cleanup);

	printf ("OrangePi Pi blink\n");

	/* Initialize and setting WiringPi */
	wiringPiSetup();
  
	/* Configure GPIO mode */
	pinMode (LED, OUTPUT);

	while (blink) {
		digitalWrite(LED, HIGH);	// On
		delay(100);		            // mS
		digitalWrite(LED, LOW);	// Off
		delay(50);
	}

	digitalWrite(LED, LOW);
	return 0;
}
