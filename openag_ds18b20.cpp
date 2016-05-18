/** 
 *  \file openag_ds18b20.cpp
 *  \brief Sensor module for temperature. 
 */
#include "openag_ds18b20.h"

Ds18b20::Ds18b20(String temperature_id, int temperature_pin) {
  _temperature_id = temperature_id;
  _temperature_pin = temperature_pin;
}


void Ds18b20::begin(void) {
  // Construct Objects
  _ds = new OneWire(_temperature_pin);
  getTemperature();
}


String Ds18b20::get(String id) {
  String message = "";
  if (id == _temperature_id) {
    getTemperature();
    message = id + ":" + String(temperature, 1);
  }
  return message;
}


String Ds18b20::set(String id, String value) {
  return "";
}


void Ds18b20::getTemperature(void) {
  // Read Temperature
  byte present = _ds->reset();
  _ds->select(_temperature_address);    
  _ds->write(0xBE); // Read Scratchpad            
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    _temperature_data[i] = _ds->read();
  }         
  _ds->reset_search();           
  byte MSB = _temperature_data[1];
  byte LSB = _temperature_data[0];        
  float temp_read = ((MSB << 8) | LSB); // using two's compliment
  temperature = temp_read / 16;

  // Start Conversion For Next Temperature Reading
  if (!_ds->search(_temperature_address)) {
     // Serial.println("no more sensors on chain, reset search!");
      _ds->reset_search();
  }      
  if (OneWire::crc8(_temperature_address, 7) != _temperature_address[7]) {
     // Serial.println("CRC is not valid!");
  }        
  if (_temperature_address[0] != 0x10 && _temperature_address[0] != 0x28) {
     // Serial.print("Device is not recognized!");
  }      
  _ds->reset();
  _ds->select(_temperature_address);
  _ds->write(0x44,1); // start conversion, with parasite power on at the end
}

float Ds18b20::avergeArray(int* arr, int number){
  int i;
  int max,min;
  float avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to averaging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (float)amount/(number-2);
  }//if
  return avg;
}



