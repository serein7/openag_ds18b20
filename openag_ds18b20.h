/** 
 *  \file openag_ds18b20.h
 *  \brief Sensor module for temperature. 
 */
#ifndef DS18B20_H
#define DS18B20_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <OneWire.h>

/**
 * \brief Sensor module for temperature
 */
class Ds18b20 {
  public:
    // Public Functions
    Ds18b20(String temperature_id, int temperature_pin);
    void begin(void);
    String get(String id);
    String set(String id, String value);

    // Public Variables
    float temperature; // degrees C
    
  private:
    // Private Functions
    void getTemperature(void);
    float avergeArray(int* arr, int number);
    void startTempertureConversion(void);
    float TempProcess(bool ch);

    // Private Variables
    String _temperature_id;
    int _temperature_pin;
    int _prev_update_time;
    byte _temperature_data[12];
    byte _temperature_address[8];
    OneWire *_ds;
};

#endif



