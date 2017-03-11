#!/usr/bin/python
import serial
import time
import json

def get_ph_now(attempt=0):  
    try:
        ser = serial.Serial('/dev/ttyUSB0', 9600)
        print ser.readline()
        ph=float(ser.readline().split(':')[-1].strip())
        return ph
    except Exception as exc:
        print 'Attempt {}: Unable to get ph -- {}'.format(attempt+1, exc)
        attempt+=1
        get_ph_now(attempt)

def get_ph_average(duration,pause=1):
     ph_list = []
     for i in range(0,duration):
         ph_list.append(get_ph_now())
         time.sleep(pause)
     print 'Average over the last {} cycles with a pause of {} second(s) between'.format(duration,pause)
     print sum(ph_list) / len(ph_list)
         
def main():
    print 'PH now'
    print get_ph_now()
    print 'PH over 30 seconds'
    get_ph_average(30,pause=1)
    quit()
   
main()
