/*
I, Jorge Isaza, student number 000811486, certify that all code submitted is my own work; 
that I have not copied it from any other source. 
I also certify that I have not allowed my work to be copied by others.
*/



// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College
// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>
// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

DeviceAddress tempSensor;


/// @brief Function to rank the temperature
/// @param temp 
/// @return 
String TempertureRank(double temp){
  String response = "";

  if(temp < 10){
    response = "Cold!";
  }
  else if (temp >= 10 && temp < 15)
  {
    response = "Cool!";
  }
  else if (temp >= 15 && temp < 25)
  {
    response = "Perfect!";
  }
  else if (temp >= 25 && temp < 35)
  {
    response = "Hot!";
  }
  else{
    response = "Too Hot!";
  }

  return response;
} 
bool sensorAddress = false;


void setup() {
  // configure the USB serial monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  DS18B20.begin();

  // Gets a boolean indicating if the sensor was found
  sensorAddress = DS18B20.getAddress(tempSensor, 0);
  
  //Serial.println("Sensor Address: " + sensorAddress); 
  if(!sensorAddress){
    Serial.println("Temperature Application");
    Serial.println("NO DS18B20 temperature sensors are installed");
  }

}
void loop() {
  float fTemp;
  // ask DS18B20 for the current temperature

  sensorAddress = DS18B20.getAddress(tempSensor, 0);
  //Serial.println("Sensor Address: " + sensorAddress); 

  if(sensorAddress){
    DS18B20.requestTemperatures();
    // fetch the temperature. We only have 1 sensor, so the index is 0.
    fTemp = DS18B20.getTempCByIndex(0);
    // print the temp to the USB serial monitor
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius");
    String tempertureRanked = TempertureRank(fTemp);
    Serial.println("Or " + tempertureRanked); 
  }

  
  // wait 2s (2000ms) before doing this again
  delay(5000);
}
