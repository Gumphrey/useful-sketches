// credit to https://stackoverflow.com/questions/36219687/python-serial-to-arduino-speed-test

void setup() {
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()) {
    Serial.write(Serial.read());
  }
}
