#!/usr/bin/python
import serial
import time
import json

cycleduration=8

def get_ph_now(attempt=0):  
    try:
        ser = serial.Serial('/dev/ttyUSB0', 9600)
        rawser = ser.readline().strip()
        while not 'PH' in rawser:
            print 'No Reading. Trying again'
            time.sleep(.5)
            rawser = ser.readline()
        ph=float(rawser.split(':')[-1].strip())
        return ph
    except Exception as exc:
        print 'Attempt {}: Unable to get ph -- {}\nSerial Info:{}'.format(attempt+1, exc,rawser)
        attempt+=1
        get_ph_now(attempt)

def get_ph_average(duration,pause=1):
     print 'PH over {} cycles'.format(duration)
     ph_list = []
     for i in range(0,duration):
         ph_list.append(get_ph_now())
         time.sleep(pause)
     print 'Average over the last {} cycles with a pause of {} second(s) between'.format(duration,pause)
     print sum(ph_list) / len(ph_list)
         
def main():
    print 'PH now'
    print get_ph_now()
    get_ph_average(cycleduration,pause=1)
    quit()
   
#main()
