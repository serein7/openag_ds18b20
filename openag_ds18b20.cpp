/**
 *  \file openag_ds18b20.cpp
 *  \brief Sensor module for temperature.
 */
#include "openag_ds18b20.h"

Ds18b20::Ds18b20(String id, String* parameters) : Peripheral(id, parameters){
  this->id = id;
  _temperature_pin = parameters[0].toInt();
}

Ds18b20::~Ds18b20(){}

void Ds18b20::begin() {

  _ds = new OneWire(_temperature_pin); // enable OneWire port
  _time_of_last_reading = 0; // initialize time of last reading
  _temperature_message = getErrorMessage(TEMPERATURE_KEY); // initialize message
}

String Ds18b20::get(String key) {
  if (key == String(TEMPERATURE_KEY)) {
    readData();
    return getTemperature();
  }
  return getErrorMessage(key);
}

String Ds18b20::set(String key, String value) {
  return getErrorMessage(key);
}

String Ds18b20::getTemperature(){
  if (millis() - _time_of_last_reading > MIN_UPDATE_INTERVAL){ // can only read sensor so often
    readData();
    _time_of_last_reading = millis();
  }
  return _temperature_message;
}

void Ds18b20::readData() {
  boolean is_good_reading = true;
  byte temperature_data[12];
  byte temperature_address[8];

  // Start temperature conversion
  if (!_ds->search(temperature_address)) {
      _ds->reset_search();
  }
  _ds->reset();
  _ds->select(temperature_address);
  _ds->write(0x44,1); // start conversion, with parasite power on at the end

  // Read sensor
  _ds->reset();
  _ds->select(temperature_address);
  _ds->write(0xBE); // Read Scratchpad
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    temperature_data[i] = _ds->read();
  }
  _ds->reset_search();

  // Check for failures
  if (OneWire::crc8(temperature_address, 7) != temperature_address[7]) {
     is_good_reading = false; // invalid CRC
  }
  else if (temperature_address[0] != 0x10 && temperature_address[0] != 0x28) {
     is_good_reading = false; // unrecognized device
  }
  else { // good reading
    byte MSB = temperature_data[1];
    byte LSB = temperature_data[0];
    float temp_read = ((MSB << 8) | LSB); // using two's compliment
    temperature = temp_read / 16;
  }

  // Update messages
  if (is_good_reading) {
    _temperature_message = getMessage(TEMPERATURE_KEY, String(temperature, 1));
  }
  else { // read failure
    _temperature_message = getErrorMessage(TEMPERATURE_KEY);
  }
}

String Ds18b20::getMessage(String key, String value) {
  return String(id + "," + key + "," + value);
}

String Ds18b20::getErrorMessage(String key) {
  return String(id + "," + key + ",error");
}
