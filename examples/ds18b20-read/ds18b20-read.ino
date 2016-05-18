#include <openag-ds18b20.h>
Ds18b20 ds18b20("temperature", 22);

void setup() {
  Serial.begin(9600);
  ds18b20.begin();
}

void loop() {
  Serial.println(ds18b20.get("temperature"));
  delay(1000);
}