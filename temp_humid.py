#!/usr/bin/python
def get_env_info():
    import DHT22
    import pigpio
    from time import sleep
    pi = pigpio.pi()
    s = DHT22.sensor(pi,3)
    s.trigger()
    sleep(.01)
    ctemp = s.temperature()
    print('Humidity Percentage: {:3.2f}'.format(s.humidity() / 1.))
    print('Celcius Temp: {:3.2f}'.format(ctemp / 1.))
    print('F Temp: {:3.2f}'.format(ctemp * 9/5 + 32  / 1.))
    s.cancel()
    pi.stop()


