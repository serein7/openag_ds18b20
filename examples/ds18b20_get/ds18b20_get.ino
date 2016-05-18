#include <openag_ds18b20.h>
Ds18b20 ds18b20("water_temperature", 22);

void setup() {
  Serial.begin(9600);
  ds18b20.begin();
}

void loop() {
  Serial.println(ds18b20.get("water_temperature"));
  delay(1000);
}