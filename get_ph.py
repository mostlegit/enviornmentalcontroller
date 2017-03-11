#!/usr/bin/python
import serial
import time
import json

def get_ph_now():  
    try:
        ser = serial.Serial('/dev/ttyUSB0', 9600) #Trash Reading because first one normally garbage
        ser = serial.Serial('/dev/ttyUSB0', 9600)
        ph=ser.readline().strip()        
        print ph
    except Exception as exc:
        print 'Unable to get ph -- {}'.format(exc)

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
