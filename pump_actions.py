#!/usr/bin/python

import RPi.GPIO as GPIO

from time import sleep


def turn_on(sec_pause, pin_no):
    GPIO.setmode(GPIO.BCM)
    print "{} is going to turn on for {} seconds".format(pin_no,sec_pause)
    GPIO.setup(pin_no, GPIO.OUT)
    GPIO.setup(pin_no, GPIO.LOW)
    sleep(sec_pause)
    GPIO.setup(pin_no, GPIO.HIGH)
    GPIO.cleanup()
