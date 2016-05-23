/**
 *  \file openag_ds18b20.h
 *  \brief Sensor module for temperature.
 */
#ifndef DS18B20_H
#define DS18B20_H

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include "WProgram.h"
#endif

#include <OneWire.h>
#include <openag_peripheral.h>

/**
 * \brief Sensor module for temperature
 */
class Ds18b20 : public Peripheral {
  public:
    // Public Functions
    Ds18b20(String id, String* parameters);
    ~Ds18b20();
    void begin();
    String get(String key);
    String set(String key, String value);

    // Public Variables
    String id;
    float temperature; // degrees C

  private:
    // Private Functions
    String getTemperature();
    void readData();
    String getMessage(String key, String value);
    String getErrorMessage(String key);

    // Private Variables
    uint32_t _time_of_last_reading;
    const static uint32_t _min_update_interval = 1000;
    String _temperature_key;
    int _temperature_pin;
    String _temperature_message;
    OneWire *_ds;
};

#endif
