/** 
 *  \file openag-s18b20.h
 *  \brief Sensor module for water temperature. 
 *  \author Jake Rye
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
 * \brief Sensor module for water temperature
 */
class Ds18b20 {
  public:
    // Public Functions
    /*
     * \brief Class constructor.
     */
    Ds18b20(String temperature_id, int temperature_pin);

    /**
     * \brief Called once to setup module.
     * Declares objects, configures initial state, sets configuration & calibration parameters.
     */
    void begin(void);
    
    /**
     * \brief Returns JSON string with module data.
     * Module data: temperature
     * Data: "<instruction_code> <instruction_id> <value>".
     * Example: "SWTM 1 1", 
     */
    String get(String id);

    /**
     * \brief Reserved to passing data string to object
     * Currently unused. Exists to comply with SAModule interface.
     */
    String set(String id, String value);

    // Public Variables
    float temperature; // degrees C
    
  private:
    // Private Functions
    void getSensorData(void);
    float getTemperature(void);
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

#endif // DS18B20_H_



