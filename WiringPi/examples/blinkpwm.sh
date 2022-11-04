#!/bin/bash
#
# blink.sh:
#	Standard "blink" program in wiringPi. Blinks an LED connected
#	to the first GPIO pin.
#
# Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
#######################################################################
# This file is part of wiringPi:
#	https://projects.drogon.net/raspberry-pi/wiringpi/
#
#    wiringPi is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    wiringPi is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
#######################################################################

# LED Pin - wiringPi pin 0 is BCM_GPIO 17.
FREQ=1
echo $FREQ
CICLO=(1 / $FREQ)
echo $CICLO
RESOL=256
echo $RESOL
CARGAPER=10
echo $CARGAPER
CARGAON=$(((($RESOL * CARGAPER)) / 100))
echo $CARGAON
CARGAOFF=$(((((((( $RESOL * $CARGAPER)) / 100)) - 100))))
echo $CARGAOFF
PIN=40

gpio mode $PIN out

while true; do
  gpio write $PIN 1
  echo $(($CICLO * $CARGAON))
  sleep $(($CICLO * $CARGAON))
  gpio write $PIN 0
  echo $(($CICLO * $CARGAOFF))
  sleep $(($CICLO * $CARGAOFF))
done
