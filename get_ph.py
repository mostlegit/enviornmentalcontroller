#!/usr/bin/python
import serial
import time
import json

def get_ph_now():  
    try:
        ser = serial.Serial('/dev/ttyUSB0', 9600)
        ph=ser.readline()
        print ph
        return float(ph)
    except Exception as exc:
        print 'Unable to get ph'

def get_ph_average(duration,pause=1):
     ph_list = []
     for i in range(0,duration):
         ph_list.append(get_ph_now())
         time.sleep(pause)
     print sum(ph_list) / len(ph_list)
         

