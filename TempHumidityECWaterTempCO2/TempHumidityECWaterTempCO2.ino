// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

const int analogInPin = A1;  // Analog input pin that the sensor output is attached to
const int analogOutPin = 11; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the sensor
int outputValue = 0;        // value output to the PWM (analog out)

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            4         // Pin which is connected to the DHT sensor.

#include <OneWire.h>
#include <DallasTemperature.h>

// This is an updated version of the Tester program that comes with the DallasTemp library
// It will drive a DS18x20 tempurature sensor plugged directly to the Arduino header pins 8,9, and 10.
// The flat side of the sensor should face into the center of the board.
// More info and a video here...
// http://wp.josh.com/2014/06/23/no-external-pull-up-needed-for-ds18b20-temp-sensor/#more-1892


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 8

// Uncomment this line if you are using the updated dallas_temp_library that 
// supports the busFail() method to diagnose bus problems
// #define BUSFAIL 

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Uncomment the type of sensor in use:
//#define DHTTYPE           DHT11     // DHT 11
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

//CO2
#include "SoftwareSerial.h"
#include "NDIR_SoftwareSerial.h"

//Select 2 digital pins as SoftwareSerial's Rx and Tx. For example, Rx=2 Tx=3
NDIR_SoftwareSerial mySensor(2, 3);

void setup()
{
    Serial.begin(9600);

//CO2
    if (mySensor.begin()) {
        Serial.println("Wait 10 seconds for sensor initialization...");
        delay(10000);
    } else {
        Serial.println("ERROR: Failed to connect to the sensor.");
        while(1);
    }
      // Initialize device.
  dht.begin();
  // Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  // Serial.println("------------------------------------");
  // Serial.println("Temperature");
  // Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  // Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  // Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  // Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  // Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  // Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  // Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  // Serial.println("------------------------------------");
  // Serial.println("Humidity");
  // Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  // Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  // Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  // Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  // Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  // Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
  // Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  // This lines just make it so you can plug a DS18B20 directly into 
  // digitial pins 8-10. 
  
  digitalWrite( 8 , LOW );
  pinMode( 8  , OUTPUT );
  digitalWrite( 10 , LOW );  
  pinMode( 10 , OUTPUT );
  
  // Serial.println("Dallas Temperature IC Control Library Demo");
}

void loop() {
  //CO2
    if (mySensor.measure()) {
        Serial.print("CO2 : ");
        Serial.print(mySensor.ppm);
        Serial.print(" ");
    } else {
        Serial.println("Sensor communication error.");
    }

    delay(1000);
      // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temp : ");
    Serial.print(event.temperature * 9/5 + 32);
    Serial.print(" *F ");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity : ");
    Serial.print(event.relative_humidity);
    Serial.print("% ");
  }
// read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 5000);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
       
  Serial.print("EC : ");      
  Serial.print(analogRead(1)* 5.00 / 1024, 2);   
  Serial.print(" ");
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(500);
  //Water Temp
    #ifdef BUSFAIL
  
    Serial.print(" Test:");
      
    if (sensors.reset()) {
      
      Serial.print("good");
      
    } else {
      
      if (sensors.busFail()) {
        
        Serial.print("fail");
        
      } else {
        
        Serial.print("empty");
        
      }
        
    }
    
  #endif 

  int numberOfDevices; // Number of temperature devices found

  DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address    
  
  // For testing purposes, reset the bus every loop so we can see if any devices appear or fall off
  sensors.begin();

  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();

  Serial.print("Water ");
 // report parasite power requirements

  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
  {
    // Output the device ID
    Serial.print(": ");


                float tempC = sensors.getTempC(tempDeviceAddress);

                Serial.print(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit

  } 
  //else ghost device! Check your power requirements and cabling
  
  }
  
 Serial.println("");
  
 delay(1000);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

