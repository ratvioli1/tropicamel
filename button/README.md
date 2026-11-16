## Building

turn-button is an Arduino sketch meant for the ESP32-C3.

TODO: add core install instructions

```bash
arduino-cli board listall XIAO
...
arduino-cli compile --fqbn esp32:esp32:XIAO_ESP32C3 turn_button
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:XIAO_ESP32C3 turn_button
arduino-cli monitor -p /dev/ttyACM0 -c baudrate=115200
```
