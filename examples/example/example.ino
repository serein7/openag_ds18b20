#include <openag_ds18b20.h>
String parameters[] = {String("22")};
Ds18b20 ds18b20("ds18b20_1", parameters);

void setup() {
  Serial.begin(9600);
  ds18b20.begin();
}

void loop() {
  Serial.println(ds18b20.get("temperature"));
  delay(1000);
}
