#!/usr/bin/python
import serial
import time
import json

def get_ph_now(attempt=0):  
    try:
        ser = serial.Serial('/dev/ttyUSB0', 9600) #Trash Reading because first one normally garbage
        ser = serial.Serial('/dev/ttyUSB0', 9600)
        ph=float(ser.readline().split(':')[-1].strip())
        print ph
    except Exception as exc:
        print 'Attempt {}: Unable to get ph -- {}'.format(attempt+1, exc)
        attempt+=1
        get_ph_now(attempt)

def get_ph_average(duration,pause=1):
     ph_list = []
     for i in range(0,duration):
         ph_list.append(get_ph_now())
         time.sleep(pause)
     print sum(ph_list) / len(ph_list)
         
def main():
    get_ph_now()
    get_ph_now()
    quit()
   
main()
