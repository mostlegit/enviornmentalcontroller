#!/usr/bin/python
from flask import Flask, render_template, request, url_for
import RPi.GPIO as GPIO

from time import sleep
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
pump1pin = 2
pump2pin = 3

#pumps_to_turn_on = {2 : 3 , 3 : 4, 4 : 1}
#Dictionary in format {GPIO#, Second_on)


for i in [ 2 , 3]:
    GPIO.setup(i,GPIO.OUT)
    GPIO.setup(i, GPIO.LOW)

