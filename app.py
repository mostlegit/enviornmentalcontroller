#!/usr/bin/python
from flask import Flask, render_template, request, url_for
import RPi.GPIO as GPIO

from time import sleep

GPIO.setmode(GPIO.BCM)
pump1pin = 2
pump2pin = 3
 
#pumps_to_turn_on = {2 : 3 , 3 : 4, 4 : 1}
#Dictionary in format {GPIO#, Second_on)


def turn_on(sec_pause, pin_no):
    print "{} is going to turn on for {} seconds".format(pin_no,sec_pause)
    GPIO.setup(pin_no, GPIO.LOW)
    sleep(sec_pause)
    GPIO.setup(pin_no, GPIO.HIGH)


#try:
#    for pump, seconds in pumps_to_turn_on.iteritems():
#        turn_on(seconds,pump)
#except:
#    print "Shit went bad. Exiting"
#    for pump in pumps_to_turn_on.keys():
#        GPIO.setup(pump, GPIO.HIGH)

app = Flask(__name__)

@app.route('/')
def form():
    return render_template('./form_submit.html')

# Define a route for the action of the form, for example '/hello/'
# We are also defining which type of requests this route is 
# accepting: POST requests in this case
@app.route('/runpumps/', methods=['POST'])
def runpumps():
    pump1time=request.form['pump1time']
    pump2time=request.form['pump2time']
    print 'Turning on pump 1 on GPIO {} for {} seconds'.format(pump1pin, pump1time)
    turn_on(float(pump1time), pump1pin)
    print 'Turning on pump 2 on GPIO {} for {} seconds'.format(pump2pin, pump2time)
    turn_on(float(pump2time), pump2pin)
    return render_template('./form_action.html', pump1time=pump1time, pump2time=pump2time)

if __name__ == '__main__':
    try:
        app.run()
    except Exception as exc:
        print exc
        print 'Turning shit off for sanity sake'
        for pin in [pump2pin, pump1pin]:
            GPIO.setup(pin, GPIO.HIGH)
